/*
 * FlightController.cpp
 *
 *  Created on: Apr 15, 2026
 *      Author: dalya
 */

#include "FlightController.hpp"

FlightController::FlightController() 
    : gps_receiver(nullptr), loop_frequency(100.0f), last_update_time(0.0f), initialized(false) {
}

FlightController::FlightController(GPSReceiver* gps_receiver) 
    : gps_receiver(gps_receiver), loop_frequency(100.0f), last_update_time(0.0f), initialized(false) {
}

FlightController::~FlightController() {
    if (initialized) {
        emergencyStop();
    }
}

bool FlightController::init() {
    if (initialized) {
        return true;
    }
    
    control_system.init();
    if (!motor_controller.init()) {
        return false;
    }
    if (!state_estimator.initializeSensors()) {
        return false;
    }
    
    initialized = true;
    return true;
}

void FlightController::update(float dt) {
    if (!initialized || dt <= 0.0f) {
        return;
    }
    
    state_estimator.updateState();
    float throttle_cmd = control_system.updateControl(state_estimator, dt);
    
    float roll_output = control_system.getRollOutput();
    float pitch_output = control_system.getPitchOutput();
    float yaw_output = control_system.getYawOutput();
    
    motor_controller.setMotorThrottle(throttle_cmd, roll_output, pitch_output, yaw_output);
}

void FlightController::setAttitudeSetpoints(float roll_sp, float pitch_sp, float yaw_sp) {
    control_system.setAttitudeSetpoints(roll_sp, pitch_sp, yaw_sp);
}

void FlightController::setAltitudeSetpoint(float altitude_sp) {
    control_system.setAltitudeSetpoint(altitude_sp);
}

void FlightController::setThrottle(float throttle) {
    // TODO: Implement direct throttle control
}

bool FlightController::arm() {
    if (!initialized) return false;
    return motor_controller.arm();
}

bool FlightController::disarm() {
    return motor_controller.disarm();
}

bool FlightController::isArmed() const {
    return motor_controller.isArmed();
}

void FlightController::emergencyStop() {
    motor_controller.emergencyStop();
}

Vector3D FlightController::getAttitude() const {
    Vector3D attitude;
    attitude.x = 0.0f; // TODO: Read roll from state estimator
    attitude.y = 0.0f; // TODO: Read pitch from state estimator
    attitude.z = state_estimator.getHeading();
    return attitude;
}

float FlightController::getAltitude() const {
    return state_estimator.getAltitude();
}

GPSData FlightController::getGPSData() const {
    if (gps_receiver == nullptr) {
        return GPSData{0.0, 0.0, 0.0f, 0.0f, 0, false};
    }
    return gps_receiver->getCoordinates();
}

void FlightController::setLoopFrequency(float frequency) {
    loop_frequency = (frequency > 0.0f) ? frequency : 100.0f;
}
