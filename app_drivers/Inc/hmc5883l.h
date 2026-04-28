/*
 * hmc5883l.h
 *
 *  Created on: Apr 26, 2026
 *  HMC5883L 3-Axis Magnetometer (GY273 module)
 */

#ifndef INC_HMC5883L_H_
#define INC_HMC5883L_H_

#include "stm32f4xx_hal.h"
#include <stdint.h>

// HMC5883L I2C Address
#define HMC5883L_I2C_ADDR       0x1E    // 7-bit address, shifted: 0x3C

// Register Addresses
#define HMC5883L_REG_CONFIG_A   0x00
#define HMC5883L_REG_CONFIG_B   0x01
#define HMC5883L_REG_MODE       0x02
#define HMC5883L_REG_DATA_X_H   0x03    // X MSB
#define HMC5883L_REG_DATA_X_L   0x04    // X LSB
#define HMC5883L_REG_DATA_Z_H   0x05    // Z MSB
#define HMC5883L_REG_DATA_Z_L   0x06    // Z LSB
#define HMC5883L_REG_DATA_Y_H   0x07    // Y MSB
#define HMC5883L_REG_DATA_Y_L   0x08    // Y LSB
#define HMC5883L_REG_STATUS     0x09
#define HMC5883L_REG_ID_A       0x0A
#define HMC5883L_REG_ID_B       0x0B
#define HMC5883L_REG_ID_C       0x0C

// Mode Register Values
#define HMC5883L_MODE_CONTINUOUS   0x00
#define HMC5883L_MODE_SINGLE       0x01
#define HMC5883L_MODE_IDLE         0x02

// Gain Settings (uT per LSB)
#define HMC5883L_GAIN_1370  0x00  // ±1.3 Gauss, 1100 LSB/Gauss
#define HMC5883L_GAIN_1090  0x20  // ±1.0 Gauss, 1370 LSB/Gauss
#define HMC5883L_GAIN_820   0x40  // ±0.82 Gauss, 1700 LSB/Gauss
#define HMC5883L_GAIN_660   0x60  // ±0.66 Gauss, 2150 LSB/Gauss
#define HMC5883L_GAIN_440   0x80  // ±0.44 Gauss, 3200 LSB/Gauss
#define HMC5883L_GAIN_390   0xA0  // ±0.39 Gauss, 3600 LSB/Gauss
#define HMC5883L_GAIN_330   0xC0  // ±0.33 Gauss, 4700 LSB/Gauss
#define HMC5883L_GAIN_230   0xE0  // ±0.23 Gauss, 6800 LSB/Gauss

typedef enum {
	HMC5883L_STATE_INIT,
	HMC5883L_STATE_READY,
	HMC5883L_STATE_READING_DATA,
	HMC5883L_STATE_ERROR
} HMC5883L_State_t;

typedef struct {
	I2C_HandleTypeDef *hi2c;
	uint8_t i2c_addr;
	HMC5883L_State_t state;
	
	// I2C buffers for interrupt mode
	uint8_t tx_buff[1];
	uint8_t rx_buff[6];
	
	// Raw sensor data
	int16_t mag_x_raw, mag_y_raw, mag_z_raw;
	
	// Scaled sensor data (in Gauss)
	float mag_x, mag_y, mag_z;
	float yaw; float heading;
	// Calibration
	float offset_x, offset_y, offset_z;
	float scale_x, scale_y, scale_z;
} HMC5883L_Handle_t;

/**
 * @brief Initialize HMC5883L magnetometer
 * @param handle Pointer to HMC5883L handle
 * @param hi2c I2C handle
 * @param addr I2C address
 * @return HAL_OK if successful
 */
HAL_StatusTypeDef HMC5883L_Init(HMC5883L_Handle_t *handle, I2C_HandleTypeDef *hi2c, uint8_t addr);

/**
 * @brief Start reading raw magnetic field data (interrupt mode)
 * @param handle Pointer to HMC5883L handle
 * @return HAL_OK if successful
 */
HAL_StatusTypeDef HMC5883L_Start_Reading(HMC5883L_Handle_t *handle);

/**
 * @brief Get magnetic field in Gauss
 * @param handle Pointer to HMC5883L handle
 * @param x, y, z Pointers to store magnetometer values
 * @return HAL_OK if successful
 */
HAL_StatusTypeDef HMC5883L_GetData(HMC5883L_Handle_t *handle, float *x, float *y, float *z);

/**
 * @brief I2C receive complete callback (called from HAL)
 * @param handle Pointer to HMC5883L handle
 */
void HMC5883L_I2C_RxCpltCallback();
void HMC5883L_Parse_Data(HMC5883L_Handle_t *handle);
/**
 * @brief Calculate heading from magnetic field
 * @param x, y Magnetic field X and Y components
 * @return Heading in degrees (0-360)
 */
float HMC5883L_GetHeading(float x, float y);

#endif /* INC_HMC5883L_H_ */
