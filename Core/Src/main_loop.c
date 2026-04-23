/*
 * main_loop.c
 * Main control loop - runs at 100Hz from TIM2 interrupt
 *
 *  Created on: Apr 16, 2026
 */

#include "main_loop.h"
#include "stm32f1xx_hal.h"

// Extern functions from C++ layer
extern void FlightController_Update(float dt);

/**
 * Main control loop - called from TIM2 interrupt at 100Hz (every 10ms)
 */
void MainLoop_Update(void)
{
	// Execute flight controller at 100Hz with 0.01s time step
	FlightController_Update(CONTROL_LOOP_DT);
}

/**
 * TIM2 Interrupt Handler - fires at 1000Hz
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim->Instance == TIM2)
	{
		MainLoop_Update();
	}
}
