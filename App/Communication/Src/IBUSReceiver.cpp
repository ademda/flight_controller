/*
 * IBUSReceiver.cpp
 *
 *  Created on: Apr 16, 2026
 *      Author: dalya
 */

#include "IBUSReceiver.hpp"
#include <string.h>
#include "sbus_rx.h"

IBUSReceiver::IBUSReceiver(UART_HandleTypeDef* uart) 
	: _uart(uart), _signal_lost(false), _failsafe_counter(0) {
	
	// Initialize receiver data
	_receiver_data.throttle = 0.0f;
	_receiver_data.roll = 0.0f;
	_receiver_data.pitch = 0.0f;
	_receiver_data.yaw = 0.0f;
	_receiver_data.isArmed = false;
	
	// Initialize raw channels to center position (1500us)
	for (int i = 0; i < IBUS_MAX_CHANNELS; i++) {
		_raw_channels[i] = 1500;
	}
	
	// Initialize UART buffer
	memset(_uart_rx_buffer, 0, sizeof(_uart_rx_buffer));
}

IBUSReceiver::~IBUSReceiver() {
}

bool IBUSReceiver::init() {
	if (_uart == nullptr) {
		return false;
	}
	
	// Start DMA reception on UART
	ibus_uart_init(_uart);
	return true;
}

Receiver_Data_t IBUSReceiver::getCommand() {
	// Fetch latest data from DMA buffer in driver
	uint8_t* dma_buffer = ibus_get_buffer();
	if (dma_buffer != nullptr) {
		memcpy(_uart_rx_buffer, dma_buffer, IBUS_LENGTH);
	}
	
	// Validate and extract channel data
	if (!isValid()) {
		_signal_lost = true;
		_receiver_data.isArmed = false;
		return _receiver_data;
	}
	
	if (!verifyChecksum()) {
		_signal_lost = true;
		_receiver_data.isArmed = false;
		return _receiver_data;
	}
	
	// Extract raw channel values
	extractChannels();
	_failsafe_counter = 0;  // Reset failsafe counter on valid data
	_signal_lost = false;
	
	// Normalize throttle (Channel 0: 1000-2000 -> 0.0-1.0)
	_receiver_data.throttle = (_raw_channels[0] - 1000.0f) / 1000.0f;
	if (_receiver_data.throttle < 0.0f) _receiver_data.throttle = 0.0f;
	if (_receiver_data.throttle > 1.0f) _receiver_data.throttle = 1.0f;
	
	// Normalize roll (Channel 1: 1000-2000 -> -1.0-1.0)
	_receiver_data.roll = (_raw_channels[1] - 1500.0f) / 500.0f;
	if (_receiver_data.roll < -1.0f) _receiver_data.roll = -1.0f;
	if (_receiver_data.roll > 1.0f) _receiver_data.roll = 1.0f;
	
	// Normalize pitch (Channel 2: 1000-2000 -> -1.0-1.0)
	_receiver_data.pitch = (_raw_channels[2] - 1500.0f) / 500.0f;
	if (_receiver_data.pitch < -1.0f) _receiver_data.pitch = -1.0f;
	if (_receiver_data.pitch > 1.0f) _receiver_data.pitch = 1.0f;
	
	// Normalize yaw (Channel 3: 1000-2000 -> -1.0-1.0)
	_receiver_data.yaw = (_raw_channels[3] - 1500.0f) / 500.0f;
	if (_receiver_data.yaw < -1.0f) _receiver_data.yaw = -1.0f;
	if (_receiver_data.yaw > 1.0f) _receiver_data.yaw = 1.0f;
	
	// Arm switch (Channel 4: 1700-2000us = armed)
	_receiver_data.isArmed = (_raw_channels[4] > 1700);
	
	// Perform software failsafe check
	updateFailsafe(20);  // Failsafe after 20 missed frames
	
	return _receiver_data;
}

void IBUSReceiver::updateFromUARTBuffer(uint8_t* buffer, uint16_t length) {
	if (buffer == nullptr || length == 0) {
		return;
	}
	
	// Copy data from DMA buffer
	uint16_t copy_size = (length < IBUS_LENGTH) ? length : IBUS_LENGTH;
	memcpy(_uart_rx_buffer, buffer, copy_size);
}

void IBUSReceiver::resetFailsafe() {
	_failsafe_counter = 0;
}

bool IBUSReceiver::isSignalLost() const {
	return _signal_lost;
}

uint16_t IBUSReceiver::getRawChannel(uint8_t channel) const {
	if (channel >= IBUS_MAX_CHANNELS) {
		return 0;
	}
	return _raw_channels[channel];
}

// Private helper methods

bool IBUSReceiver::isValid() const {
	// Check frame header: length byte (0x20) and command byte (0x40)
	return (_uart_rx_buffer[0] == IBUS_LENGTH && _uart_rx_buffer[1] == IBUS_COMMAND);
}

bool IBUSReceiver::verifyChecksum() const {
	uint16_t checksum_calculated = 0xffff;
	uint16_t checksum_received;
	
	// Calculate checksum from first 30 bytes
	for (int i = 0; i < 30; i++) {
		checksum_calculated -= _uart_rx_buffer[i];
	}
	
	// Extract checksum from last two bytes (little-endian)
	checksum_received = _uart_rx_buffer[31] << 8 | _uart_rx_buffer[30];
	
	return (checksum_received == checksum_calculated);
}

void IBUSReceiver::extractChannels() {
	// Extract 14 channels from buffer, starting at byte 2
	// Each channel is 2 bytes (little-endian)
	for (int ch = 0; ch < IBUS_MAX_CHANNELS; ch++) {
		uint8_t byte_index = 2 + (ch * 2);
		_raw_channels[ch] = _uart_rx_buffer[byte_index + 1] << 8 | _uart_rx_buffer[byte_index];
	}
}

void IBUSReceiver::updateFailsafe(uint8_t failsafe_threshold) {
	_failsafe_counter++;
	
	if (_failsafe_counter >= failsafe_threshold) {
		// Trigger failsafe
		_signal_lost = true;
		_receiver_data.isArmed = false;
		
		// Set all channels to safe values
		for (int i = 0; i < IBUS_MAX_CHANNELS; i++) {
			_raw_channels[i] = 0;
		}
		
		// Clear buffer
		memset(_uart_rx_buffer, 0, sizeof(_uart_rx_buffer));
	}
}
