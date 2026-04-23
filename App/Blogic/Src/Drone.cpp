/*
 * Drone.cpp
 *
 *  Created on: Apr 15, 2026
 *      Author: dalya
 */

#include "Drone.hpp"

Drone::Drone(RCReceiver* receiver, TelemetryManager* telemetry_manager) 
    : _rc_receiver(receiver), _telemetry_manager(telemetry_manager), _initialized(false) {
}

Drone::~Drone() {
    if (_initialized) {
        disarm();
    }
}

bool Drone::init() {
    if (_initialized) {
        return true;
    }
    
    if (!_flight_controller.init()) {
        return false;
    }
    
    _initialized = true;
    return true;
}

void Drone::update(float dt) {
    if (!_initialized || dt <= 0.0f) {
        return;
    }
    
    if (_rc_receiver != nullptr) {
        Receiver_Data_t rc_cmd = _rc_receiver->getCommand();
        
        if (rc_cmd.isArmed && !isArmed()) {
            arm();
        } else if (!rc_cmd.isArmed && isArmed()) {
            disarm();
        }
        
        _flight_controller.setAttitudeSetpoints(rc_cmd.roll * 45.0f, rc_cmd.pitch * 45.0f, rc_cmd.yaw * 180.0f);
        _flight_controller.setAltitudeSetpoint(rc_cmd.throttle * 100.0f);
    }
    
    _flight_controller.update(dt);
    
    if (_telemetry_manager != nullptr) {
        _telemetry_manager->LogStateVars();
    }
}

bool Drone::arm() {
    if (!_config.checkSafety()) {
        return false;
    }
    
    _config.setMode(MODE_STABILIZE);
    return _flight_controller.arm();
}

bool Drone::disarm() {
    _config.setMode(MODE_DISARMED);
    return _flight_controller.disarm();
}

void Drone::emergencyLanding() {
    _flight_controller.emergencyStop();
    _config.setMode(MODE_DISARMED);
}

DroneConfig& Drone::getConfig() {
    return _config;
}

bool Drone::isArmed() const {
    return _flight_controller.isArmed();
}
