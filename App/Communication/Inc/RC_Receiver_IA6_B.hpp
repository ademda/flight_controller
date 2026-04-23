/*
 * RC_Receiver_IA6_B.hpp
 *
 *  Created on: Apr 15, 2026
 *      Author: dalya
 */

#ifndef COMMUNICATION_INC_RC_RECEIVER_IA6_B_HPP_
#define COMMUNICATION_INC_RC_RECEIVER_IA6_B_HPP_

#include "RCReceiver.hpp"
#include <stdint.h>

class RC_Receiver_IA6_B : public RCReceiver {
public:
	RC_Receiver_IA6_B();
	~RC_Receiver_IA6_B();
	
	bool init();
	Receiver_Data_t getCommand() override;
	void updateRawChannels(uint16_t channels[6]);
	bool isSignalLost() const;
	uint16_t getRawChannel(uint8_t channel) const;

private:
	Receiver_Data_t _receiver_data;
	uint16_t _raw_channels[6];
	bool _signal_lost;
};

#endif /* COMMUNICATION_INC_RC_RECEIVER_IA6_B_HPP_ */
