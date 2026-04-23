/*
 * Drone.hpp
 *
 *  Created on: Apr 15, 2026
 *      Author: dalya
 */

#ifndef INC_DRONE_HPP_
#define INC_DRONE_HPP_

#include "FlightController.hpp"
#include "RCReceiver.hpp"
#include "TelemetryManager.hpp"
#include "Config.hpp"

/**
 * @class Drone
 * @brief Main drone application managing high-level flight operations
 */
class Drone {
public:
    Drone(RCReceiver* receiver, TelemetryManager* telemetry_manager);
    ~Drone();

    bool init();
    void update(float dt);
    bool arm();
    bool disarm();
    void emergencyLanding();
    
    DroneConfig& getConfig();
    bool isArmed() const;

private:
    FlightController _flight_controller;
    TelemetryManager* _telemetry_manager;
    RCReceiver* _rc_receiver;
    DroneConfig _config;
    bool _initialized;
};

#endif /* INC_DRONE_HPP_ */