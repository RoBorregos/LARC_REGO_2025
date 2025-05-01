/*
 * @file Almacen.h
 * @date 25/04/2025
 * @author Brisma Alvarez Valdez
 *
 * @brief Head file of the Almacen class to control two servos.
 */

#ifndef ALMACEN_H
#define ALMACEN_H

#include <Arduino.h>
#include <Servo.h>
#include "Constants.h"

using namespace Constants;


class Almacen {
private:
    Servo servo_selector; // Servo object to control the servo for the classification of balls to store en each compartment
    Servo servo_container; // Servo object to control the servo for open the container to drop the balls
    int selector_pin, container_pin;  // Pins connected to servo
    
    // Angles for each case (drop the balls, classification and initial positions)
    /*int left_angle = 60;
    int right_angle = 120;
    int drop_left_angle = 70;
    int drop_right_angle = 140;
    int init_selector_angle = 0;
    int init_container_angle = 0;
    const int KDropDelay = 10000; */
    
    int totalCount = 0;
    
    void ClassifyBalls(); // Classify the balls in the container depending of the type
    void DropBalls(); // Open the compartment depending of the type of container
    
    enum class AlmacenState{
        IDLE = 0;
        STORING = 1,
        DROPPING = 2
    };
    
    AlmacenState almacen_state_ = AlmacenState::IDLE;

public:
    // Constructor: initializes the gripper pins
    Almacen(int selector_pin, int container_pin);
    
    // Class methods
    void InitSelector(); // Configure the pin and connect the selector servo and stablish a initial position
    void InitContainer();// Configure the pin and connect the container servo and stablish a initial position
    void Update(); // Handles the state machine logic
    void SetState (int state); // Sets the state of the almacen
};

#endif
