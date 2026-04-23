/*
 * esc_pwm.c
 *
 *  Created on: Apr 16, 2026
 *      Author: dalya
 */

#include "esc_pwm.h"
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

// Utility macros for min/max
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

/**
 * Initialize ESC PWM outputs on Timer1
 * Configure all 4 channels for PWM output
 */
bool ESC_PWM_Init(TIM_HandleTypeDef *htim)
{
	if (htim == NULL)
		return false;

	// Start PWM generation on all 4 channels
	HAL_TIM_PWM_Start(htim, ESC_TIMER_CH1);
	HAL_TIM_PWM_Start(htim, ESC_TIMER_CH2);
	HAL_TIM_PWM_Start(htim, ESC_TIMER_CH3);
	HAL_TIM_PWM_Start(htim, ESC_TIMER_CH4);

	// Set all motors to minimum throttle (1000us) initially
	ESC_PWM_SetPulse(htim, ESC_TIMER_CH1, ESC_PWM_MIN);
	ESC_PWM_SetPulse(htim, ESC_TIMER_CH2, ESC_PWM_MIN);
	ESC_PWM_SetPulse(htim, ESC_TIMER_CH3, ESC_PWM_MIN);
	ESC_PWM_SetPulse(htim, ESC_TIMER_CH4, ESC_PWM_MIN);

	return true;
}

/**
 * Set PWM pulse width in microseconds
 */
void ESC_PWM_SetPulse_us(TIM_HandleTypeDef *htim, uint32_t channel, uint16_t pulse_us)
{
	// Clamp to valid range
	pulse_us = MAX(ESC_PWM_MIN_US, MIN(pulse_us, ESC_PWM_MAX_US));

	// Convert microseconds to pulse value
	uint16_t pulse = US_TO_PULSE(pulse_us);
	ESC_PWM_SetPulse(htim, channel, pulse);
}

/**
 * Set PWM pulse width (direct pulse value)
 */
void ESC_PWM_SetPulse(TIM_HandleTypeDef *htim, uint32_t channel, uint16_t pulse)
{
	if (htim == NULL)
		return;

	// Clamp pulse value to valid range
	pulse = MAX(ESC_PWM_MIN, MIN(pulse, ESC_PWM_MAX));

	// Set the compare value for the channel
	__HAL_TIM_SET_COMPARE(htim, channel, pulse);
}

/**
 * Set throttle for all 4 motors (0.0 to 1.0)
 */
void ESC_PWM_SetThrottle(TIM_HandleTypeDef *htim, float throttle1, float throttle2, float throttle3, float throttle4)
{
	if (htim == NULL)
		return;

	// Clamp throttle values
	throttle1 = MAX(0.0f, MIN(throttle1, 1.0f));
	throttle2 = MAX(0.0f, MIN(throttle2, 1.0f));
	throttle3 = MAX(0.0f, MIN(throttle3, 1.0f));
	throttle4 = MAX(0.0f, MIN(throttle4, 1.0f));

	// Convert throttle (0.0-1.0) to pulse width (1000-2000us)
	uint16_t pulse1_us = (uint16_t)(ESC_PWM_MIN_US + (ESC_PWM_MAX_US - ESC_PWM_MIN_US) * throttle1);
	uint16_t pulse2_us = (uint16_t)(ESC_PWM_MIN_US + (ESC_PWM_MAX_US - ESC_PWM_MIN_US) * throttle2);
	uint16_t pulse3_us = (uint16_t)(ESC_PWM_MIN_US + (ESC_PWM_MAX_US - ESC_PWM_MIN_US) * throttle3);
	uint16_t pulse4_us = (uint16_t)(ESC_PWM_MIN_US + (ESC_PWM_MAX_US - ESC_PWM_MIN_US) * throttle4);

	// Set PWM for each motor
	ESC_PWM_SetPulse_us(htim, ESC_TIMER_CH1, pulse1_us);
	ESC_PWM_SetPulse_us(htim, ESC_TIMER_CH2, pulse2_us);
	ESC_PWM_SetPulse_us(htim, ESC_TIMER_CH3, pulse3_us);
	ESC_PWM_SetPulse_us(htim, ESC_TIMER_CH4, pulse4_us);
}

/**
 * Calibrate ESCs - ESCs must be calibrated before use
 * Procedure: Send max throttle (2000us), then min throttle (1000us)
 */
void ESC_PWM_Calibrate(TIM_HandleTypeDef *htim, uint32_t duration_ms)
{
	if (htim == NULL)
		return;

	// Step 1: Send maximum throttle (2000us) for calibration
	ESC_PWM_SetThrottle(htim, 1.0f, 1.0f, 1.0f, 1.0f);
	HAL_Delay(duration_ms);

	// Step 2: Send minimum throttle (1000us) for calibration
	ESC_PWM_SetThrottle(htim, 0.0f, 0.0f, 0.0f, 0.0f);
	HAL_Delay(duration_ms);

	// After calibration, ESCs should be ready to receive commands
	// Set to neutral (1500us) before starting
	ESC_PWM_SetThrottle(htim, 0.5f, 0.5f, 0.5f, 0.5f);
	HAL_Delay(500);
}
