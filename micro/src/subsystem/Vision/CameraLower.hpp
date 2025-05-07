/*
* @file Elevator.h
* @date 01/05/2025
* @author Dana E. Torres Estrada
*
* @brief Header file for receiving Upper Camera data from serial
*/

#ifndef CAMERALOWER_H
#define CAMERALOWER_H

#include <Arduino.h>
#include "../systems/system.hpp"

class CameraLower : public System {
private:
public:
    // Constructor with initialization
    CameraLower(); // recibir mensaje de si la inicializacion fue exitosa o no

    // Method to receive Serial data of the Upper Camera from the raspberry
    void receiveData(); // Bean type (MADURO or SOBREMADURO), offset_x, offset_y, distance

    // Method to define what the lower camera will be searching for
    void setState(int state) override;

    bool isPoolTooClose(); // calibrar con distancia o booleano

    float getOffset_X();

    float getOffset_Y();

    bool objectPresent();

    // TODO: Individual getters or a structure??
    enum class CameraLowerState {
        AVOID_OBSTACLES = 0,
        FETCH_TREES = 1,
        FETCH_STOREHOUSE_MADURO = 2,
        FETCH_STOREHOUSE_SOBREMADURO = 3,
    };

    CameraLowerState camera_state_ = CameraLowerState::AVOID_OBSTACLES;
};

#endif // CAMERALOWER_H