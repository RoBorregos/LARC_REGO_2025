/**
 * LARC 2025
 *
 * @Roborregos
 */

#include <Arduino.h>
#include <Wire.h>
#include "pose2d.hpp"
#include "robot/statemanager.hpp"
#include "subsystem/Drive/Drive.hpp"
#include "subsystem/LineSensor/LineSensor.h"
const unsigned long UPDATE_INTERVAL = 20;

extern Drive drive_;
extern LineSensor line_sensor_;
void setup()
{
  Serial.begin(9600);
  Wire.begin();

  drive_.acceptHeadingInput(Rotation2D::fromDegrees(0));
  drive_.setState(0);

  interrupts();
}

void loop()
{
  drive_.update();

  if (line_sensor_.leftDetected()) {
    Serial.println("Left detected");
  }
  if (line_sensor_.rightDetected()) {
    Serial.println("Right detected");
  }

  delay(UPDATE_INTERVAL);
}