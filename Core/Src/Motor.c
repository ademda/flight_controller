/*
 * Motor.c
 *
 *  Created on: Apr 28, 2026
 *      Author: dalya
 */

#include "Motor.h"
void motor_mixer(float roll_out, float pitch_out, float yaw_out,
                 float throttle, Motor_t *motor_out) {

    // Base throttle for all motors
    float m1 = throttle;  // Front-Right
    float m2 = throttle;  // Front-Left
    float m3 = throttle;  // Back-Left
    float m4 = throttle;  // Back-Right

    // Apply roll correction (left-right tilt)
    // Roll right: Increase right motors (m1, m4), decrease left motors (m2, m3)
    m1 += roll_out;
    m4 += roll_out;
    m2 -= roll_out;
    m3 -= roll_out;

    // Apply pitch correction (forward-backward tilt)
    // Pitch forward: Increase front motors (m1, m2), decrease back motors (m3, m4)
    m1 += pitch_out;
    m2 += pitch_out;
    m3 -= pitch_out;
    m4 -= pitch_out;

    // Apply yaw correction (rotation)
    // For X-config: Motors 1,3 spin CW, Motors 2,4 spin CCW
    // Yaw right: Speed up CW motors (m1, m3), slow down CCW motors (m2, m4)
    m1 -= yaw_out;
    m3 -= yaw_out;
    m2 += yaw_out;
    m4 += yaw_out;

    // ============ Limit motor values to valid PWM range ============
    // Valid range: 1000µs (min throttle) to 2000µs (max throttle)


    if (m1 < MOTOR_MIN) m1 = MOTOR_MIN;
    if (m1 > MOTOR_MAX) m1 = MOTOR_MAX;

    if (m2 < MOTOR_MIN) m2 = MOTOR_MIN;
    if (m2 > MOTOR_MAX) m2 = MOTOR_MAX;

    if (m3 < MOTOR_MIN) m3 = MOTOR_MIN;
    if (m3 > MOTOR_MAX) m3 = MOTOR_MAX;

    if (m4 < MOTOR_MIN) m4 = MOTOR_MIN;
    if (m4 > MOTOR_MAX) m4 = MOTOR_MAX;

    // ============ Store motor outputs ============
    motor_out->motor1 = (uint16_t)m1;
    motor_out->motor2 = (uint16_t)m2;
    motor_out->motor3 = (uint16_t)m3;
    motor_out->motor4 = (uint16_t)m4;
}

