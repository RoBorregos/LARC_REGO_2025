/*
 * @file LineSensor.cpp
 * @date 07/05/2025
 * @author Brisma Alvarez Valdez
 *
 * @brief Cpp file of the Almacen class to control two servos.
 */

#include "LineSensor.h"

/*LineSensor::LineSensor() {
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
}*/

LineSensor::LineSensor() {}

void LineSensor::update() {
  if (!Serial.available()) return;

  String received = Serial.readStringUntil('\n');
  received.trim();

  if (received.startsWith("Left:")) {
    String value = received.substring(5);
    value.trim();
    if (value == "YES") {
      left_detected_ = true;
      right_detected_ = false;
    } else {
      left_detected_ = false;
    }
  } else if (received.startsWith("Right:")) {
    String value = received.substring(6);
    value.trim();
    if (value == "YES") {
      right_detected_ = true;
      left_detected_ = false;
    } else {
      right_detected_ = false;
    }
  }
}

bool LineSensor::leftDetected() {
  update(); // to avoid having to modify the statemachine
  return left_detected_;
}
bool LineSensor::rightDetected() {
  update(); // to avoid having to modify the statemachine
  return right_detected_;
}

