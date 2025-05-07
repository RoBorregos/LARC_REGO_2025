/*
 * @file Elevador.cpp
 * @date 25/04/2025
 * @author Brisma Alvarez Valdez
 *
 * @brief Implementation of the Elevador class to control a stepper motor
 */
#include "Elevator.h"

// Constructor
Elevator::Elevator(int stepPin, int dirPin, float actual_position_cm, int limit_pin)
    : step_pin(stepPin), dir_pin(dirPin), actual_position_cm(0.0), limit_pin(limit_pin) {}

// Método de inicialización
void Elevator::setup() {
    pinMode(step_pin, OUTPUT);
    pinMode(dir_pin, OUTPUT);
    digitalWrite(dir_pin, LOW);
    pinMode(limit_pin, INPUT_PULLUP); 
}

// Métodos privados para mover el motor
void Elevator::MoveUp(int steps) {
    digitalWrite(dir_pin, LOW); // Establecer dirección
    for (int i = 0; i < steps; i++) {
        digitalWrite(step_pin, HIGH);
        delayMicroseconds(800);
        digitalWrite(step_pin, LOW);
        delayMicroseconds(800);
    }
}

void Elevator::MoveDown(int steps) {
    digitalWrite(dir_pin, HIGH); // Establecer dirección
    for (int i = 0; i < steps; i++) {
        digitalWrite(step_pin, HIGH);
        delayMicroseconds(800);
        digitalWrite(step_pin, LOW);
        delayMicroseconds(800);
    }
}

int Elevator::translateCmToSteps(float distance_cm) {
    return (int)((distance_cm / (2.0 * M_PI * ElevatorConstants::kStepperRadius)) * ElevatorConstants::kStepsPerRevolution);
}

// Métodos públicos para moverse a niveles específicos
void Elevator::Init(float initial_dist) {
    int steps = translateCmToSteps(actual_position_cm - initial_dist);
    MoveDown(steps);
    actual_position_cm = initial_dist;
}

void Elevator::LowerLevel(float lower_dist) {
    float delta = lower_dist - actual_position_cm;
    int steps = translateCmToSteps(abs(delta));

    if (delta > 0) {
        MoveUp(steps);
    } else if (delta < 0) {
        MoveDown(steps);
    }

    actual_position_cm = lower_dist;
}

void Elevator::MidLevel(float mid_dist) {
    float delta = mid_dist - actual_position_cm;
    int steps = translateCmToSteps(abs(delta));

    if (delta > 0) {
        MoveUp(steps);
    } else if (delta < 0) {
        MoveDown(steps);
    }

    actual_position_cm = mid_dist;
}

void Elevator::UpperLevel(float upper_dist) {
    float delta = upper_dist - actual_position_cm;
    int steps = translateCmToSteps(abs(delta));

    if (delta > 0) {
        MoveUp(steps);
    } else if (delta < 0) {
        MoveDown(steps);
    }

    actual_position_cm = upper_dist;
}

void Elevator::MaxLevel(float max_dist) {
    float delta = max_dist - actual_position_cm;
    int steps = translateCmToSteps(abs(delta));

    if (delta > 0) {
        MoveUp(steps);
    } else if (delta < 0) {
        MoveDown(steps);
    }

    actual_position_cm = max_dist;
}

// Metodo para ver si el limit esta presionado 
bool Elevator::LimitState() {
    return digitalRead(limit_pin) == LOW;
}

// Método para actualizar la lógica de la máquina de estados
void Elevator::Update(){
    switch (elevator_state_){
        case ElevatorState::IDLE:
            break;
        case ElevatorState::INIT:
            Init(ElevatorConstants::kInitLevel); // Cambiar
            break;
        case ElevatorState::LOWER:
            LowerLevel(ElevatorConstants::kLowerLevel);
            break;
        case ElevatorState::MID:
            MidLevel(ElevatorConstants::kMidLevel);
            break;
        case ElevatorState::UPPER:
            UpperLevel(ElevatorConstants::kUpperLevel);
            break;
        case ElevatorState::MAX:
            MaxLevel(ElevatorConstants::kMaxLevel);
            break;
    }
}

// Método para establecer el estado del elevador
void Elevator::setState(int state) {
    if (state == static_cast<int>(ElevatorState::IDLE)) {
        elevator_state_ = ElevatorState::IDLE;
    } else if (state == static_cast<int>(ElevatorState::INIT)) {
        elevator_state_ = ElevatorState::INIT;
    } else if (state == static_cast<int>(ElevatorState::LOWER)) {
        elevator_state_ = ElevatorState::LOWER;
    } else if (state == static_cast<int>(ElevatorState::MID)) {
        elevator_state_ = ElevatorState::MID;
    } else if (state == static_cast<int>(ElevatorState::UPPER)) {
        elevator_state_ = ElevatorState::UPPER;
    } else if (state == static_cast<int>(ElevatorState::MAX)) {
        elevator_state_ = ElevatorState::MAX;
    }
}
