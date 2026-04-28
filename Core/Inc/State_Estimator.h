/*
 * State_Estimator.h
 *
 *  Created on: Apr 27, 2026
 *      Author: dalya
 */

#ifndef INC_STATE_ESTIMATOR_H_
#define INC_STATE_ESTIMATOR_H_

#include "utils.h"
#include "stm32f4xx_hal.h"
#include "bmp280.h"
#include "mpu6050.h"
#include "hmc5883l.h"

typedef struct {
	float roll;
	float pitch;
	float yaw;
	float altitude;
	float last_altitude;
	float climb_rate;
}State_Estimator_t;

void compute_current_state(State_Estimator_t *state, MPU6050_Handle_t* mpu, BMP280_Handle_t *bmp, HMC5883L_Handle_t *hmc);

#endif /* INC_STATE_ESTIMATOR_H_ */
