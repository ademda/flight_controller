/*
 * sbus_rx.c
 *
 *  Low-level iBUS UART reception driver
 *  Handles DMA-based reception of iBUS frames
 *  Protocol validation is done in IBUSReceiver class
 *
 *  Created on: Apr 15, 2026
 *      Author: dalya
 */

#include "sbus_rx.h"
#include <string.h>

/* Static buffer for DMA reception */
static uint8_t ibus_dma_buffer[IBUS_FRAME_LENGTH] = {0};
static UART_HandleTypeDef* p_uart_handle = NULL;


/**
 * @brief Initialize iBUS UART reception
 * @param huart: UART handle pointer
 */
void ibus_uart_init(UART_HandleTypeDef* huart)
{
	if (huart == NULL) {
		return;
	}
	
	p_uart_handle = huart;
	
	/* Start DMA reception on UART */
	HAL_UART_Receive_DMA(p_uart_handle, ibus_dma_buffer, IBUS_FRAME_LENGTH);
}


/**
 * @brief Get pointer to DMA buffer
 * @return Pointer to iBUS frame buffer
 */
uint8_t* ibus_get_buffer(void)
{
	return ibus_dma_buffer;
}


/**
 * @brief Called from HAL_UART_RxCpltCallback in stm32f1xx_it.c
 * @note Restart DMA after each complete frame reception
 */
void ibus_uart_dma_complete_callback(void)
{
	if (p_uart_handle != NULL) {
		/* Restart DMA for continuous reception */
		HAL_UART_Receive_DMA(p_uart_handle, ibus_dma_buffer, IBUS_FRAME_LENGTH);
	}
}


