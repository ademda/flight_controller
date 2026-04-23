/*
 * GPSReceiver.cpp
 *
 *  Created on: Apr 15, 2026
 *      Author: dalya
 */

#include "../Inc/GPSReceiver_Neo_6M.hpp"

GPSReceiver_Neo_6M::GPSReceiver_Neo_6M() : last_update_time(0) {
    _gps_data = {0.0, 0.0, 0.0f, 0.0f, 0, false};
}

GPSReceiver_Neo_6M::~GPSReceiver_Neo_6M() {
}

bool GPSReceiver_Neo_6M::init() {
    // TODO: Initialize UART for GPS serial communication
    return true;
}

GPSData GPSReceiver_Neo_6M::getCoordinates() {
    // TODO: Parse NMEA sentences from serial buffer
    return _gps_data;
}

void GPSReceiver_Neo_6M::updateRawData(const GPSData& data) {
    _gps_data = data;
}

