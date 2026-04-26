/*
 * tuning.c
 *
 *  Created on: Apr 26, 2026
 *      Author: dalya
 *  Purpose: PID tuning configuration implementation
 */

#include "tuning.h"

/* ============================================================================
 * MONITORING VARIABLES
 * ========================================================================== */

// Current attitude measurements
float tuning_current_roll = 0.0f;
float tuning_current_pitch = 0.0f;
float tuning_current_yaw = 0.0f;

// Setpoints
float tuning_roll_setpoint = 0.0f;
float tuning_pitch_setpoint = 0.0f;
float tuning_yaw_setpoint = 0.0f;

// Error values
float tuning_roll_error = 0.0f;
float tuning_pitch_error = 0.0f;
float tuning_yaw_error = 0.0f;

// PID outputs
float tuning_roll_output = 0.0f;
float tuning_pitch_output = 0.0f;
float tuning_yaw_output = 0.0f;

/* ============================================================================
 * TUNABLE PID GAINS
 * ========================================================================== */

// Roll PID gains (default values)
float pid_roll_kp = 1.0f;
float pid_roll_ki = 0.05f;
float pid_roll_kd = 0.1f;

// Pitch PID gains (default values)
float pid_pitch_kp = 1.0f;
float pid_pitch_ki = 0.05f;
float pid_pitch_kd = 0.1f;

// Yaw PID gains (default values)
float pid_yaw_kp = 2.0f;
float pid_yaw_ki = 0.1f;
float pid_yaw_kd = 0.05f;

/* ============================================================================
 * IMPLEMENTATION
 * ========================================================================== */

void tuning_init(void) {
    // Initialize all monitoring variables to zero
    tuning_current_roll = 0.0f;
    tuning_current_pitch = 0.0f;
    tuning_current_yaw = 0.0f;
    
    tuning_roll_setpoint = 0.0f;
    tuning_pitch_setpoint = 0.0f;
    tuning_yaw_setpoint = 0.0f;
    
    tuning_roll_error = 0.0f;
    tuning_pitch_error = 0.0f;
    tuning_yaw_error = 0.0f;
    
    tuning_roll_output = 0.0f;
    tuning_pitch_output = 0.0f;
    tuning_yaw_output = 0.0f;
}

void tuning_update_monitor(float roll_angle, float pitch_angle, float yaw_angle,
                           float roll_out, float pitch_out, float yaw_out) {
    // Update current measurements
    tuning_current_roll = roll_angle;
    tuning_current_pitch = pitch_angle;
    tuning_current_yaw = yaw_angle;
    
    // Update outputs
    tuning_roll_output = roll_out;
    tuning_pitch_output = pitch_out;
    tuning_yaw_output = yaw_out;
    
    // Calculate errors from setpoints
    tuning_roll_error = tuning_roll_setpoint - tuning_current_roll;
    tuning_pitch_error = tuning_pitch_setpoint - tuning_current_pitch;
    tuning_yaw_error = tuning_yaw_setpoint - tuning_current_yaw;
    
    // Handle yaw wraparound (±180 degrees)
    if (tuning_yaw_error > 180.0f) {
        tuning_yaw_error -= 360.0f;
    } else if (tuning_yaw_error < -180.0f) {
        tuning_yaw_error += 360.0f;
    }
}

int tuning_is_axis_enabled(int axis) {
    switch (axis) {
        case 0:  // Roll
            return ROLL_TUNING;
        case 1:  // Pitch
            return PITCH_TUNING;
        case 2:  // Yaw
            return YAW_TUNING;
        default:
            return 0;
    }
}

int tuning_get_active_axis(void) {
    if (ROLL_TUNING) return 0;
    if (PITCH_TUNING) return 1;
    if (YAW_TUNING) return 2;
    return -1;
}
