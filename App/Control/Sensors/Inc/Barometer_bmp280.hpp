/*
 * Barometer_bmp280.hpp
 *
 *  Created on: Apr 15, 2026
 *      Author: dalya
 */

#ifndef CONTROL_SENSORS_INC_BAROMETER_BMP280_HPP_
#define CONTROL_SENSORS_INC_BAROMETER_BMP280_HPP_

#include "Barometer.hpp"
extern "C" {
    #include "bmp280.h"
}
class Barometer_bmp280 : public Barometer {
private:
    float sea_level_pressure;  // Reference pressure for altitude calculation
    
public:
    Barometer_bmp280(BMP280_Handle_t *handle, I2C_HandleTypeDef *hi2c);
    virtual ~Barometer_bmp280();
    
    /**
     * @brief Initialize BMP280 sensor
     * @return true if initialization successful
     */
    virtual bool init() override;
    
    /**
     * @brief Read pressure from BMP280
     * @return Pressure value in Pa
     */
    virtual float readPressure() override;
    
    /**
     * @brief Read temperature from BMP280
     * @return Temperature value in Celsius
     */
    virtual float readTemperature() override;
    
    /**
     * @brief Calculate altitude from pressure
     * @param pressure Pressure value in Pa
     * @return Altitude in meters
     */
    virtual float readAltitude() override;

    virtual void readData() override;
    BMP280_Handle_t *_handle; 
    I2C_HandleTypeDef *_hi2c;
};

#endif /* CONTROL_SENSORS_INC_BAROMETER_BMP280_HPP_ */
