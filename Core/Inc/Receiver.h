/*
 * FlightController.h
 *
 *  Created on: Apr 27, 2026
 *      Author: dalya
 */

#ifndef INC_RECEIVER_H_
#define INC_RECEIVER_H_

#include "utils.h"
#include "sbus_rx.h"

#define IBUS_USER_CHANNELS	5

#define PULSE_MIN		1000
#define PULSE_MAX		2000
#define PULSE_MID 		1500

#define ROLL_MAX_DEG 	45
#define ROLL_MIN_DEG 	-45
#define PITCH_MAX_DEG	45
#define PITCH_MIN_DEG	-45
#define YAW_MAX_DEG  	45
#define YAW_MIN_DEG  	-45
#define THROTTLE_MAX	1800
#define THROTTLE_MIN	1200


typedef struct {
	float roll;
	float pitch;
	uint16_t throttle;
	float yaw;
	Drone_state arm_value;
	uint16_t ibus_data[IBUS_FRAME_LENGTH];
}RC_Command_t;

void get_commands(uint16_t *ibus_data, RC_Command_t * rc_cmd);
void parse_received_data(uint16_t *ibus_data);

#endif /* INC_RECEIVER_H_ */
