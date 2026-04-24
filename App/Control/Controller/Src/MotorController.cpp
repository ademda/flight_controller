/*
 * MotorController.cpp
 *
 *  Created on: Apr 15, 2026
 *      Author: dalya
 */
#include "MotorController.hpp"
#include <algorithm>
extern "C" {
    #include "esc_pwm.h"
}
MotorController::MotorController(){}

MotorController::MotorController(TIM_HandleTypeDef *htim_in) 
    : armed(false), calibrated(false), min_throttle(0.1f), max_throttle(1.0f), htim(htim_in) {
    current_throttle = {0.0f, 0.0f, 0.0f, 0.0f};
}

MotorController::~MotorController() {
    emergencyStop();
}

bool MotorController::init() {
    // Initialize ESC PWM outputs
    if (!ESC_PWM_Init(htim)) {
        return false;
    }
    
    disarm();
    return true;
}

void MotorController::setMotorThrottle(float throttle, float roll, float pitch, float yaw) {
    if (!armed || !calibrated) {
        return; // Ignore command if not armed or not calibrated
    }
    
    // Clamp input values
    throttle = std::max(min_throttle, std::min(throttle, max_throttle));
    roll = std::max(-1.0f, std::min(roll, 1.0f));
    pitch = std::max(-1.0f, std::min(pitch, 1.0f));
    yaw = std::max(-1.0f, std::min(yaw, 1.0f));
    
    // Mix throttle, roll, pitch, yaw for quadcopter (X-configuration)
    // Motor layout:
    // Motor1 (FR): +throttle, +roll, -pitch, -yaw
    // Motor2 (FL): +throttle, -roll, -pitch, +yaw
    // Motor3 (BL): +throttle, -roll, +pitch, -yaw
    // Motor4 (BR): +throttle, +roll, +pitch, +yaw
    
    current_throttle.motor1 = throttle + roll - pitch - yaw;
    current_throttle.motor2 = throttle - roll - pitch + yaw;
    current_throttle.motor3 = throttle - roll + pitch - yaw;
    current_throttle.motor4 = throttle + roll + pitch + yaw;
    
    // Normalize if any motor exceeds limits
    float max_motor = std::max({current_throttle.motor1, current_throttle.motor2,
                                current_throttle.motor3, current_throttle.motor4});
    if (max_motor > max_throttle) {
        float scale = max_throttle / max_motor;
        current_throttle.motor1 *= scale;
        current_throttle.motor2 *= scale;
        current_throttle.motor3 *= scale;
        current_throttle.motor4 *= scale;
    }
    
    // Apply PWM to ESCs
    if (htim != nullptr) {
        ESC_PWM_SetThrottle(htim, current_throttle.motor1, current_throttle.motor2,
                           current_throttle.motor3, current_throttle.motor4);
    }
}

bool MotorController::arm() {
    if (armed) {
        return true; // Already armed
    }
    
    if (!calibrated) {
        return false; // Must calibrate ESCs first
    }
    
    // Set motors to minimum throttle (1000us) before arming
    if (htim != nullptr) {
        ESC_PWM_SetThrottle(htim, 0.0f, 0.0f, 0.0f, 0.0f);
    }
    
    armed = true;
    return true;
}

bool MotorController::disarm() {
    armed = false;
    current_throttle = {0.0f, 0.0f, 0.0f, 0.0f};
    
    // Set all motors to 0 throttle (stop spinning)
    if (htim != nullptr) {
        ESC_PWM_SetThrottle(htim, 0.0f, 0.0f, 0.0f, 0.0f);
    }
    
    return true;
}

bool MotorController::isArmed() const {
    return armed;
}

MotorThrottle MotorController::getThrottle() const {
    return current_throttle;
}

void MotorController::setMinThrottle(float min) {
    min_throttle = std::max(0.0f, std::min(min, 0.5f));
}

void MotorController::setMaxThrottle(float max) {
    max_throttle = std::max(0.5f, std::min(max, 1.0f));
}

void MotorController::emergencyStop() {
    armed = false;
    current_throttle = {0.0f, 0.0f, 0.0f, 0.0f};
    
    // Immediately cut all motor power (set all PWM to 0)
    if (htim != nullptr) {
        ESC_PWM_SetThrottle(htim, 0.0f, 0.0f, 0.0f, 0.0f);
    }
}

bool MotorController::calibrateESCs(uint32_t duration_ms) {
    if (htim == nullptr) {
        return false;
    }
    
    if (armed) {
        return false; // Cannot calibrate while armed
    }
    
    // Perform ESC calibration routine
    ESC_PWM_Calibrate(htim, duration_ms);
    
    calibrated = true;
    return true;
}
