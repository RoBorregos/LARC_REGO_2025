/*
 * @file Gripper.h
 * @date 25/04/2025
 * @author Brisma Alvarez Valdez
 *
 * @brief Head file of the Gripper class to control a servo.
 */

#ifndef GRIPPER_H
#define GRIPPER_H

#include <Arduino.h>
#include <Servo.h>

#include "Constants.h"

using namespace Constants;

class Gripper {
private:
    Servo gripper; // Servo object to control the servo
    int servo_pin;  // Pin connected to servo
    
    void Open(); // Moves servo to open position
    void Close(); // Moves servo to closed position
    
    enum class GripperState{
        OPEN = 0;
        CLOSED = 1
    };
    
    GripperState griper_state_ = GripperState::OPEN;

public:
    // Constructor: initializes the gripper pins
    Gripper(int servo_pin);
    
    // Class methods
    void Init(); // Configure the pins and connect the servo
    void Update(); // Handles the state machine logic
    void SetState(int state); // Sets the state of the gripper
};

#endif
