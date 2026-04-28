/*
 * Motor.h
 *
 *  Created on: Apr 28, 2026
 *      Author: dalya
 */

#ifndef INC_MOTOR_H_
#define INC_MOTOR_H_

#include <stdint.h>
#include "stm32f4xx_hal.h"


#define MOTOR_MIN 1200.0f
#define MOTOR_MAX 1800.0f

typedef struct{
	uint16_t motor1;
	uint16_t motor2;
	uint16_t motor3;
	uint16_t motor4;
	TIM_HandleTypeDef *htim;
}Motor_t;


void motor_mixer(float roll_out, float pitch_out, float yaw_out,
                 float throttle, Motor_t *motor_out);

#endif /* INC_MOTOR_H_ */
