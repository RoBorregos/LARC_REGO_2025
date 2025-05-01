/**
 * @file Intake.cpp
 * @brief Implementation of the Intake class
 * @author Brisma Alvarez Valdez & Juan Pablo Gutierrez
 * @date 2025-04-25
 */

#include "Intake.hpp"

Intake::Intake() : in1(Pins::kIntakeMotorPinINA), in2(Pins::kIntakeMotorPinINB) {}

void Intake::update() {
    switch (intake_state_) {
        case IntakeState::STOPPED:
            run(0);
            break;
        case IntakeState::INTAKING:
            run(IntakeConstants::kIntakeSpeed);
            break;
        case IntakeState::OUTTAKING:
            run(IntakeConstants::kOuttakeSpeed);
            break;
    }
}

void Intake::setState(int state) {
    intake_state_ = static_cast<IntakeState>(state);
}

void Intake::run(int speed) {
    if (speed > 0) {
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
    } else if (speed < 0) {
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
    } else {
        digitalWrite(in1, LOW);
        digitalWrite(in2, LOW);
    }
}
