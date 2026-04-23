/*
 * GPSReceiver.hpp
 *
 *  Created on: Apr 15, 2026
 *      Author: dalya
 */

#ifndef COMMUNICATION_INC_GPSRECEIVER_HPP_
#define COMMUNICATION_INC_GPSRECEIVER_HPP_

#include <stdint.h>

typedef struct{
    double latitude;
    double longitude;
    float altitude;
    float speed;
    uint8_t satellites;
    bool hasFix;
}GPSData;

class GPSReceiver {
public:
	virtual ~GPSReceiver() = 0;
    virtual GPSData getCoordinates() = 0;
    GPSData _gps_data;
};



#endif /* COMMUNICATION_INC_GPSRECEIVER_HPP_ */
