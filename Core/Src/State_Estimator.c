/*
 * State_Estimator.c
 *
 *  Created on: Apr 27, 2026
 *      Author: dalya
 */
#include "mpu6050.h"
#include "bmp280.h"
#include "hmc5883l.h"
#include "State_Estimator.h"

void compute_current_state(State_Estimator_t *state, MPU6050_Handle_t* mpu, BMP280_Handle_t *bmp, HMC5883L_Handle_t *hmc){
	state->pitch = mpu->pitch;
	state->roll = mpu->roll;
	state->yaw = hmc->yaw;
	state->altitude = bmp->altitude;
	state->climb_rate = state->altitude - state->last_altitude;
	state->last_altitude = state->altitude;
}

