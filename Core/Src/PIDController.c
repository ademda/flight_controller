/*
 * PIDController.c
 *
 *  Created on: Apr 27, 2026
 *      Author: dalya
 */
#include "PIDController.h"
#include "PIDConstants.h"

void pid_init(PID_Controller_t *roll_pid, PID_Controller_t *pitch_pid,
		PID_Controller_t *yaw_pid, PID_Controller_t *alt_pid) {

    // ========== ROLL PID ==========
    // Controls left-right tilt
    roll_pid->Kp = ROLL_KP;
    roll_pid->Ki = ROLL_KI;
    roll_pid->Kd = ROLL_KD;
    roll_pid->integral_max = ROLL_INTEGRAL_MAX;
    roll_pid->output_max = ROLL_OUTPUT_MAX;
    roll_pid->output_min = ROLL_OUTPUT_MIN;
    roll_pid->prev_error = 0.0f;
    roll_pid->integral = 0.0f;

    // ========== PITCH PID ==========
    // Controls forward-backward tilt (same as roll for X-quad)
    pitch_pid->Kp = PITCH_KP;
    pitch_pid->Ki = PITCH_KI;
    pitch_pid->Kd = PITCH_KD;
    pitch_pid->integral_max = PITCH_INTEGRAL_MAX;
    pitch_pid->output_max = PITCH_OUTPUT_MAX;
    pitch_pid->output_min = PITCH_OUTPUT_MIN;
    pitch_pid->prev_error = 0.0f;
    pitch_pid->integral = 0.0f;

    // ========== YAW PID ==========
    // Controls rotation (different tuning than roll/pitch)
    // Note: Yaw uses yaw_rate (degrees/sec), not angle error
    yaw_pid->Kp = YAW_KP;
    yaw_pid->Ki = YAW_KI;
    yaw_pid->Kd = YAW_KD;
    yaw_pid->integral_max = YAW_INTEGRAL_MAX;
    yaw_pid->output_max = YAW_OUTPUT_MAX;
    yaw_pid->output_min = YAW_OUTPUT_MIN;
    yaw_pid->prev_error = 0.0f;
    yaw_pid->integral = 0.0f;

    // ========== ALTITUDE PID ==========
    // Controls climb rate (vertical speed)
    // This is often a slower loop than attitude control
    alt_pid->Kp = ALT_KP;
    alt_pid->Ki = ALT_KI;
    alt_pid->Kd = ALT_KD;
    alt_pid->integral_max = ALT_INTEGRAL_MAX;
    alt_pid->output_max = ALT_OUTPUT_MAX;
    alt_pid->output_min = ALT_OUTPUT_MIN;
    alt_pid->prev_error = 0.0f;
    alt_pid->integral = 0.0f;
}

float pid_compute(PID_Controller_t* pid_controller, float setpoint, float current){
	float error = setpoint - current;
	float P_out = pid_controller->Kp * error;
	pid_controller->integral =pid_controller->Ki*(error + pid_controller->integral);
	if (pid_controller->integral > pid_controller->integral_max){
		pid_controller->integral = pid_controller->integral_max;
	}
	else if (pid_controller->integral < -pid_controller->integral_max){
		pid_controller->integral = -pid_controller->integral_max;
	}

	float D_out = pid_controller->Kd*(error - pid_controller->prev_error);
	float PID_out = PID_out + pid_controller->integral + D_out;

	if (PID_out > pid_controller->output_max){
		PID_out = pid_controller->output_max;
	}
	else if (PID_out < pid_controller->output_min){
		PID_out = pid_controller->output_min;
	}
	return PID_out;
}

void pid_reset(PID_Controller *pid) {
    pid->integral = 0.0f;
    pid->prev_error = 0.0f;
}

void drone_control(PID_Controller_t *roll_pid,PID_Controller_t *pitch_pid,
				   PID_Controller_t*yaw_pid, RC_Command_t *rc_cmd, State_t *state,
				   float* roll_correction,float *pitch_correction, float*  yaw_correction){

	 *roll_correction = pid_compute(roll_pid, rc_cmd->roll, state->roll);
	 *pitch_correction = pid_compute(pitch_pid, rc_cmd->pitch, state->pitch);
	 *yaw_correction = pid_compute(yaw_pid, rc_cmd->yaw, state->yaw);
	//float alt_out = pid_compute(alt_pid, rc_cmd->throttle, state->climb_rate);
	/*No need for PID for altitude since i will inject the thrtotle directly to the 4 esc*/
}



