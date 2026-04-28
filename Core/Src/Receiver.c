/*
 * FlightController.c
 *
 *  Created on: Apr 27, 2026
 *      Author: dalya
 */

#include "Receiver.h"
#include "utils.h"

void parse_received_data(uint16_t *ibus_data){
	for (uint8_t channel_index = 0 ,buffer_index = 2; channel_index < IBUS_USER_CHANNELS ; channel_index++, buffer_index+= 2){
		ibus_data[channel_index] = uart_rx_buffer[buffer_index] << 8 | uart_rx_buffer[buffer_index];
	}
}

void get_commands(uint16_t *ibus_data, RC_Command_t * rc_cmd){
	uint16_t roll_raw = ibus_data[0];
	uint16_t pitch_raw = ibus_data[1];
	uint16_t throttle_raw = ibus_data[2];
	uint16_t yaw_raw = ibus_data[3];
	uint16_t arm_raw = ibus_data[4];

	rc_cmd->roll = MAP(roll_raw, PULSE_MIN, PULSE_MAX, ROLL_MIN_DEG, ROLL_MAX_DEG);
	rc_cmd->pitch = MAP(pitch_raw, PULSE_MIN, PULSE_MAX, PITCH_MIN_DEG, PITCH_MAX_DEG);
	rc_cmd->throttle = MAP(throttle_raw, PULSE_MIN, PULSE_MAX, THROTTLE_MIN, THROTTLE_MAX);
	rc_cmd->yaw = MAP(yaw_raw, PULSE_MIN, PULSE_MAX, YAW_MIN_DEG, YAW_MAX_DEG);

	rc_cmd->arm_value = arm_raw > PULSE_MID ? ARMED : DISARMED;
}



