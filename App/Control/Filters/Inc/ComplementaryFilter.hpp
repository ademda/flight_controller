/*
 * ComplementaryFilter.hpp
 *
 *  Created on: Apr 15, 2026
 *      Author: dalya
 */

#ifndef CONTROL_FILTERS_INC_COMPLEMENTARYFILTER_HPP_
#define CONTROL_FILTERS_INC_COMPLEMENTARYFILTER_HPP_

#include "Filter.hpp"

/**
 * @class ComplementaryFilter
 * @brief 1D Complementary filter for sensor fusion
 * 
 * Combines a slow response sensor (integrated) with a fast response sensor (direct)
 * using weighted averaging: output = alpha * integrated + (1 - alpha) * direct
 * 
 * Commonly used for:
 * - Accelerometer + Gyroscope fusion for accurate tilt angle
 * - Barometer + Vertical velocity for altitude estimation
 */
class ComplementaryFilter : public Filter {
private:
    float state;           // Current filtered state
    float alpha;           // Filter coefficient (0.0 to 1.0)
    float last_input;      // Previous input for differentiation
    
public:
    /**
     * @brief Constructor for complementary filter
     * @param alpha Filter coefficient (0.0 to 1.0)
     *              Higher alpha = more weight on integrated/fast response
     *              Lower alpha = more weight on direct/slow response
     */
    ComplementaryFilter(float alpha = 0.98f);
    virtual ~ComplementaryFilter();
    
    /**
     * @brief Apply complementary filter
     * @param input Current measurement input
     * @return Filtered output combining current and previous states
     */
    virtual float apply(float input) override;
    
    /**
     * @brief Reset filter state
     */
    virtual void reset() override;
    
    /**
     * @brief Set filter coefficient
     * @param new_alpha New alpha value (0.0 to 1.0)
     */
    void setAlpha(float new_alpha);
    
    /**
     * @brief Get current filter coefficient
     * @return Current alpha value
     */
    float getAlpha() const;
    
    /**
     * @brief Get current state estimate
     * @return Current filtered state
     */
    float getState() const;
};

#endif /* CONTROL_FILTERS_INC_COMPLEMENTARYFILTER_HPP_ */
