/*
 * @file CameraUpper.cpp
 * @date 01/05/2025
 * @author Dana E. Torres Estrada
 *
 * @brief Implementation file for receiving Upper Camera data from serial
 */

#include "CameraUpper.hpp"

//* Constructor
CameraUpper::CameraUpper() {
    // Mensaje de inicialización simulada
    Serial.println("CameraUpper inicializada correctamente (simulado)");
}

void CameraUpper::receiveData() {
    // Simulación de recepción de datos desde Serial
    Serial.println("Datos recibidos desde Raspberry Pi (simulado)");
}

int CameraUpper::beanPresent() {
    // Retornamos un tipo de frijol hardcodeado
    return 1; // 1 = MADURO
}

float CameraUpper::getBeanOffset_X() {
    // Valor hardcodeado de desplazamiento en X
    return 0.25;
}