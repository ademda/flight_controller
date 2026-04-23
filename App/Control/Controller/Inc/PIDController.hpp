/*
 * PIDController.hpp
 *
 *  Created on: Apr 15, 2026
 *      Author: dalya
 */

#ifndef CONTROL_CONTROLLER_INC_PIDCONTROLLER_HPP_
#define CONTROL_CONTROLLER_INC_PIDCONTROLLER_HPP_

/**
 * @class PIDController
 * @brief Proportional-Integral-Derivative controller for closed-loop control
 * 
 * Implements PID control law: output = Kp*e + Ki*integral(e) + Kd*de/dt
 */
class PIDController{
private:
    float kp; // Proportional gain
    float ki; // Integral gain
    float kd; // Derivative gain
    float previous_error; // To store the previous error for derivative calculation
    float integral; // To accumulate the integral of the error
    float error_limit; // Limit for integral windup prevention
    float output_limit; // Saturation limit for controller output
    
public:
    /**
     * @brief Constructor for PID controller
     * @param kp Proportional gain coefficient
     * @param ki Integral gain coefficient
     * @param kd Derivative gain coefficient
     */
    PIDController(float kp=0.0f,float ki=0.0f,float kd=0.0f,float error_limit=1000.0f,float output_limit=1000.0f);
    ~PIDController();
    
    /**
     * @brief Calculate PID output
     * @param error Current error (setpoint - measurement)
     * @param dt Time step in seconds
     * @return PID controller output
     */
    float calculate(float error, float dt);
    
    /**
     * @brief Reset controller state
     */
    void reset();
    
    /**
     * @brief Set new PID gains
     * @param new_kp Proportional gain
     * @param new_ki Integral gain
     * @param new_kd Derivative gain
     */
    void setGains(float new_kp, float new_ki, float new_kd);
    
    /**
     * @brief Set output limits for saturation
     * @param limit Maximum absolute output value
     */
    void setOutputLimit(float limit);
    
    /**
     * @brief Set integral windup prevention limit
     * @param limit Maximum integral accumulation
     */
    void setIntegralLimit(float limit);
};

#endif /* CONTROL_CONTROLLER_INC_PIDCONTROLLER_HPP_ */
