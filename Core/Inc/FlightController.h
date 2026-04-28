/*
 * FlightController.h
 *
 *  Created on: Apr 27, 2026
 *      Author: dalya
 */

#ifndef FLIGHTCONTROLLER_H_
#define FLIGHTCONTROLLER_H_

#include "Receiver.h"
#include "State_Estimator.h"
#include "PIDController.h"
#include "Motor.h"
#include "esc_pwm.h"
#include "hmc5883l.h"
#include "bmp280.h"
#include "mpu6050.h"
#include "stm32f4xx_hal.h"

typedef enum {
	NON_CALIBRATED,
	CALIBRATED
}Calibration_state;

typedef struct {
	RC_Command_t* rc_cmd;
	State_Estimator_t* state;
	MPU6050_Handle_t* mpu;
	BMP280_Handle_t* bmp;
	HMC5883L_Handle_t* hmc;
	PID_Controller_t* roll_pid;
	PID_Controller_t* pitch_pid;
	PID_Controller_t* yaw_pid;
	PID_Controller_t* alt_pid;
	Motor_t* motor_out;
	Calibration_state calib_state;
}Drone_t;


void flight_controller_update(Drone_t* drone);

#endif /* FLIGHTCONTROLLER_H_ */
