/*
 * @file Elevador.cpp
 * @date 25/04/2025
 * @author Brisma Alvarez Valdez
 *
 * @brief Implementation of the Elevador class to control a stepper motor
 */
#include "Elevator.hpp"

Elevator::Elevator()
    : step_pin(Pins::kStepperPin), dir_pin(Pins::kDirPin), limit_pin(Pins::kLimitPin), actual_position_cm(0.0), target_position_cm(0.0)
{
    pinMode(step_pin, OUTPUT);
    pinMode(dir_pin, OUTPUT);
    digitalWrite(dir_pin, LOW);
    pinMode(limit_pin, INPUT_PULLUP);
}

void Elevator::Move(int steps)
{
    if (steps > 0)
    {
        digitalWrite(dir_pin, LOW);
    }
    else
    {
        digitalWrite(dir_pin, HIGH);
    }

    for (int i = 0; i < steps; i++)
    {
        digitalWrite(step_pin, HIGH);
        delayMicroseconds(800);
        digitalWrite(step_pin, LOW);
        delayMicroseconds(800);
    }
}

int Elevator::translateCmToSteps(float distance_cm)
{
    return (int)((distance_cm / (2.0 * M_PI * ElevatorConstants::kStepperRadius)) * ElevatorConstants::kStepsPerRevolution);
}

// Metodo para ver si el limit esta presionado
bool Elevator::GetLimitState()
{
    return digitalRead(limit_pin) == LOW;
}

// Método para actualizar la lógica de la máquina de estados
void Elevator::update()
{
    switch (elevator_state_){
        case ElevatorState::HOME:
            target_position_cm = ElevatorConstants::kIdleLevel;
            break;
        case ElevatorState::LOWER:
            target_position_cm = ElevatorConstants::kLowerLevel;
            break;
        case ElevatorState::MID:
            target_position_cm = ElevatorConstants::kMidLevel;
            break;
        case ElevatorState::UPPER:
            target_position_cm = ElevatorConstants::kUpperLevel;
            break;
    }

    if (GetLimitState())
    {
        elevator_state_ = ElevatorState::HOME;
        actual_position_cm = 0.0;
    }

    Move(translateCmToSteps(target_position_cm - actual_position_cm));
}

void Elevator::setState(int state)
{
    elevator_state_ = static_cast<ElevatorState>(state);
}
