/*
 * PIDConstants.h
 *
 *  Created on: Apr 27, 2026
 *      Author: dalya
 */

#ifndef INC_PIDCONSTANTS_H_
#define INC_PIDCONSTANTS_H_

// ========== ROLL PID CONSTANTS ==========
#define ROLL_KP             4.5f
#define ROLL_KI             0.05f
#define ROLL_KD             2.0f
#define ROLL_INTEGRAL_MAX   50.0f
#define ROLL_OUTPUT_MAX     200.0f
#define ROLL_OUTPUT_MIN     -200.0f

// ========== PITCH PID CONSTANTS ==========
#define PITCH_KP            4.5f
#define PITCH_KI            0.05f
#define PITCH_KD            2.0f
#define PITCH_INTEGRAL_MAX  50.0f
#define PITCH_OUTPUT_MAX    200.0f
#define PITCH_OUTPUT_MIN    -200.0f

// ========== YAW PID CONSTANTS ==========
#define YAW_KP              3.0f
#define YAW_KI              0.02f
#define YAW_KD              1.0f
#define YAW_INTEGRAL_MAX    30.0f
#define YAW_OUTPUT_MAX      150.0f
#define YAW_OUTPUT_MIN      -150.0f

// ========== ALTITUDE PID CONSTANTS ==========
#define ALT_KP              2.0f
#define ALT_KI              0.01f
#define ALT_KD              0.5f
#define ALT_INTEGRAL_MAX    20.0f
#define ALT_OUTPUT_MAX      100.0f
#define ALT_OUTPUT_MIN      -100.0f


#endif /* INC_PIDCONSTANTS_H_ */
