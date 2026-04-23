/*
 * IMU.hpp
 *
 *  Created on: Apr 15, 2026
 *      Author: dalya
 */

#ifndef CONTROL_SENSORS_INC_IMU_HPP_
#define CONTROL_SENSORS_INC_IMU_HPP_

typedef struct {
    float x;
    float y;
    float z;
} Vector3D;

class IMU {
public:
    IMU();
    virtual ~IMU();
    
    /**
     * @brief Initialize IMU sensor
     * @return true if initialization successful, false otherwise
     */
    virtual bool init() = 0;
    
    /**
     * @brief Read accelerometer values
     * @return Acceleration vector in g
     */
    virtual Vector3D readAccelerometer() = 0;
    
    /**
     * @brief Read gyroscope values
     * @return Angular velocity vector in deg/s
     */
    virtual Vector3D readGyroscope() = 0;
    
    /**
     * @brief Calibrate IMU sensors
     * @return true if calibration successful, false otherwise
     */
    virtual float readRoll() = 0;
    
    virtual float readPitch() = 0;

    virtual bool calibrate() = 0;

    virtual void readData() = 0;
};

#endif /* CONTROL_SENSORS_INC_IMU_HPP_ */
