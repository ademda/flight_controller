/*
 * ControlSystem.hpp
 *
 *  Created on: Apr 15, 2026
 *      Author: dalya
 */

#ifndef CONTROL_CONTROLLER_INC_CONTROLSYSTEM_HPP_
#define CONTROL_CONTROLLER_INC_CONTROLSYSTEM_HPP_

#include "PIDController.hpp"
#include "StateEstimator.hpp"
#include "MotorController.hpp"

/**
 * @struct Setpoints
 * @brief Desired state values for control
 */
typedef struct {
    float roll;      // Desired roll angle (degrees)
    float pitch;     // Desired pitch angle (degrees)
    float yaw;       // Desired yaw angle (degrees)
    float altitude;  // Desired altitude (meters)
} Setpoints;

/**
 * @class ControlSystem
 * @brief Main flight control system coordinating attitude and altitude control
 * 
 * Manages four PID controllers for stabilization:
 * - Roll control
 * - Pitch control
 * - Yaw control
 * - Altitude control
 */
class ControlSystem {
private:
    PIDController roll_pid;      // Roll stabilization controller
    PIDController pitch_pid;     // Pitch stabilization controller
    PIDController yaw_pid;       // Yaw stabilization controller
    PIDController altitude_pid;  // Altitude control
    
    Setpoints current_setpoints; // Current desired state
    Setpoints previous_setpoints; // Previous setpoints for change detection
    
    float last_roll_output;      // Last roll output for getter
    float last_pitch_output;     // Last pitch output for getter
    float last_yaw_output;       // Last yaw output for getter
    float last_altitude_output;  // Last altitude output for getter
    
public:
    ControlSystem();
    ~ControlSystem();
    
    /**
     * @brief Initialize control system with default PID gains
     */
    void init();
    
    /**
     * @brief Update control outputs based on current state
     * @param state_estimator State estimator with current measurements
     * @param dt Time step in seconds
     * @return Motor throttle command (0.0 to 1.0)
     */
    float updateControl(StateEstimator& state_estimator, float dt);
    
    /**
     * @brief Set desired attitude setpoints
     * @param roll_sp Desired roll angle (degrees)
     * @param pitch_sp Desired pitch angle (degrees)
     * @param yaw_sp Desired yaw angle (degrees)
     */
    void setAttitudeSetpoints(float roll_sp, float pitch_sp, float yaw_sp);
    
    /**
     * @brief Set desired altitude setpoint
     * @param altitude_sp Desired altitude (meters)
     */
    void setAltitudeSetpoint(float altitude_sp);
    
    /**
     * @brief Get roll control output
     * @return Roll control value (-1.0 to 1.0)
     */
    float getRollOutput() const;
    
    /**
     * @brief Get pitch control output
     * @return Pitch control value (-1.0 to 1.0)
     */
    float getPitchOutput() const;
    
    /**
     * @brief Get yaw control output
     * @return Yaw control value (-1.0 to 1.0)
     */
    float getYawOutput() const;
    
    /**
     * @brief Get altitude control output
     * @return Altitude control value (0.0 to 1.0)
     */
    float getAltitudeOutput() const;
};

#endif /* CONTROL_CONTROLLER_INC_CONTROLSYSTEM_HPP_ */
