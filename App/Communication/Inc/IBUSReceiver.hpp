/*
 * IBUSReceiver.hpp
 *
 *  Created on: Apr 16, 2026
 *      Author: dalya
 */

#ifndef COMMUNICATION_INC_IBUSRECEIVER_HPP_
#define COMMUNICATION_INC_IBUSRECEIVER_HPP_

#include "RCReceiver.hpp"
#include "stm32f1xx_hal.h"
#include <stdint.h>

class IBUSReceiver : public RCReceiver {
public:
	IBUSReceiver(UART_HandleTypeDef* uart);
	~IBUSReceiver();
	
	bool init();
	Receiver_Data_t getCommand() override;
	void updateFromUARTBuffer(uint8_t* buffer, uint16_t length);
	bool isSignalLost() const;
	uint16_t getRawChannel(uint8_t channel) const;
	void resetFailsafe();

private:
	// Protocol constants
	static constexpr uint8_t IBUS_LENGTH = 0x20;           // 32 bytes
	static constexpr uint8_t IBUS_COMMAND = 0x40;          // Command byte
	static constexpr uint8_t IBUS_MAX_CHANNELS = 14;
	static constexpr uint8_t IBUS_USER_CHANNELS = 6;
	
	// UART communication
	UART_HandleTypeDef* _uart;
	uint8_t _uart_rx_buffer[32];
	
	// Data
	Receiver_Data_t _receiver_data;
	uint16_t _raw_channels[IBUS_MAX_CHANNELS];
	bool _signal_lost;
	uint8_t _failsafe_counter;
	
	// Helper methods
	bool isValid() const;
	bool verifyChecksum() const;
	void extractChannels();
	void updateFailsafe(uint8_t failsafe_threshold);
};

#endif /* COMMUNICATION_INC_IBUSRECEIVER_HPP_ */
