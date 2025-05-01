/**
 * LARC 2025
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
#include "subsystem/Intake/Intake.hpp"
#include "constants/constants.h"
#include "pose2d.hpp"
/* Drive drive = Drive();
Gripper gripper = Gripper();
Intake intake = Intake(); */

DCMotor frontleft(Pins::kUpperMotors[0], Pins::kUpperMotors[1], Pins::kPwmPin[0], 
               false, Pins::kEncoders[0], LOW, 1, DriveConstants::kWheelDiameter);

// Timing variables
unsigned long lastUpdateTime = 0;
const unsigned long UPDATE_INTERVAL = 50; // 50ms update interval

void setup()
{
  Serial.begin(9600);
  Wire.begin();
/* 
  drive.setState(0);
  gripper.setState(1);
  intake.setState(1);
  drive.acceptHeadingInput(Rotation2D(0)); */
  interrupts();
}

void loop()
{
  unsigned long currentTime = millis();
  //drive.update();
  //gripper.update();
  //intake.update();

  frontleft.move(100);

  double encoder_count = frontleft.getPositionRotations();
  // Check if it's time to update
  if (currentTime - lastUpdateTime >= UPDATE_INTERVAL)
  {
    Serial.println("Encoder Count: " + String(encoder_count));

    lastUpdateTime = currentTime;
  }

  if (encoder_count >= 1)
  {
    frontleft.move(0);
  }
}