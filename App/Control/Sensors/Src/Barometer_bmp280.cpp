/*
 * Barometer_bmp280.cpp
 *
 *  Created on: Apr 15, 2026
 *      Author: dalya
 */

#include "Barometer_bmp280.hpp"

#include <math.h>

// Standard sea level pressure in Pa
#define SEA_LEVEL_PRESSURE 101325

Barometer_bmp280::Barometer_bmp280(BMP280_Handle_t *handle, I2C_HandleTypeDef *hi2c) 
: sea_level_pressure(SEA_LEVEL_PRESSURE), _handle(handle), _hi2c(hi2c) {
}

Barometer_bmp280::~Barometer_bmp280() {
}

bool Barometer_bmp280::init() {
    BMP280_Init(_handle, _hi2c);
    return false;
}

float Barometer_bmp280::readPressure() {
    return _handle->pressure;
}

float Barometer_bmp280::readTemperature() {
    return _handle->temperature;
}

float Barometer_bmp280::readAltitude() {
    return _handle->altitude;
}

void Barometer_bmp280::readData() {
    BMP280_Start_Reading(_handle);
}
