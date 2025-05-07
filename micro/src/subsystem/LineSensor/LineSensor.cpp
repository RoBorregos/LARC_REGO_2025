/*
 * @file LineSensor.cpp
 * @date 07/05/2025
 * @author Brisma Alvarez Valdez
 *
 * @brief Cpp file of the Almacen class to control two servos.
 */

#include "LineSensor.h"

LineSensor::LineSensor() {
  this->leftPin = Pins::kLineSensorLeftPin;
  this->rightPin = Pins::kLineSensorRightPin;
}

void LineSensor::begin() {
  pinMode(leftPin, INPUT);
  pinMode(rightPin, INPUT);
}

bool LineSensor::leftDetected() {
  return digitalRead(leftPin) == HIGH;
}

bool LineSensor::rightDetected() {
  return digitalRead(rightPin) == HIGH;
}

