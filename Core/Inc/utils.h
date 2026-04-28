/*
 * utils.h
 *
 *  Created on: Apr 27, 2026
 *      Author: dalya
 */

#ifndef INC_UTILS_H_
#define INC_UTILS_H_


#define MAP(value, in_min, in_max, out_min, out_max) \
    ((value - in_min) * (out_max - out_min) / (in_max - in_min) + out_min)

typedef enum{
	ARMED,
	DISARMED
}Drone_state;


#endif /* INC_UTILS_H_ */
