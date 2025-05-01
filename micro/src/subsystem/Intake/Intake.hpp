/**
 * @file Intake.hpp
 * @brief Header file for the Intake class
 * @author Brisma Alvarez Valdez & Juan Pablo Gutierrez
 * @date 2025-04-25
 */

#pragma once

#include "../systems/system.hpp"
#include "constants/constants.h"
#include "constants/pins.h"

using namespace Constants;

class Intake : public System {
    public:
        Intake();
        void update() override;
        void setState(int state) override;
    private:
        int in1;
        int in2;
        void run(int speed);
        enum class IntakeState {
            STOPPED = 0,
            INTAKING = 1,
            OUTTAKING = 2,
        };

        IntakeState intake_state_ = IntakeState::STOPPED;
};