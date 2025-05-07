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

class CameraUpper {
private:
public:
    // Constructor with initialization
    CameraUpper(); // recibir mensaje de si la inicializacion fue exitosa o no

    // Method to receive Serial data of the Upper Camera from the raspberry
    void receiveData(); // Bean type (MADURO or SOBREMADURO), offset_x, offset_y, distance

    // TODO: Individual getters or a structure??

    int beanPresent(); // 0 =NO, 1=MADURO, 2=SOBREMADURO //!para ROBO es un bool
    float getBeanOffset_X();
};

#endif // CAMERAUPPER_H