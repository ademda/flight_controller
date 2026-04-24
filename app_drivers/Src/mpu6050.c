/*
 * mpu6050.c
 *
 *  Created on: Apr 15, 2026
 *      Author: dalya
 */

#include "mpu6050.h"
#include <math.h>

MPU6050_Handle_t *g_mpu6050_handle = NULL;

// Forward declarations
void MPU6050_Parse_Data(MPU6050_Handle_t *handle);
static void MPU6050_Configure(MPU6050_Handle_t *handle);

// Initialize MPU6050 with interrupt mode
void MPU6050_Init(MPU6050_Handle_t *handle, I2C_HandleTypeDef *hi2c, uint8_t i2c_addr)
{
	handle->hi2c = hi2c;
	handle->i2c_addr = i2c_addr;
	handle->state = MPU6050_STATE_INIT;
	handle->data_ready_callback = NULL;
	
	// Set default scale factors
	handle->accel_scale = 1.0f / 16384.0f;  // ±2g range
	handle->gyro_scale = 1.0f / 131.0f;     // ±250°/s range
	
	// Initialize calibration offsets
	handle->accel_offset_x = 0;
	handle->accel_offset_y = 0;
	handle->accel_offset_z = 0;
	handle->gyro_offset_x = 0;
	handle->gyro_offset_y = 0;
	handle->gyro_offset_z = 0;
	
	g_mpu6050_handle = handle;
	
	// Wake up MPU6050 (disable sleep mode)
	uint8_t pwr_mgmt[2] = {MPU6050_REG_PWR_MGMT_1, 0x00};
	HAL_I2C_Master_Transmit(handle->hi2c, handle->i2c_addr, pwr_mgmt, 2, 1000);
	
	// Configure the sensor
	MPU6050_Configure(handle);
	
	handle->state = MPU6050_STATE_READY;
}

// Configure MPU6050 registers
static void MPU6050_Configure(MPU6050_Handle_t *handle)
{
	// Set config register (DLPF, sampling rate)
	uint8_t config[2] = {MPU6050_REG_CONFIG, 0x00};  // No DLPF
	HAL_I2C_Master_Transmit(handle->hi2c, handle->i2c_addr, config, 2, 1000);
	
	// Set gyro config (±250°/s)
	uint8_t gyro_config[2] = {MPU6050_REG_GYRO_CONFIG, 0x00};
	HAL_I2C_Master_Transmit(handle->hi2c, handle->i2c_addr, gyro_config, 2, 1000);
	
	// Set accel config (±2g)
	uint8_t accel_config[2] = {MPU6050_REG_ACCEL_CONFIG, 0x00};
	HAL_I2C_Master_Transmit(handle->hi2c, handle->i2c_addr, accel_config, 2, 1000);
}

// Start reading sensor data
void MPU6050_Start_Reading(MPU6050_Handle_t *handle)
{
	if (handle->state == MPU6050_STATE_READY)
	{
		handle->state = MPU6050_STATE_READING_DATA;
		handle->tx_buff[0] = MPU6050_REG_ACCEL_XOUT_H;
		HAL_I2C_Master_Transmit_IT(handle->hi2c, handle->i2c_addr, handle->tx_buff, 1);
	}
}

// Parse raw I2C data and convert to sensor values
void MPU6050_Parse_Data(MPU6050_Handle_t *handle)
{
	uint8_t *rx = handle->rx_buff;
	
	// Extract raw values (big-endian)
	handle->accel_x_raw = (int16_t)((rx[0] << 8) | rx[1]);
	handle->accel_y_raw = (int16_t)((rx[2] << 8) | rx[3]);
	handle->accel_z_raw = (int16_t)((rx[4] << 8) | rx[5]);
	handle->temp_raw = (int16_t)((rx[6] << 8) | rx[7]);
	handle->gyro_x_raw = (int16_t)((rx[8] << 8) | rx[9]);
	handle->gyro_y_raw = (int16_t)((rx[10] << 8) | rx[11]);
	handle->gyro_z_raw = (int16_t)((rx[12] << 8) | rx[13]);
	
	// Apply calibration offsets and scale factors
	handle->accel_x = (handle->accel_x_raw - handle->accel_offset_x) * handle->accel_scale;
	handle->accel_y = (handle->accel_y_raw - handle->accel_offset_y) * handle->accel_scale;
	handle->accel_z = (handle->accel_z_raw - handle->accel_offset_z) * handle->accel_scale;
	
	handle->gyro_x = (handle->gyro_x_raw - handle->gyro_offset_x) * handle->gyro_scale;
	handle->gyro_y = (handle->gyro_y_raw - handle->gyro_offset_y) * handle->gyro_scale;
	handle->gyro_z = (handle->gyro_z_raw - handle->gyro_offset_z) * handle->gyro_scale;
	
	// Temperature: 35°C = 0, +0.00294°C / LSB
	handle->temperature = (handle->temp_raw / 340.0f) + 36.53f;
	
	// Calculate roll and pitch from accelerometer (in degrees)
	handle->roll = atan2f(handle->accel_y, handle->accel_z) * 180.0f / 3.14159265359f;
	handle->pitch = atan2f(-handle->accel_x, sqrtf(handle->accel_y * handle->accel_y + handle->accel_z * handle->accel_z)) * 180.0f / 3.14159265359f;
}



// Calibration function - collects samples to compute offset values
void MPU6050_Calibrate(MPU6050_Handle_t *handle, uint16_t num_samples)
{
	// Accumulation variables
	int32_t accel_x_sum = 0, accel_y_sum = 0, accel_z_sum = 0;
	int32_t gyro_x_sum = 0, gyro_y_sum = 0, gyro_z_sum = 0;
	
	// Collect samples
	for (uint16_t i = 0; i < num_samples; i++)
	{
		// Trigger a read
		MPU6050_Start_Reading(handle);
		
		// Wait for data to be read (blocking - replace with proper waiting if needed)
		uint32_t timeout = 10000;
		while (handle->state != MPU6050_STATE_READY && timeout > 0)
		{
			timeout--;
		}
		
		// Accumulate raw values
		accel_x_sum += handle->accel_x_raw;
		accel_y_sum += handle->accel_y_raw;
		accel_z_sum += handle->accel_z_raw;
		gyro_x_sum += handle->gyro_x_raw;
		gyro_y_sum += handle->gyro_y_raw;
		gyro_z_sum += handle->gyro_z_raw;
		
		// Small delay between samples
		for (uint32_t delay = 0; delay < 50000; delay++) {}
	}
	
	// Calculate averages and store as offsets
	handle->accel_offset_x = (int16_t)(accel_x_sum / num_samples);
	handle->accel_offset_y = (int16_t)(accel_y_sum / num_samples);
	handle->accel_offset_z = (int16_t)(accel_z_sum / num_samples);
	handle->gyro_offset_x = (int16_t)(gyro_x_sum / num_samples);
	handle->gyro_offset_y = (int16_t)(gyro_y_sum / num_samples);
	handle->gyro_offset_z = (int16_t)(gyro_z_sum / num_samples);
}
