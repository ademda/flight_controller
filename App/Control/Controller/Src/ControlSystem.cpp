/*
 * ControlSystem.cpp
 *
 *  Created on: Apr 15, 2026
 *      Author: dalya
 */

#include "ControlSystem.hpp"
#include "tuning.h"
#include <algorithm>
#include <math.h>

ControlSystem::ControlSystem()
    : roll_pid(1.0f, 0.05f, 0.1f),
      pitch_pid(1.0f, 0.05f, 0.1f),
      yaw_pid(2.0f, 0.1f, 0.05f),
      altitude_pid(0.5f, 0.01f, 0.1f),
      last_roll_output(0.0f),
      last_pitch_output(0.0f),
      last_yaw_output(0.0f),
      last_altitude_output(0.0f) {
    current_setpoints = {0.0f, 0.0f, 0.0f, 0.0f};
    previous_setpoints = {0.0f, 0.0f, 0.0f, 0.0f};
}

ControlSystem::~ControlSystem() {
}

void ControlSystem::init() {
    // Initialize tuning system
    tuning_init();
    
    // Update PID gains from tuning variables
    updatePIDGainsFromTuning();
    
    // Set output limits for controllers (in degrees for attitude, in m/s for altitude)
    roll_pid.setOutputLimit(45.0f);      // Max ±45 degree correction
    pitch_pid.setOutputLimit(45.0f);
    yaw_pid.setOutputLimit(120.0f);      // Max ±120 deg/s yaw rate
    altitude_pid.setOutputLimit(2.0f);   // Max ±2 m/s vertical velocity
    
    // Reset all controllers
    roll_pid.reset();
    pitch_pid.reset();
    yaw_pid.reset();
    altitude_pid.reset();
}

float ControlSystem::updateControl(StateEstimator& state_estimator, float dt) {
    if (dt <= 0.0f) {
        return 0.0f;
    }
    
    // Get current state from estimators
    Vector3D accel = state_estimator.getAcceleration();
    Vector3D gyro = state_estimator.getAngularVelocity();
    float altitude = state_estimator.getAltitude();
    float heading = state_estimator.getHeading();
    
    // TODO: Implement DCM (Direction Cosine Matrix) or quaternion to get current attitude angles
    // For now, using simplified attitude estimation from accelerometers
    // current_roll = atan2(accel.y, accel.z) * 180 / PI
    // current_pitch = atan2(accel.x, accel.z) * 180 / PI
    // current_yaw = heading
    
    float current_roll = 0.0f;   // TODO: Calculate from IMU data
    float current_pitch = 0.0f;  // TODO: Calculate from IMU data
    float current_yaw = heading;
    float current_altitude = altitude;
    
    // Calculate errors
    float roll_error = current_setpoints.roll - current_roll;
    float pitch_error = current_setpoints.pitch - current_pitch;
    float yaw_error = current_setpoints.yaw - current_yaw;
    float altitude_error = current_setpoints.altitude - current_altitude;
    
    // Handle yaw wraparound (±180 degrees)
    if (yaw_error > 180.0f) {
        yaw_error -= 360.0f;
    } else if (yaw_error < -180.0f) {
        yaw_error += 360.0f;
    }
    
    // Calculate PID outputs
    float roll_cmd = roll_pid.calculate(roll_error, dt);
    float pitch_cmd = pitch_pid.calculate(pitch_error, dt);
    float yaw_cmd = yaw_pid.calculate(yaw_error, dt);
    float altitude_cmd = altitude_pid.calculate(altitude_error, dt);
    
    // Normalize outputs to motor command range
    last_roll_output = std::max(-1.0f, std::min(roll_cmd / 45.0f, 1.0f));
    last_pitch_output = std::max(-1.0f, std::min(pitch_cmd / 45.0f, 1.0f));
    last_yaw_output = std::max(-1.0f, std::min(yaw_cmd / 120.0f, 1.0f));
    last_altitude_output = std::max(0.0f, std::min(altitude_cmd / 2.0f + 0.5f, 1.0f)); // Offset to 0-1 range
    
    // ========================================================================
    // TUNING MODE: Zero out outputs for non-tuning axes
    // ========================================================================
    // Only allow control on the axis being tuned
    int active_axis = tuning_get_active_axis();
    if (active_axis >= 0) {
        // If tuning mode is active, zero out all non-tuning axes
        if (active_axis != 0) last_roll_output = 0.0f;    // Zero roll if not tuning
        if (active_axis != 1) last_pitch_output = 0.0f;   // Zero pitch if not tuning
        if (active_axis != 2) last_yaw_output = 0.0f;     // Zero yaw if not tuning
    }
    
    // Update tuning monitoring variables with current state
    tuning_update_monitor(current_roll, current_pitch, current_yaw,
                          last_roll_output, last_pitch_output, last_yaw_output);
    
    // Update tuning setpoints for monitoring
    tuning_roll_setpoint = current_setpoints.roll;
    tuning_pitch_setpoint = current_setpoints.pitch;
    tuning_yaw_setpoint = current_setpoints.yaw;
    
    return last_altitude_output;
}

void ControlSystem::setAttitudeSetpoints(float roll_sp, float pitch_sp, float yaw_sp) {
    current_setpoints.roll = std::max(-45.0f, std::min(roll_sp, 45.0f));    // Limit to ±45 degrees
    current_setpoints.pitch = std::max(-45.0f, std::min(pitch_sp, 45.0f));
    current_setpoints.yaw = yaw_sp; // Allow any yaw angle
}

void ControlSystem::setAltitudeSetpoint(float altitude_sp) {
    current_setpoints.altitude = std::max(0.0f, altitude_sp); // Prevent negative altitude
}

float ControlSystem::getRollOutput() const {
    return last_roll_output;
}

float ControlSystem::getPitchOutput() const {
    return last_pitch_output;
}

float ControlSystem::getYawOutput() const {
    return last_yaw_output;
}

float ControlSystem::getAltitudeOutput() const {
    return last_altitude_output;
}

void ControlSystem::updatePIDGainsFromTuning() {
    // Update roll PID gains from tuning variables
    roll_pid.setGains(pid_roll_kp, pid_roll_ki, pid_roll_kd);
    
    // Update pitch PID gains from tuning variables
    pitch_pid.setGains(pid_pitch_kp, pid_pitch_ki, pid_pitch_kd);
    
    // Update yaw PID gains from tuning variables
    yaw_pid.setGains(pid_yaw_kp, pid_yaw_ki, pid_yaw_kd);
}
