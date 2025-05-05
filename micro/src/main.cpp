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
#include "constants/constants.h"
#include "pose2d.hpp"
Drive drive = Drive();
Gripper gripper = Gripper();

#include <Servo.h>
Servo servo = Servo();

// Timing variables
unsigned long lastUpdateTime = 0;
const unsigned long UPDATE_INTERVAL = 50; // 50ms update interval

void setup()
{
  Serial.begin(9600);
/*  Wire.begin();

  drive.setState(0);
  drive.acceptHeadingInput(Rotation2D(0)); */
  servo.attach(Pins::kGripperServoPin);
  interrupts();
}

void loop()
{
  servo.write(GripperConstants::kOpenAngle);
  delay(1000);
  servo.write(GripperConstants::kClosedAngle);
  delay(1000);
 /*  unsigned long currentTime = millis();
  drive.update();
  gripper.update();

  // Check if it's time to update
  if (currentTime - lastUpdateTime >= UPDATE_INTERVAL)
  {
    static unsigned long lastStateChangeTime = 0;
    static bool gripperState = false;

    if (currentTime - lastStateChangeTime >= 4000) // 4000ms = 4 seconds
    {
      Serial.println("HII");
      gripperState = !gripperState; // Toggle the state
      gripper.setState(gripperState ? 1 : 0);
      lastStateChangeTime = currentTime;
    }
    
    lastUpdateTime = currentTime;
  } */
}