/*
 * hmc5883l.c
 *
 *  Created on: Apr 26, 2026
 *  HMC5883L 3-Axis Magnetometer (GY273 module)
 *  Interrupt mode I2C reading
 */

#include "hmc5883l.h"
#include <math.h>

// Conversion factor: 1 Gauss = 100 microTesla
// Using default gain of ±1.3 Gauss (1100 LSB/Gauss)
static const float HMC5883L_LSB_PER_GAUSS = 1100.0f;

HMC5883L_Handle_t *g_hmc5883l_handle = NULL;

HAL_StatusTypeDef HMC5883L_Init(HMC5883L_Handle_t *handle, I2C_HandleTypeDef *hi2c, uint8_t addr) {
	if (handle == NULL || hi2c == NULL) return HAL_ERROR;
	
	handle->hi2c = hi2c;
	handle->i2c_addr = (addr << 1);  // Convert 7-bit to 8-bit address
	handle->state = HMC5883L_STATE_INIT;
	
	// Initialize calibration values (no calibration by default)
	handle->offset_x = 0.0f;
	handle->offset_y = 0.0f;
	handle->offset_z = 0.0f;
	handle->scale_x = 1.0f;
	handle->scale_y = 1.0f;
	handle->scale_z = 1.0f;
	
	g_hmc5883l_handle = handle;
	
	// Configure HMC5883L
	uint8_t config_a = 0x70;  // 8 samples averaged, 15Hz output rate, normal measurement
	uint8_t config_b = HMC5883L_GAIN_1370;  // ±1.3 Gauss default
	uint8_t mode = HMC5883L_MODE_CONTINUOUS;  // Continuous measurement
	
	// Write Config A using blocking call (initialization only)
	HAL_StatusTypeDef status = HAL_I2C_Mem_Write(hi2c, handle->i2c_addr, 
		HMC5883L_REG_CONFIG_A, I2C_MEMADD_SIZE_8BIT, &config_a, 1, 1000);
	if (status != HAL_OK) return status;
	
	// Write Config B
	status = HAL_I2C_Mem_Write(hi2c, handle->i2c_addr, 
		HMC5883L_REG_CONFIG_B, I2C_MEMADD_SIZE_8BIT, &config_b, 1, 1000);
	if (status != HAL_OK) return status;
	
	// Write Mode
	status = HAL_I2C_Mem_Write(hi2c, handle->i2c_addr, 
		HMC5883L_REG_MODE, I2C_MEMADD_SIZE_8BIT, &mode, 1, 1000);
	if (status != HAL_OK) return status;
	
	handle->state = HMC5883L_STATE_READY;
	return HAL_OK;
}

// Parse received I2C data
static void HMC5883L_Parse_Data(HMC5883L_Handle_t *handle) {
	uint8_t *data = handle->rx_buff;
	
	// Combine bytes into 16-bit values (big-endian)
	// Data format: X_H, X_L, Z_H, Z_L, Y_H, Y_L
	handle->mag_x_raw = (int16_t)((data[0] << 8) | data[1]);
	handle->mag_z_raw = (int16_t)((data[2] << 8) | data[3]);
	handle->mag_y_raw = (int16_t)((data[4] << 8) | data[5]);
	
	// Convert to Gauss using default gain and apply calibration
	handle->mag_x = (handle->mag_x_raw / HMC5883L_LSB_PER_GAUSS - handle->offset_x) * handle->scale_x;
	handle->mag_y = (handle->mag_y_raw / HMC5883L_LSB_PER_GAUSS - handle->offset_y) * handle->scale_y;
	handle->mag_z = (handle->mag_z_raw / HMC5883L_LSB_PER_GAUSS - handle->offset_z) * handle->scale_z;
}

// Start reading sensor data in interrupt mode
HAL_StatusTypeDef HMC5883L_Start_Read(HMC5883L_Handle_t *handle) {
	if (handle == NULL || handle->state != HMC5883L_STATE_READY) {
		return HAL_ERROR;
	}
	
	handle->state = HMC5883L_STATE_READING_DATA;
	handle->tx_buff[0] = HMC5883L_REG_DATA_X_H;  // Start register address
	
	// Send register address and request data (interrupt mode)
	HAL_StatusTypeDef status = HAL_I2C_Mem_Read_IT(handle->hi2c, handle->i2c_addr,
		HMC5883L_REG_DATA_X_H, I2C_MEMADD_SIZE_8BIT, handle->rx_buff, 6);
	
	if (status != HAL_OK) {
		handle->state = HMC5883L_STATE_ERROR;
	}
	
	return status;
}

// I2C receive complete callback (called from HAL)
void HMC5883L_I2C_RxCpltCallback(HMC5883L_Handle_t *handle) {
	if (handle == NULL) return;
	
	// Parse the received data
	HMC5883L_Parse_Data(handle);
	
	// Update state back to ready
	handle->state = HMC5883L_STATE_READY;
	
	// Immediately start reading again (continuous polling)
	HMC5883L_Start_Read(handle);
}

HAL_StatusTypeDef HMC5883L_GetData(HMC5883L_Handle_t *handle, float *x, float *y, float *z) {
	if (handle == NULL) return HAL_ERROR;
	
	if (x != NULL) *x = handle->mag_x;
	if (y != NULL) *y = handle->mag_y;
	if (z != NULL) *z = handle->mag_z;
	
	return HAL_OK;
}

float HMC5883L_GetHeading(float x, float y) {
	// Calculate heading using arctangent of Y/X
	float heading_rad = atan2f(y, x);
	
	// Convert from radians to degrees
	float heading = heading_rad * 180.0f / M_PI;
	
	// Normalize to 0-360 range
	if (heading < 0) {
		heading += 360.0f;
	}
	
	return heading;
}
