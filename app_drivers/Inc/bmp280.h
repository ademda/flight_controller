/*
 * bmp280.h
 *
 *  Created on: Apr 15, 2026
 *      Author: dalya
 */

#ifndef INC_BMP280_H_
#define INC_BMP280_H_

#include "stm32f4xx_hal.h"
#include <stdint.h>

#define BMP280_CHIP_ID 0x58
#define BMP280_SPI_MASK_WRITE 0b01111111

#define BMP280_REG_ID         0xD0
#define BMP280_REG_RESET      0xE0
#define BMP280_REG_STATUS	  0xF3
#define BMP280_REG_CTRL_MEAS  0xF4
#define BMP280_REG_CONFIG     0xF5
#define BMP280_REG_PRESS      0xF7
#define BMP280_REG_TEMP       0xFA
#define BMP280_REG_CTRL       0xF4
#define BMP280_REG_CALIB      0x88
#define BMP280_REG_DATA       0xF7

#define BMP280_RESET_VALUE    0xB6
#define BMP280_I2C_ADDR       0x76 << 1  // 7-bit address shifted for HAL
#define BMP280_CALIB_SIZE     24
#define BMP280_DATA_SIZE      6

typedef enum {
	BMP280_STATE_INIT,
	BMP280_STATE_READ_CALIB,
	BMP280_STATE_READY,
	BMP280_STATE_READING_DATA,
	BMP280_STATE_ERROR
} BMP280_State_t;

typedef struct {
	I2C_HandleTypeDef *hi2c;
	BMP280_State_t state;
	
	// Calibration values
	int16_t dig_T1, dig_T2, dig_T3;
	int16_t dig_P1, dig_P2, dig_P3, dig_P4, dig_P5, dig_P6, dig_P7, dig_P8, dig_P9;
	
	// Sensor data
	int32_t temperature_raw;
	int32_t pressure_raw;
	float temperature;
	float pressure;
	float altitude;
	
	// I2C buffers
	uint8_t rx_buff[24];
} BMP280_Handle_t;

// Function declarations
void BMP280_Init(BMP280_Handle_t *handle, I2C_HandleTypeDef *hi2c);
void BMP280_Start_Reading(BMP280_Handle_t *handle);
void BMP280_Read_Calibration(BMP280_Handle_t *handle);
void BMP280_Calculate_Values(BMP280_Handle_t *handle);
void BMP280_Process(BMP280_Handle_t *handle);
void BMP280_I2C_RxCpltCallback();

#endif /* INC_BMP280_H_ */
