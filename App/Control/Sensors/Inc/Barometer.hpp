/*
 * Barometer.hpp
 *
 *  Created on: Apr 15, 2026
 *      Author: dalya
 */

#ifndef CONTROL_SENSORS_INC_BAROMETER_HPP_
#define CONTROL_SENSORS_INC_BAROMETER_HPP_

class Barometer {
public:
    Barometer();
    virtual ~Barometer();
    
    /**
     * @brief Initialize barometer sensor
     * @return true if initialization successful, false otherwise
     */
    virtual bool init() = 0;
    
    /**
     * @brief Read pressure from sensor
     * @return Pressure value in Pa
     */
    virtual float readPressure() = 0;
    
    /**
     * @brief Read temperature from sensor
     * @return Temperature value in Celsius
     */
    virtual float readTemperature() = 0;
    
    /**
     * @brief Calculate altitude from pressure
     * @param pressure Pressure value in Pa
     * @return Altitude in meters
     */
    virtual float readAltitude() = 0;

    virtual void readData() = 0;
};

#endif /* CONTROL_SENSORS_INC_BAROMETER_HPP_ */
