/*
 * @file statemanager.cpp
 * @date 01/04/2025
 * @author Juan Pablo Gutiérrez & Dana E. Torres Estrada
 *
 * @brief Header file for the StateManager class, which manages the robot's state and subsystems.
 */

#ifndef STATE_MANAGER_HPP
#define STATE_MANAGER_HPP

#include <Arduino.h>
#include "system.hpp"
#include "../systems/RobotState.h"
#include "system.hpp"
#include "../subsystem/Elevator/Elevator.hpp"
#include "../subsystem/Gripper/Gripper.hpp"
#include "InstructionHandler.h"
#include "../subsystem/Drive/drive.hpp"

class StateManager {
private:
    /*System* systems_[5];

    systems[0] = new Drive();
    systems[1] = new Elevator();
    systems[2] = new Gripper();*/

    Drive* drive_;
    Elevator* elevator_;
    Gripper* gripper_;

    InstructionHandler* instructionHandler_ = new InstructionHandler(8);  // Dirección I2C

    RobotState state_;

public:
    StateManager();
    void stateAction();
    void stateTransition();
    void setState(RobotState state);
    RobotState getState() const;
};

#endif // STATE_MANAGER_HPP