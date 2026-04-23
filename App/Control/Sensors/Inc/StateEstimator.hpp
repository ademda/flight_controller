/*
 * StateEstimator.hpp
 *
 *  Created on: Apr 15, 2026
 *      Author: dalya
 */

#ifndef CONTROL_SENSORS_INC_STATEESTIMATOR_HPP_
#define CONTROL_SENSORS_INC_STATEESTIMATOR_HPP_

#include "Filter.hpp"
#include "Barometer.hpp"
#include "IMU.hpp"
#include "Magnetometer.hpp"

/**
 * @class StateEstimator
 * @brief Fuses sensor data from IMU, barometer, and magnetometer to estimate drone state
 * 
 * This class combines measurements from multiple sensors:
 * - IMU: Provides acceleration and angular velocity
 * - Barometer: Provides altitude and vertical velocity
 * - Magnetometer: Provides heading/yaw angle
 * - Filter: Applies filtering to sensor measurements for noise reduction
 */
class StateEstimator {
private:
    Filter* filter;              // Low-pass or Kalman filter for sensor fusion
    Barometer* barometer;        // Altitude and temperature sensor
    IMU* imu;                    // Inertial measurement unit (accelerometer + gyroscope)
    Magnetometer* magnetometer;  // Heading/compass sensor
    
public:
    StateEstimator();
    ~StateEstimator();
    
    /**
     * @brief Initialize all sensors
     * @return true if all sensors initialized successfully
     */
    bool initializeSensors();
    
    /**
     * @brief Get filtered altitude reading
     * @return Estimated altitude in meters
     */
    float getAltitude() const;
    
    /**
     * @brief Get estimated heading
     * @return Heading angle in degrees (0-360)
     */
    float getHeading() const;
    
    /**
     * @brief Get accelerometer readings
     * @return Acceleration vector in g
     */
    Vector3D getAcceleration();
    
    /**
     * @brief Get gyroscope readings
     * @return Angular velocity vector in deg/s
     */
    Vector3D getAngularVelocity();
    
    /**
     * @brief Update state estimates with current sensor readings
     */
    void updateState();
    
    /**
     * @brief Get pointer to filter for advanced configuration
     * @return Pointer to Filter object
     */
    Filter* getFilter();
    
    /**
     * @brief Get pointer to barometer for advanced configuration
     * @return Pointer to Barometer object
     */
    Barometer* getBarometer();
    
    /**
     * @brief Get pointer to IMU for advanced configuration
     * @return Pointer to IMU object
     */
    IMU* getIMU();
    
    /**
     * @brief Get pointer to magnetometer for advanced configuration
     * @return Pointer to Magnetometer object
     */
    Magnetometer* getMagnetometer();
};

#endif /* CONTROL_SENSORS_INC_STATEESTIMATOR_HPP_ */
