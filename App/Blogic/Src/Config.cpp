/*
 * Config.cpp
 *
 *  Created on: Apr 15, 2026
 *      Author: dalya
 */
#include "../Inc/Config.hpp"

DroneConfig::DroneConfig() 
    : current_mode(MODE_DISARMED), previous_mode(MODE_DISARMED),
      battery_voltage(12.0f), battery_warning_threshold(10.5f),
      controller_temperature(25.0f), armed_flag(false) {
}

DroneConfig::~DroneConfig() {
}

void DroneConfig::setMode(DroneMode mode) {
    previous_mode = current_mode;
    current_mode = mode;
    
    if (mode == MODE_DISARMED) {
        armed_flag = false;
    } else {
        armed_flag = true;
    }
}

DroneMode DroneConfig::getMode() const {
    return current_mode;
}

bool DroneConfig::checkSafety() const {
    // TODO: Read battery voltage from ADC
    // battery_voltage = readBattery();
    
    // TODO: Read controller temperature
    // controller_temperature = readTemperature();
    
    // Check safety conditions
    if (battery_voltage < battery_warning_threshold) {
        return false; // Battery too low
    }
    
    if (controller_temperature > 80.0f) {
        return false; // Controller overheating
    }
    
    return true;
}

float DroneConfig::getBatteryVoltage() const {
    return battery_voltage;
}

void DroneConfig::setBatteryWarningThreshold(float voltage) {
    battery_warning_threshold = (voltage > 0.0f) ? voltage : 10.5f;
}

bool DroneConfig::isBatteryLow() const {
    return battery_voltage < battery_warning_threshold;
}

float DroneConfig::getTemperature() const {
    return controller_temperature;
}

bool DroneConfig::isSafeToFly() const {
    return checkSafety() && armed_flag && current_mode != MODE_DISARMED;
}