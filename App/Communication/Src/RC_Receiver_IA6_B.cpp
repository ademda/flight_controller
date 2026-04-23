/*
 * RC_Receiver_IA6_B.cpp
 *
 *  Created on: Apr 15, 2026
 *      Author: dalya
 */

#include "../Inc/RC_Receiver_IA6_B.hpp"

RC_Receiver_IA6_B::RC_Receiver_IA6_B() : _signal_lost(false) {
    _receiver_data.throttle = 0.0f;
    _receiver_data.roll = 0.0f;
    _receiver_data.pitch = 0.0f;
    _receiver_data.yaw = 0.0f;
    _receiver_data.isArmed = false;
    
    for (int i = 0; i < 6; i++) {
        _raw_channels[i] = 1500;
    }
}

RC_Receiver_IA6_B::~RC_Receiver_IA6_B() {
}

bool RC_Receiver_IA6_B::init() {
    // TODO: Initialize UART for PPM signal reception
    return true;
}

Receiver_Data_t RC_Receiver_IA6_B::getCommand() {
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
    
    // TODO: Check for signal loss
    for (int i = 0; i < 6; i++) {
        if (_raw_channels[i] < 500 || _raw_channels[i] > 2500) {
            _signal_lost = true;
            _receiver_data.isArmed = false;
            return _receiver_data;
        }
    }
    _signal_lost = false;
    
    return _receiver_data;
}

void RC_Receiver_IA6_B::updateRawChannels(uint16_t channels[6]) {
    for (int i = 0; i < 6; i++) {
        _raw_channels[i] = channels[i];
    }
}

bool RC_Receiver_IA6_B::isSignalLost() const {
    return _signal_lost;
}

uint16_t RC_Receiver_IA6_B::getRawChannel(uint8_t channel) const {
    if (channel >= 6) return 0;
    return _raw_channels[channel];
}
