/*
 * TelemetryManager.hpp
 *
 *  Created on: Apr 15, 2026
 *      Author: dalya
 */

#ifndef INC_TELEMETRYMANAGER_HPP_
#define INC_TELEMETRYMANAGER_HPP_

class TelemetryManager{
public:
    virtual ~TelemetryManager() = 0;
    virtual void LogStateVars() = 0;
};

#endif /* INC_TELEMETRYMANAGER_HPP_ */
