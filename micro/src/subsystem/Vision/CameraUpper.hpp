/*
 * @file CameraUpper.h
 * @date 01/05/2025
 * @author Dana E. Torres Estrada
 *
 * @brief Header file for receiving Upper Camera data from serial
 */

#ifndef CAMERAUPPER_H
#define CAMERAUPPER_H

#include <Arduino.h>
#include "constants/constants.h"
using namespace Constants;

class CameraUpper {
private:
    float current_offset_x_ = 0.0;
    float current_offset_y_ = 0.0;
    BeanConstants::BeanType current_bean_type_ = BeanConstants::NONE;

public:
    CameraUpper(); // Constructor

    BeanConstants::BeanType beanPresent();

    float getBeanOffset_X();
    float getBeanOffset_Y();

    // Method to receive Serial data of the Upper Camera from the raspberry
    void update();
};

#endif // CAMERAUPPER_H