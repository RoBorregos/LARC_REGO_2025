/*
 * @file statemanager.cpp
 * @date 01/04/2025
 * @author Juan Pablo Gutiérrez & Dana E. Torres Estrada
 *
 * @brief Implementation file for the StateManager class, which manages the robot's state and subsystems.
 */

#include "statemanager.hpp"
/* 
StateManager::StateManager() : state_(RobotState::INIT), calcTrackStartTime_(0),
                               followTrackStartTime_(0), searchingRight_(false), pickingTime_(0), pickingBall_(false) {}

void StateManager::stateAction()
{
    switch (state_)
    {
    case RobotState::INIT:
        // drive_->setup();
        elevator_->setup();
        gripper_->Init();
        gripper_->CameraOriented();
        // Initialize other systems as needed

        instructionHandler_->begin(); // Initialize I2C communication with vision

        calcTrackStartTime_ = millis();
        break;

    case RobotState::IDLE:
        drive_->moveForward(0);
        elevator_->moveToHeight(elevator_->kIdleLevel);
        gripper_->Close();
        break;

    case RobotState::CALC_TRACK:
        if (!searchingRight_)
        {
            // primero debe mandar que avance hacia adelante
            drive_->moveForward(200);
            // si pasa 10 segundos, manda que avance hacia la derecha
            if (millis() - calcTrackStartTime_ > 10000)
            {
                // si encuentra pelotas, manda detenerse
                searchingRight_ = true;
                // si esta avanzando a la derecha y encuentra pelotas, manda detenerse
                calcTrackStartTime_ = millis();
                // si no encuentra pelotas, y pasan 20 segundos, manda a que se detenga y idle
            }
        }
        // si no encuentra pelotas, y pasan 20 segundos, manda a que se detenga y idle
    }
    else
    {
        drive_->moveRight(150);
        if (instructionHandler_->foundBall())
        {
            drive_->stop();
            setState(RobotState::FOLLOW_TRACK);
        }
        else if (millis() - calcTrackStartTime_ > 20000)
        {
            drive_->stop();
            setState(RobotState::IDLE);
        }
        break;

    case RobotState::FOLLOW_TRACK:
        drive_->moveForward(200);

        if (millis() - followTrackStartTime_ > 10000 && !instructionHandler_->foundBall())
        {
            drive_->moveRight(100); // Start lateral search
            followTrackStartTime_ = millis();
        }
        else if (instructionHandler_->foundBall())
        {
            drive_->stop();
            setState(RobotState::FETCH_BEAN);
        }
        break;

    case RobotState::FETCH_BEAN:
        if (instructionHandler_->foundBall())
        {
            // Alineación precisa si es necesario
            // checar si hay pekota
            setState(RobotState::PICK_BEAN);
        }
        else
        {
            setState(RobotState::IDLE); // Fallo en detección
        }
        break;

    case RobotState::PICK_BEAN:
        gripper_->Open();
        gripper_->Run();
        delay(2000); // Esperar a que la gripper agarre la pelota
        // mover a la siguiente pelota
        break;

    case RobotState::DROP_BEAN:
        break;

    case RobotState::FINISH:
        gripper_->Close();
        drive_->moveBackward(200);
        delay(3000);
        drive_->moveForward(0);
        elevator_->moveToHeight(elevator_->kIdleLevel);
        break;

    default:
        break;
    }
}

void StateManager::stateTransition()
{
    switch (state_)
    {
    case RobotState::INIT:
        setState(RobotState::CALC_TRACK);
        break;

    case RobotState::IDLE:
        break;

    case RobotState::CALC_TRACK:
        // Check conditions to transition to the next state
        break;

    case RobotState::FOLLOW_TRACK:
        if (instructionHandler_->foundBean()) // detecta pelota
            setState(RobotState::PICK_BEAN);
        break;

    case RobotState::FETCH_BEAN:
        break;

    case RobotState::PICK_BEAN:
        // if completado, ya se recogieron todas las pelotas
        setState(RobotState::FINISH);
        break;

    case RobotState::DROP_BEAN:
        break;

    case RobotState::FINISH:
        break;

    default:
        // tendremos un case ERROR?
        break;
    }
}

void StateManager::setState(RobotState state)
{
    if (state == RobotState::CALC_TRACK)
    {
        calcTrackStartTime_ = millis();
        searchingRight_ = false;
    }
    if (state == RobotState::FOLLOW_TRACK)
    {
        followTrackStartTime_ = millis();
    }
    state_ = state;
}

RobotState StateManager::getState() const
{
    return state_;
} */