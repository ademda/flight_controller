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


typedef struct {
	RC_Command_t rc_cmd;
	State_t state;
	MPU6050_Handle_t mpu;
	BMP280_Handle_t bmp;
	HMC5883L_Handle_t hmc;
	PID_Controller_t roll_pid;
	PID_Controller_t pitch_pid;
	PID_Controller_t yaw_pid;
	PID_Controller_t alt_pid;
	Motor_t motor_out;
}Drone_t;

void flight_controller_init(Drone_t* drone);

void flight_controller_update(Drone_t* drone);

#endif /* FLIGHTCONTROLLER_H_ */
