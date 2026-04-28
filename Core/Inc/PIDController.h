/*
 * PIDController.h
 *
 *  Created on: Apr 27, 2026
 *      Author: dalya
 */

#ifndef INC_PIDCONTROLLER_H_
#define INC_PIDCONTROLLER_H_

#include "Receiver.h"
#include "State_Estimator.h"
#include "stm32f4xx_hal.h"

typedef struct {
	float Kp;
	float Ki;
	float Kd;
	float integral_max;
	float output_max;
	float output_min;
	float prev_error;
	float integral;
}PID_Controller_t;

void drone_control(PID_Controller_t *roll_pid,PID_Controller_t *pitch_pid,
				   PID_Controller_t*yaw_pid, RC_Command_t *rc_cmd, State_Estimator_t *state,
				   float* roll_correction,float *pitch_correction, float*  yaw_correction);

float pid_compute(PID_Controller_t* pid_controller, float setpoint, float current);

void pid_reset(PID_Controller_t *pid);



#endif /* INC_PIDCONTROLLER_H_ */
