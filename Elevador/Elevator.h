/*
 * @file Elevador.h
 * @date 25/04/2025
 * @author Brisma Alvarez Valdez
 *
 * @brief Head file of the Elevador class to control a stepper motor.
 */

#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <Arduino.h>

#include "Constants.h"

using namespace Constants;

class Elevator {
private:
    // Pines
    const int step_pin;
    const int dir_pin;

    float actual_position_cm;

    // Métodos privados para mover el motor
    void MoveUp(int steps);
    void MoveDown(int steps);
    int translateCmToSteps(float distance_cm);
    
    // Métodos para moverse a niveles específicos
    void Init(float initial_dist);
    void LowerLevel(float lower_dist);
    void MidLevel(float mid_dist);
    void UpperLevel(float upper_dist);
    void MaxLevel(float max_dist);
    
    // States
    enum class ElevatorState {
        IDLE = 0,
        INIT = 1,
        LOWER = 2,
        MID = 3,
        UPPER = 4,
        MAX = 5
    };
    
    ElevatorState elevator_state_ = ElevatorState::IDLE;

public:
    // Constructor
    Elevator(int stepPin, int dirPin, float actual_position_cm);

    // Método de inicialización
    void setup();
    void Update(); // Execute state machine logic
    void SetState(int state); // Change state of elevator
};

#endif 
