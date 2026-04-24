/*
 * FlightController.hpp
 *
 *  Created on: Apr 15, 2026
 *      Author: dalya
 */

#ifndef INC_FLIGHTCONTROLLER_HPP_
#define INC_FLIGHTCONTROLLER_HPP_

#include "ControlSystem.hpp"
#include "MotorController.hpp"
#include "StateEstimator.hpp"
#include "GPSReceiver.hpp"
#include "RCReceiver.hpp"
/**
 * @class FlightController
 * @brief Core flight control loop managing sensor fusion and attitude stabilization
 */
class FlightController {
private:
	MotorController motor_controller;
	StateEstimator state_estimator;
	GPSReceiver* gps_receiver;
	ControlSystem control_system;
	float loop_frequency;
	float last_update_time;
	bool initialized;

public:
	FlightController();
	FlightController(GPSReceiver* gps_receiver);
	~FlightController();
	
	bool init();
	void update(float dt);
	void setAttitudeSetpoints(float roll_sp, float pitch_sp, float yaw_sp);
	void setAltitudeSetpoint(float altitude_sp);
	void setThrottle(float throttle);
	bool arm();
	bool disarm();
	bool isArmed() const;
	void emergencyStop();
	Vector3D getAttitude() const;
	float getAltitude() const;
	GPSData getGPSData() const;
	void setLoopFrequency(float frequency);
};

#endif /* INC_FLIGHTCONTROLLER_HPP_ */
