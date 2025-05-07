/*
 * @file StateManager.hpp
 * @date 01/04/2025
 * @author  Dana E. Torres Estrada
 *
 * @brief Header file for the StateManager class, which manages the robot's state and subsystems.
*/
#ifndef STATE_MANAGER_HPP
#define STATE_MANAGER_HPP

#include <Arduino.h>
#include "RobotState.h"
#include "../subsystem/Elevator/Elevator.hpp"
#include "../subsystem/Gripper/Gripper.hpp"
#include "../subsystem/Drive/drive.hpp"
#include "../subsystem/LowerSorter/LowerSorter.hpp"
#include "../subsystem/UpperSorter/UpperSorter.hpp"
#include "system.hpp"
#include "actions.hpp"
class StateManager {
private:
    Elevator elevator_;
    Gripper gripper_;
    Drive drive_;
    LowerSorter lower_sorter_;
    UpperSorter upper_sorter_;
    //Almacen* almacen_; //Rego
    //Revolver* revolver_; //Robo
    //LineSensor* line_sensor_;

    RobotState state_;

    //TODO: sacar las constantes hardcodeadas al hpp

    //* esta bien sus esta maquina

    // Constants for specific robot
    const int mid_level_beans_ = 4; // REGO //2 para ROBO
    const int low_level_beans_ = 3; // REGO 3 o 2 // 1 para ROBO

    // Control variables
    long start_time_ = 0;
    bool direction_ = false; // 0 or false = left | 1 or true = right
    int current_tree_ = 0;
    int current_beans_ = 0;
    bool droped_SOBREMADURO = false;
    long state_start_time_ = 0; 

public:
    StateManager();
    void stateAction(); // Method to run state
    void stateTransition(); // Method to change state
    void setState(RobotState state);
    RobotState getState();
    unsigned long getTimeSpent();
    void update();
};

#endif // STATE_MANAGER_HPP
