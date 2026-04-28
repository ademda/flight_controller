/*
 * esc_pwm.h
 *
 *  Created on: Apr 16, 2026
 *      Author: dalya
 */

#ifndef INC_ESC_PWM_H_
#define INC_ESC_PWM_H_

#include "stm32f4xx_hal.h"
#include <stdint.h>
#include <stdbool.h>

// Timer configuration parameters
#define ESC_TIMER_PRESCALER     63      // Prescaler value
#define ESC_TIMER_ARR           2499    // Auto-reload register (2.5ms period)
#define ESC_TIMER_FREQ_HZ       72000000UL

// Calculate microsecond to pulse value conversion
// Timer clock = 72MHz / (63+1) = 1.125MHz
// Each tick = 1/1.125MHz = 0.888us
#define US_PER_TICK             ((float)(ESC_TIMER_PRESCALER + 1) / (ESC_TIMER_FREQ_HZ / 1000000UL))

// PWM pulse widths for ESC (in microseconds)
#define ESC_PWM_MIN_US          1000    // Minimum throttle
#define ESC_PWM_MAX_US          2000    // Maximum throttle
#define ESC_PWM_MID_US          1500    // Middle throttle

// Convert microseconds to timer pulse value
#define US_TO_PULSE(us)         ((uint16_t)((us) / US_PER_TICK))

#define ESC_PWM_MIN             US_TO_PULSE(ESC_PWM_MIN_US)
#define ESC_PWM_MAX             US_TO_PULSE(ESC_PWM_MAX_US)
#define ESC_PWM_MID             US_TO_PULSE(ESC_PWM_MID_US)

// Timer and channels for 4 ESCs
#define ESC_TIMER               TIM1
#define ESC_TIMER_CH1           TIM_CHANNEL_1    // Motor 1
#define ESC_TIMER_CH2           TIM_CHANNEL_2    // Motor 2
#define ESC_TIMER_CH3           TIM_CHANNEL_3    // Motor 3
#define ESC_TIMER_CH4           TIM_CHANNEL_4    // Motor 4

/**
 * @brief Initialize ESC PWM outputs on Timer1
 * @param htim Pointer to Timer1 handle
 * @return true if successful
 */
bool ESC_PWM_Init(TIM_HandleTypeDef *htim);

/**
 * @brief Set PWM pulse width for a specific ESC channel
 * @param htim Pointer to Timer1 handle
 * @param channel Timer channel (TIM_CHANNEL_1 to TIM_CHANNEL_4)
 * @param pulse_us Pulse width in microseconds (1000-2000)
 */
void ESC_PWM_SetPulse_us(TIM_HandleTypeDef *htim, uint32_t channel, uint16_t pulse_us);

/**
 * @brief Set PWM pulse width for a specific ESC channel (direct pulse value)
 * @param htim Pointer to Timer1 handle
 * @param channel Timer channel (TIM_CHANNEL_1 to TIM_CHANNEL_4)
 * @param pulse Pulse value (calculated from microseconds)
 */
void ESC_PWM_SetPulse(TIM_HandleTypeDef *htim, uint32_t channel, uint16_t pulse);

/**
 * @brief Set all 4 motors to specific throttle values (0.0-1.0)
 * @param htim Pointer to Timer1 handle
 * @param throttle1 Motor 1 throttle (0.0 = min, 1.0 = max)
 * @param throttle2 Motor 2 throttle
 * @param throttle3 Motor 3 throttle
 * @param throttle4 Motor 4 throttle
 */
void ESC_PWM_SetThrottle(TIM_HandleTypeDef *htim, uint16_t throttle1, uint16_t throttle2, uint16_t throttle3, uint16_t throttle4);

/**
 * @brief Calibrate ESCs (must be done before first use)
 * Sends maximum throttle, then minimum throttle for calibration
 * @param htim Pointer to Timer1 handle
 * @param duration_ms How long to hold each throttle level (typically 1000-2000ms)
 */
void ESC_PWM_Calibrate(TIM_HandleTypeDef *htim, uint32_t duration_ms);

#endif /* INC_ESC_PWM_H_ */
