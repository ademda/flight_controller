/*
 * PIDController.cpp
 *
 *  Created on: Apr 15, 2026
 *      Author: dalya
 */
#include "../Inc/PIDController.hpp"
#include <algorithm>

PIDController::PIDController(float kp, float ki, float kd, float error_limit ,float output_limit) 
    : kp(kp), ki(ki), kd(kd), previous_error(0.0f), integral(0.0f),
      error_limit(error_limit), output_limit(output_limit)
{
}

PIDController::~PIDController()
{
}

float PIDController::calculate(float error, float dt) {
    if (dt <= 0.0f) {
        return 0.0f;
    }
    
    // Proportional term
    float p_term = kp * error;
    
    // Integral term with windup prevention
    integral += error * dt;
    if (integral > error_limit) {
        integral = error_limit;
    } else if (integral < -error_limit) {
        integral = -error_limit;
    }
    float i_term = ki * integral;
    
    // Derivative term
    float derivative = (error - previous_error) / dt;
    float d_term = kd * derivative;
    
    // Calculate output with saturation
    float output = p_term + i_term + d_term;
    
    // Clamp output to limits
    if (output > output_limit) {
        output = output_limit;
    } else if (output < -output_limit) {
        output = -output_limit;
    }
    
    // Store error for next iteration
    previous_error = error;
    
    return output;
}

void PIDController::reset() {
    previous_error = 0.0f;
    integral = 0.0f;
}

void PIDController::setGains(float new_kp, float new_ki, float new_kd) {
    kp = new_kp;
    ki = new_ki;
    kd = new_kd;
}

void PIDController::setOutputLimit(float limit) {
    output_limit = (limit > 0.0f) ? limit : 1000.0f;
}

void PIDController::setIntegralLimit(float limit) {
    error_limit = (limit > 0.0f) ? limit : 1000.0f;
}
