#include "CameraLower.hpp"

CameraLower::CameraLower() {
    Serial.println("CameraLower inicializada correctamente (simulado)");
}

void CameraLower::receiveData() {
    Serial.println("Datos recibidos desde la cámara inferior (simulado)");
}

void CameraLower::setState(int state) {
    camera_state_ = static_cast<CameraLowerState>(state);
    Serial.print("Estado de CameraLower cambiado a: ");
    Serial.println(state);
}

bool CameraLower::isPoolTooClose() {
    return false;
}

float CameraLower::getOffset_X() {
    return -0.15;
}

float CameraLower::getOffset_Y() {
    return 0.0;
}

bool CameraLower::objectPresent() {
    return true;
}