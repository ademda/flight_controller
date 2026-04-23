/*
 * Magnetometer_GY273.cpp
 *
 *  Created on: Apr 15, 2026
 *      Author: dalya
 */

#include "../Inc/Magnetometer_GY273.hpp"
#include <math.h>

Magnetometer_GY273::Magnetometer_GY273() : offset({0, 0, 0}), scale(1.0f) {
}

Magnetometer_GY273::~Magnetometer_GY273() {
}

bool Magnetometer_GY273::init() {
    // TODO: Implement GY273 (HMC5883L) initialization via I2C
    return false;
}

MagneticField Magnetometer_GY273::readMagneticField() {
    MagneticField field = {0, 0, 0};
    // TODO: Read raw magnetic field data from GY273
    // TODO: Apply calibration offset and scale conversions
    return field;
}

float Magnetometer_GY273::calculateHeading(MagneticField magField) {
    // Calculate heading using arctangent of Y/X
    float heading_rad = atan2f(magField.y, magField.x);
    
    // Convert from radians to degrees
    float heading = heading_rad * 180.0f / M_PI;
    
    // Normalize to 0-360 range
    if (heading < 0) {
        heading += 360.0f;
    }
    
    return heading;
}

bool Magnetometer_GY273::calibrate() {
    // TODO: Implement calibration routine (rotate sensor 360 degrees)
    return false;
}
