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
const unsigned long UPDATE_INTERVAL = 20;

extern Drive drive_;
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

  Pose2D pose = drive_.getPose();
  Serial.println("Theta: " + String(pose.getTheta().getDegrees()));
  delay(UPDATE_INTERVAL);
}