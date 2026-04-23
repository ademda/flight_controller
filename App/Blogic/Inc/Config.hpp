/*
 * Config.hpp
 *
 *  Created on: Apr 15, 2026
 *      Author: dalya
 */

#ifndef INC_CONFIG_HPP_
#define INC_CONFIG_HPP_

#include <stdint.h>

/**
 * @enum DroneMode
 * @brief Operating modes for the drone
 */
typedef enum {
    MODE_DISARMED = 0,      // Motors disabled
    MODE_ARMED_MANUAL = 1,  // Manual control
    MODE_STABILIZE = 2,     // Attitude stabilization
    MODE_ALTITUDE_HOLD = 3, // Maintain altitude
    MODE_AUTO = 4           // Autonomous mission
} DroneMode;

/**
 * @class DroneConfig
 * @brief Drone configuration and mode management
 */
class DroneConfig {
public:    
    DroneConfig();
    ~DroneConfig();
    
    /**
     * @brief Set drone operating mode
     * @param mode Desired operating mode
     */
    void setMode(DroneMode mode);
    
    /**
     * @brief Get current drone operating mode
     * @return Current operating mode
     */
    DroneMode getMode() const;
    
    /**
     * @brief Check drone safety conditions
     * @return true if all safety checks pass
     */
    bool checkSafety() const;
    
    /**
     * @brief Get battery voltage
     * @return Battery voltage in volts
     */
    float getBatteryVoltage() const;
    
    /**
     * @brief Set battery warning threshold
     * @param voltage Voltage threshold
     */
    void setBatteryWarningThreshold(float voltage);
    
    /**
     * @brief Get low battery warning status
     * @return true if battery is low
     */
    bool isBatteryLow() const;
    
    /**
     * @brief Get temperature reading
     * @return Controller temperature in Celsius
     */
    float getTemperature() const;
    
    /**
     * @brief Check if drone is armed and safe to fly
     * @return true if safe to fly
     */
    bool isSafeToFly() const;
    
private:
    DroneMode current_mode;
    DroneMode previous_mode;
    float battery_voltage;
    float battery_warning_threshold;
    float controller_temperature;
    bool armed_flag;
};

#endif /* INC_CONFIG_HPP_ */
