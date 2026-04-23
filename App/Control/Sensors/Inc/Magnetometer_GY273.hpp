/*
 * Magnetometer_GY273.hpp
 *
 *  Created on: Apr 15, 2026
 *      Author: dalya
 */

#ifndef CONTROL_SENSORS_INC_MAGNETOMETER_GY273_HPP_
#define CONTROL_SENSORS_INC_MAGNETOMETER_GY273_HPP_

#include "Magnetometer.hpp"

class Magnetometer_GY273 : public Magnetometer {
private:
    MagneticField offset;  // Magnetic field offset for calibration
    float scale;           // Scale factor for calibration
    
public:
    Magnetometer_GY273();
    virtual ~Magnetometer_GY273();
    
    /**
     * @brief Initialize GY273 (HMC5883L) sensor
     * @return true if initialization successful
     */
    virtual bool init() override;
    
    /**
     * @brief Read magnetic field values from GY273
     * @return Magnetic field vector in uT
     */
    virtual MagneticField readMagneticField() override;
    
    /**
     * @brief Calculate heading from magnetic field
     * @param magField Magnetic field vector
     * @return Heading angle in degrees (0-360)
     */
    virtual float calculateHeading(MagneticField magField) override;
    
    /**
     * @brief Calibrate GY273 magnetometer
     * @return true if calibration successful
     */
    virtual bool calibrate() override;
};

#endif /* CONTROL_SENSORS_INC_MAGNETOMETER_GY273_HPP_ */
