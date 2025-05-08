/*
 * @file statemanager.cpp
 * @date 01/04/2025
 * @author Juan Pablo Gutiérrez & Dana E. Torres Estrada
 *
 * @brief Implementation file for the StateManager class, which manages the robot's state and subsystems.
*/

#include "statemanager.hpp"

StateManager::StateManager() {}

void StateManager::setState(RobotState state) {
    state_ = state;
    state_start_time_ = 0;
}

RobotState StateManager::getState() {
    return state_;
}

unsigned long StateManager::getTimeSpent() {
    return millis() - start_time_;
}

void StateManager::stateAction() {
    switch (state_) {
        case RobotState::INIT: {
            initStart();
            break;
        }
        case RobotState::EXIT_START: {
            exitStart(getTimeSpent());
            break;
        }
        case RobotState::GO_TREES: {
 
            break;
        }
        case RobotState::AVOID_LEFT_OBSTACLE: {//!checar, algo se ve muy sus
            break;
        }
        case RobotState::AVOID_RIGHT_OBSTACLE: { //!checar, algo se ve muy sus

            break;
        }
        case RobotState::GO_LEFT_LINE: {

            break;
        }
        case RobotState::GO_RIGHT_LINE: {
     
            break;
        }
        case RobotState::PICK_MID_LEVEL: {

            break;
        }
        case RobotState::PICK_LOW_LEVEL: {

            break;
        }
        case RobotState::GO_STORAGE_MADURO: {//TODO

            break;
        }
        case RobotState::GO_STORAGE_SOBREMADURO: {//TODO
            break;
        }
        case RobotState::DROP_BEANS: {
           
            break;
        }
        default:
            break;
    }
}

void StateManager::update() {
    globalUpdate();
    stateAction();
}

