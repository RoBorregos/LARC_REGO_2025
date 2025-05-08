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

void StateManager::stateTransition() {
    switch (state_) {
        case RobotState::INIT: {
            setState(RobotState::EXIT_START);
            break;
        }
        case RobotState::EXIT_START: {
            setState(RobotState::GO_TREES);
            break;
        }
        case RobotState::GO_TREES: {
            setState(RobotState::SEARCH_TREES);
            break;
        }
        case RobotState::AVOID_LEFT_OBSTACLE: {
            setState(RobotState::GO_TREES);
            break;
        }
        case RobotState::AVOID_RIGHT_OBSTACLE: {
            setState(RobotState::GO_TREES);
            break;
        }
        case RobotState::GO_LEFT_LINE: {
            setState(RobotState::SEARCH_TREES);
            break;
        }
        case RobotState::GO_RIGHT_LINE: {
            setState(RobotState::SEARCH_TREES);
            break;
        }
        case RobotState::SEARCH_TREES: {
            current_tree_++;
            setState(RobotState::PICK_MID_LEVEL);
            break;
        }
        case RobotState::PICK_MID_LEVEL: {
            current_beans_++;
            if (current_beans_>=mid_level_beans_) {
                if (current_tree_==2){
                    setState(RobotState::PICK_LOW_LEVEL);
                }
                else{
                    setState(RobotState::GO_LEFT_LINE);
                }
                current_beans_ = 0;
            }
            break;
        }
        case RobotState::PICK_LOW_LEVEL: {
            current_beans_++;
            if (current_beans_>=low_level_beans_) {
                setState(RobotState::GO_STORAGE_SOBREMADURO);
                current_beans_ = 0;
            }
            break;
        }
        case RobotState::GO_STORAGE_MADURO: {
            setState(RobotState::DROP_BEANS);
            break;
        }
        case RobotState::GO_STORAGE_SOBREMADURO: {
            setState(RobotState::DROP_BEANS);
            break;
        }
        case RobotState::DROP_BEANS: {
            setState(RobotState::SEARCH_TREES);
            break;
        }
        default:
            break;
    }
}

void StateManager::update() {
    globalUpdate();
    bool action_completed = false;
    
    // Execute the current state's action and get completion status
    switch (state_) {
        case RobotState::INIT: {
            action_completed = initStart();
            break;
        }
        case RobotState::EXIT_START: {
            action_completed = exitStart(getTimeSpent());
            break;
        }
        case RobotState::GO_TREES: {
            action_completed = goTreeZone(getTimeSpent());
            break;
        }
        case RobotState::AVOID_LEFT_OBSTACLE: {
            break;
        }
        case RobotState::AVOID_RIGHT_OBSTACLE: {
            break;
        }
        case RobotState::GO_LEFT_LINE: {
            action_completed = goLeftLimit(getTimeSpent());
            break;
        }
        case RobotState::GO_RIGHT_LINE: {
            action_completed = goRightLine(getTimeSpent());
            break;
        }
        case RobotState::SEARCH_TREES: {
            action_completed = searchForTrees(getTimeSpent());
            break;
        }
        case RobotState::PICK_MID_LEVEL: {
            action_completed = pickBean(getTimeSpent(), 2);
            break;
        }
        case RobotState::PICK_LOW_LEVEL: {
            action_completed = pickBean(getTimeSpent(), 1);
            break;
        }
        case RobotState::GO_STORAGE_MADURO: {
            break;
        }
        case RobotState::GO_STORAGE_SOBREMADURO: {
            break;
        }
        case RobotState::DROP_BEANS: {
            break;
        }
        default:
            break;
    }

    // Only transition to next state if current action is completed
    if (action_completed) {
        stateTransition();
    }
}