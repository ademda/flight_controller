/*
 * Magnetometer.hpp
 *
 *  Created on: Apr 15, 2026
 *      Author: dalya
 */

#ifndef CONTROL_SENSORS_INC_MAGNETOMETER_HPP_
#define CONTROL_SENSORS_INC_MAGNETOMETER_HPP_

typedef struct {
    float x;
    float y;
    float z;
} MagneticField;

class Magnetometer {
public:
    Magnetometer();
    virtual ~Magnetometer();
    
    /**
     * @brief Initialize magnetometer sensor
     * @return true if initialization successful, false otherwise
     */
    virtual bool init() = 0;
    
    /**
     * @brief Read magnetic field values
     * @return Magnetic field vector in uT (microTesla)
     */
    virtual MagneticField readMagneticField() = 0;
    
    /**
     * @brief Calculate heading from magnetic field
     * @param magField Magnetic field vector
     * @return Heading angle in degrees (0-360)
     */
    virtual float calculateHeading(MagneticField magField) = 0;
    
    /**
     * @brief Calibrate magnetometer
     * @return true if calibration successful, false otherwise
     */
    virtual bool calibrate() = 0;
};

#endif /* CONTROL_SENSORS_INC_MAGNETOMETER_HPP_ */
