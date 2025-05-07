/*
* @file CameraLower.h
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
    float current_offset_x_ = 0.0;
    float current_offset_y_ = 0.0;
    float current_distance_ = 0.0;
    bool object_present_ = false;
    bool object_too_close_ = false;
    bool bean_storage_type = false; // False = MADURO, True = SOBREMADURO

public:
    CameraLower(); // Constructor
    
    float getOffset_X();
    float getOffset_Y();
    float getObjectDistance();
    bool objectPresent();
    bool isObjectTooClose(); // calibrar con distancia o booleano
    
    enum class CameraLowerState {
        AVOID_OBSTACLES = 0,
        FETCH_TREES = 1,
        FETCH_STOREHOUSE_MADURO = 2,
        FETCH_STOREHOUSE_SOBREMADURO = 3,
    };
    
    CameraLowerState camera_state_ = CameraLowerState::AVOID_OBSTACLES;
    
    // Method to define what the lower camera will be searching for
    void setState(int state) override;

    // Method to receive Serial data of the Upper Camera from the raspberry
    void update();
};

#endif // CAMERALOWER_H