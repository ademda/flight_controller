/*
 * DesktopTelemetryManager.hpp
 *
 *  Created on: Apr 15, 2026
 *      Author: dalya
 */

#ifndef COMMUNICATION_INC_DESKTOPTELEMETRYMANAGER_HPP_
#define COMMUNICATION_INC_DESKTOPTELEMETRYMANAGER_HPP_
#include "TelemetryManager.hpp"
class DesktopTelemetryManager : public TelemetryManager{
public:
    DesktopTelemetryManager();
    ~DesktopTelemetryManager();
    void LogStateVars() override;
};



#endif /* COMMUNICATION_INC_DESKTOPTELEMETRYMANAGER_HPP_ */
