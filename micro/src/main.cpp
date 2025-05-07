/**
 * LARC REGO 2025
 *
 * @Roborregos
 */

#include <Arduino.h>
#include <Wire.h>
#include <dcmotor.hpp>
#include "subsystem/Drive/drive.hpp"
#include "constants/pins.h"
#include "../lib/math/odometry.hpp"
#include "subsystem/Gripper/Gripper.hpp"
#include "constants/constants.h"
#include "pose2d.hpp"
#include "subsystem/LowerSorter/LowerSorter.hpp"
#include "subsystem/UpperSorter/UpperSorter.hpp"
#include "robot/statemanager.hpp"
#include "RobotState.h"

StateManager state_manager;

void setup()
{
  Serial.begin(9600);
  Wire.begin();

  state_manager.setState(RobotState::INIT);
}

void loop()
{
  state_manager.update();
}

/* void setup()
{
  Serial.begin(9600);
  Wire.begin();

  drive.setState(0);
  drive.acceptHeadingInput(Rotation2D::fromDegrees(0));

  interrupts();
}

void loop()
{
  unsigned long currentMillis = millis();
  drive.update();
  drive.acceptInput(0, 100, 0);

  Pose2D pose = drive.getPose();
  Serial.println(pose.getTheta().getDegrees());
  if (currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;
  }
} */