/*
 * tuning.h
 *
 *  Created on: Apr 26, 2026
 *      Author: dalya
 *  Purpose: PID tuning configuration for individual axis tuning via terminal
 */

#ifndef INC_TUNING_H_
#define INC_TUNING_H_

#ifdef __cplusplus
extern "C" {
#endif

/* ============================================================================
 * TUNING MODE CONFIGURATION
 * ============================================================================
 * Enable ONLY ONE of the following at a time to tune individual PIDs
 * Set to 1 to enable tuning for that axis, 0 to disable
 * When enabled, the drone will only respond to commands on that axis
 * ========================================================================== */

#define ROLL_TUNING    0
#define PITCH_TUNING   0
#define YAW_TUNING     0

/* ============================================================================
 * TUNING MONITORING VARIABLES
 * ============================================================================
 * These global variables are exposed for monitoring with CubeMonitor
 * Use these to observe the drone's response during PID tuning
 * ========================================================================== */

extern float tuning_current_roll;      // Current roll angle (degrees)
extern float tuning_current_pitch;     // Current pitch angle (degrees)
extern float tuning_current_yaw;       // Current yaw angle (degrees)

extern float tuning_roll_setpoint;     // Roll setpoint (degrees)
extern float tuning_pitch_setpoint;    // Pitch setpoint (degrees)
extern float tuning_yaw_setpoint;      // Yaw setpoint (degrees)

extern float tuning_roll_error;        // Roll error (degrees)
extern float tuning_pitch_error;       // Pitch error (degrees)
extern float tuning_yaw_error;         // Yaw error (degrees)

extern float tuning_roll_output;       // Roll PID output (-1.0 to 1.0)
extern float tuning_pitch_output;      // Pitch PID output (-1.0 to 1.0)
extern float tuning_yaw_output;        // Yaw PID output (-1.0 to 1.0)

/* ============================================================================
 * ADJUSTABLE PID GAINS
 * ============================================================================
 * Modify these values via terminal to tune the selected axis PID
 * Format: set_pid <axis> <kp> <ki> <kd>
 * Example: set_pid roll 1.5 0.08 0.15
 * ========================================================================== */

extern float pid_roll_kp;              // Roll proportional gain
extern float pid_roll_ki;              // Roll integral gain
extern float pid_roll_kd;              // Roll derivative gain

extern float pid_pitch_kp;             // Pitch proportional gain
extern float pid_pitch_ki;             // Pitch integral gain
extern float pid_pitch_kd;             // Pitch derivative gain

extern float pid_yaw_kp;               // Yaw proportional gain
extern float pid_yaw_ki;               // Yaw integral gain
extern float pid_yaw_kd;               // Yaw derivative gain

/* ============================================================================
 * UTILITY FUNCTIONS
 * ========================================================================== */

/**
 * @brief Initialize tuning system and monitor variables
 */
void tuning_init(void);

/**
 * @brief Update monitoring variables with current PID state
 * @param roll_angle Current roll angle in degrees
 * @param pitch_angle Current pitch angle in degrees
 * @param yaw_angle Current yaw angle in degrees
 * @param roll_out Roll PID output
 * @param pitch_out Pitch PID output
 * @param yaw_out Yaw PID output
 */
void tuning_update_monitor(float roll_angle, float pitch_angle, float yaw_angle,
                           float roll_out, float pitch_out, float yaw_out);

/**
 * @brief Check if a specific axis is in tuning mode
 * @param axis Axis index: 0=roll, 1=pitch, 2=yaw
 * @return 1 if axis is in tuning mode, 0 otherwise
 */
int tuning_is_axis_enabled(int axis);

/**
 * @brief Get the active tuning axis (0=roll, 1=pitch, 2=yaw, -1=none)
 * @return Active axis index or -1 if no tuning is active
 */
int tuning_get_active_axis(void);

#ifdef __cplusplus
}
#endif

#endif /* INC_TUNING_H_ */
