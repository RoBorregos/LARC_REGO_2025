/*
 * @file Gripper.h
 * @date 12/03/2025
 * @author Brisma Alvarez Valdez & Juan Pablo Gutierrez
 *
 * @brief Head file of the Gripper class to control a servo and a motor.
 */

#pragma once

#include <Arduino.h>
#include <PWMServo.h>
#include "../systems/system.hpp"
#include "constants/constants.h"
#include "constants/pins.h"

using namespace Constants;

class Gripper : public System {
    public:
        Gripper();
        void update() override;
        void setState(int state) override;
        void move(int angle);  // Make move public temporarily
    private:
        PWMServo servo;
        enum class GripperState {
            CLOSED = 0,
            OPEN = 1,
        };

        GripperState gripper_state_ = GripperState::OPEN;
};