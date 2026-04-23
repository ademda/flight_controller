/*
 * MCUTelemetryManager.hpp
 *
 *  Created on: Apr 15, 2026
 *      Author: dalya
 */

#ifndef COMMUNICATION_INC_MCUTELEMETRYMANAGER_HPP_
#define COMMUNICATION_INC_MCUTELEMETRYMANAGER_HPP_
#include "TelemetryManager.hpp"
class MCUTelemetryManager : public TelemetryManager{
public:
    MCUTelemetryManager();
    ~MCUTelemetryManager();
    void LogStateVars() override;
    
};




#endif /* COMMUNICATION_INC_MCUTELEMETRYMANAGER_HPP_ */
