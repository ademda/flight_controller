/*
 * GPSReceiver_Neo_6M.hpp
 *
 *  Created on: Apr 15, 2026
 *      Author: dalya
 */

#ifndef COMMUNICATION_INC_GPSRECEIVER_NEO_6M_HPP_
#define COMMUNICATION_INC_GPSRECEIVER_NEO_6M_HPP_

#include "GPSReceiver.hpp"

class GPSReceiver_Neo_6M : public GPSReceiver {
public:
    GPSReceiver_Neo_6M();
    ~GPSReceiver_Neo_6M();
    
    bool init();
    GPSData getCoordinates() override;
    void updateRawData(const GPSData& data);

private:
    uint32_t last_update_time;
};

#endif /* COMMUNICATION_INC_GPSRECEIVER_NEO_6M_HPP_ */
