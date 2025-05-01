/*
 * @file Almacen.cpp
 * @date 25/04/2025
 * @author Brisma Alvarez Valdez
 *
 * @brief Implementation of the Almacen class to control two servos.
 */

#include "Almacen.h"

// Constructor: Initializes the servo pins.
Almacen::Almacen(int servoSelectorPin, int servoContainerPin)
    : selector_pin(servoSelectorPin), container_pin (servoContainerPin) {}

// Method to configure the servo selector pins
void Almacen::InitSelector() {
    servo_selector.attach(selector_pin);
    servo_selector.write(AlmacenConstants::kInitSelectorAngle);
}

// Method to configure the servo container pins
void Almacen::InitContainer() {
    servo_container.attach(container_pin);
    servo_container.write(AlmacenConstants::kInitContainerAngle);
}

// Method to classify the balls
void Almacen::ClassifyBalls(){
    if(totalCount < 14){
        servo_selector.write(AlmacenConstants::kLeftAngle);
    }
    else if (totalCount > 14){
        servo_selector.write(AlmacenConstants::kRightAngle);
    }
}

// Method to drop the balls
void Almacen::DropBalls(){
    servo_selector.write(AlmacenConstants::kDropLeftAngle);
    delay(AlmacenConstants::KDropDelay);
    servo_selector.write(AlmacenConstants::KDropRightAngle);
    delay(AlmacenConstants::KDropDelay);
}

// Method to update the state machine
void Almacen::Update(){
    switch (almacen_state_){
        case AlmacenState::IDLE:
            break;
        case AlmacenState::STORING:
            ClassifyBalls();
            break;
        case AlmacenState::DROPPING:
            DropBalls();
            break;
    }
}

// Method to set the state of the almacen
void Almacen::SetState (int state){
    if (state == static_cast<int>(AlmacenState::IDLE)){
        almacen_state_ = AlmacenState::IDLE; }
    else if (state == static_cast<int>(AlmacenState::STORING)){
        almacen_state_ = AlmacenState::STORING; }
    else if (state == static_cast<int>(AlmacenState::DROPPING)){
        almacen_state_ = AlmacenState::DROPPING;}
    }
