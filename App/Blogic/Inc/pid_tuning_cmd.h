/*
 * pid_tuning_cmd.h
 *
 *  Created on: Apr 26, 2026
 *      Author: dalya
 *  Purpose: UART command handler for PID tuning
 */

#ifndef INC_PID_TUNING_CMD_H_
#define INC_PID_TUNING_CMD_H_

#include "stm32f4xx_hal.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialize PID tuning command handler
 * @param uart_handle UART handle for receiving commands
 */
void pid_tuning_cmd_init(UART_HandleTypeDef *uart_handle);

/**
 * @brief Process received character (call from UART RX interrupt)
 * @param data Received byte
 */
void pid_tuning_cmd_process_char(uint8_t data);

/**
 * @brief Main command processing function (call regularly from main loop)
 */
void pid_tuning_cmd_update(void);

/**
 * @brief Print current PID gains to UART
 */
void pid_tuning_cmd_print_gains(void);

/**
 * @brief Print help message to UART
 */
void pid_tuning_cmd_print_help(void);

#ifdef __cplusplus
}
#endif

#endif /* INC_PID_TUNING_CMD_H_ */
