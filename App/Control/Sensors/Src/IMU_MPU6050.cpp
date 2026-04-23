/*
 * IMU_MPU6050.cpp
 *
 *  Created on: Apr 15, 2026
 *      Author: dalya
 */

#include "IMU_MPU6050.hpp"

IMU_MPU6050::IMU_MPU6050(MPU6050_Handle_t *handle, I2C_HandleTypeDef *hi2c) 
: accel_offset({0, 0, 0}), gyro_offset({0, 0, 0}), _handle(handle), _hi2c(hi2c){
}

IMU_MPU6050::~IMU_MPU6050() {
}

bool IMU_MPU6050::init() {
    MPU6050_Init(_handle, _hi2c, _handle->i2c_addr);
    return false;
}

Vector3D IMU_MPU6050::readAccelerometer() {
    Vector3D accel = {_handle->accel_x, _handle->accel_y, _handle->accel_z};
    return accel;
}

Vector3D IMU_MPU6050::readGyroscope() {
    Vector3D gyro = {_handle->gyro_x, _handle->gyro_y, _handle->gyro_z};
    return gyro;
}
float IMU_MPU6050::readRoll(){
    return _handle->roll;
}

float IMU_MPU6050::readPitch(){
    return _handle->pitch;
}

bool IMU_MPU6050::calibrate() {
    MPU6050_Calibrate(_handle, 1000); // Collect 1000 samples for calibration
    return false;
}

void IMU_MPU6050::readData() {
    MPU6050_Start_Reading(_handle);
}

