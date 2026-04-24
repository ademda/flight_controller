/*
 * RCReceiver.hpp
 *
 *  Created on: Apr 15, 2026
 *      Author: dalya
 */

#ifndef INC_RCRECEIVER_HPP_
#define INC_RCRECEIVER_HPP_

#include <stdbool.h>

typedef struct {
	float throttle; // 0.0 to 1.0
	float roll;     // -1.0 to 1.0
	float pitch;    // -1.0 to 1.0
	float yaw;      // -1.0 to 1.0
	bool isArmed;
}Receiver_Data_t;

class RCReceiver {
public:
	virtual ~RCReceiver();
	virtual Receiver_Data_t getCommand() = 0;
};



#endif /* INC_RCRECEIVER_HPP_ */
