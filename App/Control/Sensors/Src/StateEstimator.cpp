/*
 * StateEstimator.cpp
 *
 *  Created on: Apr 15, 2026
 *      Author: dalya
 */

#include "../Inc/StateEstimator.hpp"

StateEstimator::StateEstimator() : filter(nullptr), barometer(nullptr), imu(nullptr), magnetometer(nullptr) {
}

StateEstimator::~StateEstimator() {
    // Cleanup is handled by whoever created these sensor objects
}

bool StateEstimator::initializeSensors() {
    bool success = true;
    
    if (imu != nullptr) {
        if (!imu->init()) {
            success = false;
        }
    }
    
    if (barometer != nullptr) {
        if (!barometer->init()) {
            success = false;
        }
    }
    
    if (magnetometer != nullptr) {
        if (!magnetometer->init()) {
            success = false;
        }
    }
    
    return success;
}

float StateEstimator::getAltitude() const {
    if (barometer == nullptr) {
        return 0.0f;
    }
    
    float pressure = barometer->readPressure();
    return barometer->readAltitude();
}

float StateEstimator::getHeading() const {
    if (magnetometer == nullptr) {
        return 0.0f;
    }
    
    MagneticField field = magnetometer->readMagneticField();
    return magnetometer->calculateHeading(field);
}

Vector3D StateEstimator::getAcceleration() {
    if (imu == nullptr) {
        return {0, 0, 0};
    }
    
    return imu->readAccelerometer();
}

Vector3D StateEstimator::getAngularVelocity() {
    if (imu == nullptr) {
        return {0, 0, 0};
    }
    
    return imu->readGyroscope();
}

void StateEstimator::updateState() {
    // Read all sensors and update state estimates
    if (imu != nullptr) {
        Vector3D accel = imu->readAccelerometer();
        Vector3D gyro = imu->readGyroscope();
        
        // TODO: Apply filter and sensor fusion algorithms
        if (filter != nullptr) {
            // Example: Filter acceleration data
            // accel.x = filter->apply(accel.x);
        }
    }
    
    if (barometer != nullptr) {
        float pressure = barometer->readPressure();
        float temperature = barometer->readTemperature();
        float altitude = barometer->readAltitude();
        
        // TODO: Use altitude for vertical state estimation
    }
    
    if (magnetometer != nullptr) {
        MagneticField field = magnetometer->readMagneticField();
        float heading = magnetometer->calculateHeading(field);
        
        // TODO: Use heading for yaw state estimation
    }
}

Filter* StateEstimator::getFilter() {
    return filter;
}

Barometer* StateEstimator::getBarometer() {
    return barometer;
}

IMU* StateEstimator::getIMU() {
    return imu;
}

Magnetometer* StateEstimator::getMagnetometer() {
    return magnetometer;
}
