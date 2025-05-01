/*
 * @file Gripper.cpp
 * @date 25/04/2025
 * @author Brisma Alvarez Valdez
 *
 * @brief Implementation of the Gripper class to control a servo
 */

#include "Gripper.h"

// Constructor: Initializes the servo and motor pins.
Gripper::Gripper(int servoPin)
    : servo_pin(servoPin){}

// Method to configure the gripper pins
void Gripper::Init() {
    gripper.attach(servo_pin);
}

// Method to to put the gripper in open position (inicial position) move the servo (180°)
void Gripper::Open() {
    gripper.write(GripperConstants::kOpenAngle);
}

// Method to close the gripper (move the servo to 0°) for the intake
void Gripper::Close()
{
    gripper.write(GripperConstants::kClosedAngle);
}

// Method to update the state machine
void Gripper::update(){
    switch (gripper_state_){
        case GripperState::OPEN:
            Open();
            break;
        case GripperState::CLOSED:
            Close();
            break;
    }
}

// Method to set the state of the gripper
void Gripper::setState(int state) {
    if (state == static_cast<int>(GripperState::OPEN)) {
        gripper_state_ = GripperState::OPEN;
    } else if (state == static_cast<int>(GripperState::CLOSED)) {
        gripper_state_ = GripperState::CLOSED;
    }
}
