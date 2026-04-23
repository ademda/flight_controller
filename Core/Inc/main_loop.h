/*
 * main_loop.h
 * Main control loop management
 *
 *  Created on: Apr 16, 2026
 */

#ifndef MAIN_LOOP_H_
#define MAIN_LOOP_H_

// Control loop frequency (Hz)
#define CONTROL_LOOP_FREQ_HZ    1000
#define CONTROL_LOOP_DT         (1.0f / CONTROL_LOOP_FREQ_HZ)  // 0.01 seconds

/**
 * @brief Main control loop update - called from TIM2 interrupt at 100Hz
 */
void MainLoop_Update(void);

#endif /* MAIN_LOOP_H_ */
