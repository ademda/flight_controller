/*
 * Filter.hpp
 *
 *  Created on: Apr 15, 2026
 *      Author: dalya
 */

#ifndef CONTROL_SENSORS_INC_FILTER_HPP_
#define CONTROL_SENSORS_INC_FILTER_HPP_

/**
 * @class Filter
 * @brief Abstract base class for signal filtering
 */
class Filter {
public:
    Filter();
    virtual ~Filter();
    
    /**
     * @brief Apply filter to input value
     * @param input Raw input value
     * @return Filtered output value
     */
    virtual float apply(float input) = 0;
    
    /**
     * @brief Reset filter state
     */
    virtual void reset() = 0;
};

#endif /* CONTROL_SENSORS_INC_FILTER_HPP_ */
