/*
 * ComplementaryFilter.cpp
 *
 *  Created on: Apr 15, 2026
 *      Author: dalya
 */

#include "ComplementaryFilter.hpp"

ComplementaryFilter::ComplementaryFilter(float alpha) 
    : state(0.0f), alpha(alpha), last_input(0.0f) {
    // Clamp alpha to valid range [0.0, 1.0]
    if (this->alpha < 0.0f) {
        this->alpha = 0.0f;
    } else if (this->alpha > 1.0f) {
        this->alpha = 1.0f;
    }
}

ComplementaryFilter::~ComplementaryFilter() {
}

float ComplementaryFilter::apply(float input) {
    // Complementary filter formula:
    // output = alpha * (previous_state + derivative) + (1 - alpha) * input
    // This combines the integrated (gyroscope) and direct (accelerometer) measurements
    
    // Calculate derivative of input (current - previous)
    float derivative = input - last_input;
    
    // Apply complementary filter
    // alpha weight on integrated signal, (1-alpha) on direct measurement
    state = alpha * (state + derivative) + (1.0f - alpha) * input;
    
    // Store current input for next iteration
    last_input = input;
    
    return state;
}

void ComplementaryFilter::reset() {
    state = 0.0f;
    last_input = 0.0f;
}

void ComplementaryFilter::setAlpha(float new_alpha) {
    // Clamp alpha to valid range [0.0, 1.0]
    if (new_alpha < 0.0f) {
        alpha = 0.0f;
    } else if (new_alpha > 1.0f) {
        alpha = 1.0f;
    } else {
        alpha = new_alpha;
    }
}

float ComplementaryFilter::getAlpha() const {
    return alpha;
}

float ComplementaryFilter::getState() const {
    return state;
}
