/*
 * FlightControllerInit.hpp
 * C++ wrapper for flight controller initialization (static allocation)
 */

#ifndef APP_BLOGIC_INC_FLIGHTCONTROLLERINIT_HPP_
#define APP_BLOGIC_INC_FLIGHTCONTROLLERINIT_HPP_

#ifdef __cplusplus
extern "C" {
#endif

// C interface for initializing and running the flight controller
void FlightController_Initialize(void);
void FlightController_Update(float dt);
#ifdef __cplusplus
}
#endif

#endif