/*
 * MPU6050.hpp
 *
 *  Created on: Apr 15, 2026
 *      Author: dalya
 */

#ifndef CONTROL_SENSORS_INC_IMU_MPU6050_HPP_
#define CONTROL_SENSORS_INC_IMU_MPU6050_HPP_

#include "IMU.hpp"
extern "C" {
    #include "mpu6050.h"
}

class IMU_MPU6050 : public IMU {
private:
    Vector3D accel_offset;  // Acceleration offset for calibration
    Vector3D gyro_offset;   // Gyroscope offset for calibration
    
public:
    IMU_MPU6050(MPU6050_Handle_t *handle, I2C_HandleTypeDef *hi2c);
    virtual ~IMU_MPU6050();
    
    /**
     * @brief Initialize MPU6050 sensor
     * @return true if initialization successful
     */
    virtual bool init() override;
    
    /**
     * @brief Read accelerometer values from MPU6050
     * @return Acceleration vector in g
     */
    virtual Vector3D readAccelerometer() override;
    
    /**
     * @brief Read gyroscope values from MPU6050
     * @return Angular velocity vector in deg/s
     */
    virtual Vector3D readGyroscope() override;
    
    /**
     * @brief Calibrate MPU6050 sensors
     * @return true if calibration successful
     */

    virtual float readRoll() override;
    
    virtual float readPitch() override;
    
    virtual bool calibrate() override;
    
    virtual void readData() override;

    MPU6050_Handle_t *_handle;
    I2C_HandleTypeDef *_hi2c;
};

#endif /* CONTROL_SENSORS_INC_IMU_MPU6050_HPP_ */
