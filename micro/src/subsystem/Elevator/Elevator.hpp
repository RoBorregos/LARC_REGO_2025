/*
 * @file Elevador.h
 * @date 25/04/2025
 * @author Brisma Alvarez Valdez
 *
 * @brief Head file of the Elevador class to control a stepper motor.
 */

#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <Arduino.h>
#include "constants/constants.h"
#include "../systems/system.hpp"
#include "constants/pins.h"

using namespace Constants;

class Elevator : public System
{

public:
    Elevator();

    void update() override;           
    void setState(int state) override;
private:

    const int step_pin;
    const int dir_pin;
    const int limit_pin;

    float actual_position_cm;
    float target_position_cm;

    void Move(int steps);
    int translateCmToSteps(float distance_cm);

    bool GetLimitState();

    // States
    enum class ElevatorState
    {
        HOME = 0,
        LOWER = 2,
        MID = 3,
        UPPER = 4,
    };

    ElevatorState elevator_state_ = ElevatorState::HOME;
};

#endif
