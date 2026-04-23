/*
 * MotorController.hpp
 *
 *  Created on: Apr 15, 2026
 *      Author: dalya
 */

#ifndef CONTROL_CONTROLLER_INC_MOTORCONTROLLER_HPP_
#define CONTROL_CONTROLLER_INC_MOTORCONTROLLER_HPP_

#include "stm32f1xx_hal.h"

/**
 * @struct MotorThrottle
 * @brief PWM throttle values for 4 motors (quadcopter configuration)
 */
typedef struct {
    float motor1; // Front-right
    float motor2; // Front-left
    float motor3; // Back-left
    float motor4; // Back-right
} MotorThrottle;

/**
 * @class MotorController
 * @brief Controls quadcopter motor speeds via PWM signals
 * 
 * Manages four brushless DC motors with PWM control (1000-2000 microseconds)
 * Min throttle: 1000us, Max throttle: 2000us, Neutral: 1500us
 */
class MotorController {
private:
    MotorThrottle current_throttle;  // Current motor throttle levels
    bool armed;                       // Motor armed/disarmed state
    bool calibrated;                  // ESC calibration status
    float min_throttle;               // Minimum throttle value (0.0-1.0)
    float max_throttle;               // Maximum throttle value (0.0-1.0)
    TIM_HandleTypeDef *htim;          // Pointer to Timer1 handle for PWM
    
public:
    MotorController();
    MotorController(TIM_HandleTypeDef *htim_in);
    ~MotorController();
    
    /**
     * @brief Initialize motor controller and PWM outputs
     * @param htim Pointer to Timer1 handle for PWM
     * @return true if initialization successful
     */
    bool init();
    
    /**
     * @brief Set throttle for all motors
     * @param throttle Throttle value (0.0 to 1.0, where 0 = min, 1 = max)
     * @param roll Roll control input (-1.0 to 1.0)
     * @param pitch Pitch control input (-1.0 to 1.0)
     * @param yaw Yaw control input (-1.0 to 1.0)
     */
    void setMotorThrottle(float throttle, float roll, float pitch, float yaw);
    
    /**
     * @brief Arm motors (enable PWM output)
     * @return true if successfully armed
     */
    bool arm();
    
    /**
     * @brief Disarm motors (disable PWM output, set to minimum)
     * @return true if successfully disarmed
     */
    bool disarm();
    
    /**
     * @brief Check if motors are armed
     * @return true if motors are armed
     */
    bool isArmed() const;
    
    /**
     * @brief Get current motor throttle values
     * @return Current throttle structure
     */
    MotorThrottle getThrottle() const;
    
    /**
     * @brief Set minimum throttle cutoff
     * @param min Minimum throttle (0.0 to 1.0)
     */
    void setMinThrottle(float min);
    
    /**
     * @brief Set maximum throttle limit
     * @param max Maximum throttle (0.0 to 1.0)
     */
    void setMaxThrottle(float max);
    
    /**
     * @brief Emergency stop - cut all motor power immediately
     */
    void emergencyStop();
    
    /**
     * @brief Calibrate ESCs before first use
     * Must be called while drone is powered but not armed
     * @param duration_ms How long to hold each throttle level (1000-2000ms)
     * @return true if calibration successful
     */
    bool calibrateESCs(uint32_t duration_ms);
};

#endif /* CONTROL_CONTROLLER_INC_MOTORCONTROLLER_HPP_ */
