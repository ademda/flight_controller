/*
 * bmp280.c
 *
 *  Created on: Apr 15, 2026
 *      Author: dalya
 */

#include "bmp280.h"
#include <math.h>

static BMP280_Handle_t *g_bmp280_handle = NULL;


// Initialize BMP280 with interrupt mode
void BMP280_Init(BMP280_Handle_t *handle, I2C_HandleTypeDef *hi2c)
{
	handle->hi2c = hi2c;
	handle->state = BMP280_STATE_INIT;
	handle->data_ready_callback = NULL;
	
	g_bmp280_handle = handle;
	
	// Write configuration registers to start reading calibration data
	handle->tx_buff[0] = 0x88;  // Start address for calibration
	HAL_I2C_Master_Transmit_IT(handle->hi2c, BMP280_I2C_ADDR, handle->tx_buff, 1);
}

// Start reading sensor data
void BMP280_Start_Reading(BMP280_Handle_t *handle)
{
	if (handle->state == BMP280_STATE_READY)
	{
		handle->state = BMP280_STATE_READING_DATA;
		handle->tx_buff[0] = BMP280_REG_DATA;
		HAL_I2C_Master_Transmit_IT(handle->hi2c, BMP280_I2C_ADDR, handle->tx_buff, 1);
	}
}

// Main process function - call from main loop
void BMP280_Process(BMP280_Handle_t *handle)
{
	// State machine is driven by I2C callbacks
	// This function can be used for any polling-based checks if needed
}

// I2C Transmit complete callback
void BMP280_I2C_TxCpltCallback(BMP280_Handle_t *handle)
{
	if (handle->state == BMP280_STATE_INIT)
	{
		// After sending calibration address, read calibration data
		HAL_I2C_Master_Receive_IT(handle->hi2c, BMP280_I2C_ADDR | 0x01, handle->rx_buff, BMP280_CALIB_SIZE);
	}
	else if (handle->state == BMP280_STATE_READING_DATA)
	{
		// After sending data address, read sensor data
		HAL_I2C_Master_Receive_IT(handle->hi2c, BMP280_I2C_ADDR | 0x01, handle->rx_buff, BMP280_DATA_SIZE);
	}
}

// I2C Receive complete callback
void BMP280_I2C_RxCpltCallback(BMP280_Handle_t *handle)
{
	if (handle->state == BMP280_STATE_INIT)
	{
		// Calibration data received, parse it
		BMP280_Read_Calibration(handle);
		
		// Configure BMP280
		handle->tx_buff[0] = 0xF5;
		HAL_I2C_Master_Transmit_IT(handle->hi2c, BMP280_I2C_ADDR, handle->tx_buff, 1);
		
		// Write config register
		uint8_t config_buff[2] = {0xF5, 0b10010000};  // standby 500ms, filter 16
		HAL_I2C_Master_Transmit(handle->hi2c, BMP280_I2C_ADDR, config_buff, 2, 1000);
		
		// Write control measure register
		uint8_t ctrl_buff[2] = {0xF4, 0b01010111};  // osrs_t x2, osrs_p x16, normal mode
		HAL_I2C_Master_Transmit(handle->hi2c, BMP280_I2C_ADDR, ctrl_buff, 2, 1000);
		
		handle->state = BMP280_STATE_READY;
	}
	else if (handle->state == BMP280_STATE_READING_DATA)
	{
		// Sensor data received, calculate values
		BMP280_Calculate_Values(handle);
		handle->state = BMP280_STATE_READY;
		
		// Call user callback if registered
		if (handle->data_ready_callback)
		{
			handle->data_ready_callback();
		}
	}
}

// Read and parse calibration data from RX buffer
static void BMP280_Read_Calibration(BMP280_Handle_t *handle)
{
	uint8_t *rx_buff = handle->rx_buff;
	
	handle->dig_T1 = (rx_buff[0]) + (rx_buff[1] << 8);
	handle->dig_T2 = (rx_buff[2]) + (rx_buff[3] << 8);
	handle->dig_T3 = (rx_buff[4]) + (rx_buff[5] << 8);
	handle->dig_P1 = (rx_buff[6]) + (rx_buff[7] << 8);
	handle->dig_P2 = (rx_buff[8]) + (rx_buff[9] << 8);
	handle->dig_P3 = (rx_buff[10]) + (rx_buff[11] << 8);
	handle->dig_P4 = (rx_buff[12]) + (rx_buff[13] << 8);
	handle->dig_P5 = (rx_buff[14]) + (rx_buff[15] << 8);
	handle->dig_P6 = (rx_buff[16]) + (rx_buff[17] << 8);
	handle->dig_P7 = (rx_buff[18]) + (rx_buff[19] << 8);
	handle->dig_P8 = (rx_buff[20]) + (rx_buff[21] << 8);
	handle->dig_P9 = (rx_buff[22]) + (rx_buff[23] << 8);
}

// Calculate temperature and pressure from raw data
static void BMP280_Calculate_Values(BMP280_Handle_t *handle)
{
	uint8_t *rx_buff = handle->rx_buff;
	
	// Extract pressure raw value (first 3 bytes)
	volatile uint32_t temp[3];
	temp[2] = rx_buff[0];
	temp[1] = rx_buff[1];
	temp[0] = rx_buff[2];
	handle->pressure_raw = (temp[2] << 12) + (temp[1] << 4) + (temp[0] >> 4);
	
	// Extract temperature raw value (last 3 bytes)
	temp[2] = rx_buff[3];
	temp[1] = rx_buff[4];
	temp[0] = rx_buff[5];
	handle->temperature_raw = (temp[2] << 12) + (temp[1] << 4) + (temp[0] >> 4);
	
	// Temperature calculation
	double var1 = (((double)handle->temperature_raw) / 16384.0 - ((double)handle->dig_T1) / 1024.0) * ((double)handle->dig_T2);
	double var2 = ((((double)handle->temperature_raw) / 131072.0 - ((double)handle->dig_T1) / 8192.0) * 
	               (((double)handle->temperature_raw) / 131072.0 - ((double)handle->dig_T1) / 8192.0)) * ((double)handle->dig_T3);
	double t_fine = (int32_t)(var1 + var2);
	handle->temperature = (var1 + var2) / 5120.0;
	
	// Pressure calculation
	var1 = ((double)t_fine / 2.0) - 64000.0;
	var2 = var1 * var1 * ((double)handle->dig_P6) / 32768.0;
	var2 = var2 + var1 * ((double)handle->dig_P5) * 2.0;
	var2 = (var2 / 4.0) + (((double)handle->dig_P4) * 65536.0);
	var1 = (((double)handle->dig_P3) * var1 * var1 / 524288.0 + ((double)handle->dig_P2) * var1) / 524288.0;
	var1 = (1.0 + var1 / 32768.0) * ((double)handle->dig_P1);
	volatile double p = 1048576.0 - (double)handle->pressure_raw;
	p = (p - (var2 / 4096.0)) * 6250.0 / var1;
	var1 = ((double)handle->dig_P9) * p * p / 2147483648.0;
	var2 = p * ((double)handle->dig_P8) / 32768.0;
	handle->pressure = p + (var1 + var2 + ((double)handle->dig_P7)) / 16.0;
	
	// Altitude calculation
	handle->altitude = 44330.0f * (1 - powf(handle->pressure / 101325.0f, 1.0f / 5.255f));
}

void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef *hi2c)
{
	if (g_bmp280_handle && hi2c == g_bmp280_handle->hi2c)
	{
		BMP280_I2C_TxCpltCallback(g_bmp280_handle);
	}
}

void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef *hi2c)
{
	if (g_bmp280_handle && hi2c == g_bmp280_handle->hi2c)
	{
		BMP280_I2C_RxCpltCallback(g_bmp280_handle);
	}
}

