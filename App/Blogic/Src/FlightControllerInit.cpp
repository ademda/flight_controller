/*
 * FlightControllerInit.cpp
 * Static allocation approach - NO dynamic memory
 */

#include "FlightControllerInit.hpp"
#include "Drone.hpp"
#include "RC_Receiver_IA6_B.hpp"
#include "MCUTelemetryManager.hpp"
#include "IMU_MPU6050.hpp"
#include "Barometer_bmp280.hpp"
#include "Magnetometer_GY273.hpp"
#include "ComplementaryFilter.hpp"

// ============================================================================
// STATIC GLOBAL INSTANCES (allocated at compile time)
// ============================================================================

// Sensor instances - created statically
static IMU_MPU6050 g_imu;
static Barometer_bmp280 g_barometer;
static Magnetometer_GY273 g_magnetometer;
static ComplementaryFilter g_filter(0.98f);

// Communication instances - created statically
static RC_Receiver_IA6_B g_rc_receiver;
static MCUTelemetryManager g_telemetry;

// Application instances - created statically
static Drone g_drone(&g_rc_receiver, &g_telemetry);

// State flag
static bool g_initialized = false;

/**
 * @brief Initialize all flight controller subsystems
 * Initialize is called once at startup
 */
void FlightController_Initialize(void)
{
    if (g_initialized) {
        return;
    }

    // All static instances are already constructed
    // Now initialize them

    //g_rc_receiver.init();
    //g_telemetry.init();
    
    if (!g_drone.init()) {
        while(1);  // Halt on error
    }

    g_initialized = true;
}

/**
 * @brief Update flight controller
 * @param dt Time step in seconds
 */
void FlightController_Update(float dt)
{
    if (g_initialized && dt > 0.0f) {
        g_drone.update(dt);
    }
}

