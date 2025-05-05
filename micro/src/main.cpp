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
#include "subsystem/LowerSorter/LowerSorter.hpp"
#include "subsystem/UpperSorter/UpperSorter.hpp"

Drive drive = Drive();
Gripper gripper = Gripper();
LowerSorter lower_sorter = LowerSorter();
UpperSorter upper_sorter = UpperSorter();
/* #include <Servo.h>
Servo servo = Servo(); */

// Timing variables
unsigned long lastUpdateTime = 0;
const unsigned long UPDATE_INTERVAL = 50;

void setup()
{
  Serial.begin(9600);
  Wire.begin();

  drive.setState(0);
  drive.acceptHeadingInput(Rotation2D(0));
  interrupts();
}

void loop()
{
  unsigned long currentTime = millis();
  drive.update();
  gripper.update();
  lower_sorter.update();
  upper_sorter.update();

  if (currentTime - lastUpdateTime >= UPDATE_INTERVAL)
  {
    static unsigned long lastStateChangeTime = 0;
    static bool gripperState = false;
    static int lowerSorterState = 0; // Start with state 0
    static int upperSorterState = 0; // Start with state 0

    if (currentTime - lastStateChangeTime >= 3000)
    {
      gripperState = !gripperState;
      gripper.setState(gripperState ? 1 : 0);

      // Cycle through states 0, 1, 2
      lowerSorterState = (lowerSorterState + 1) % 3;
      Serial.print("Moving lower sorter to state: ");
      Serial.println(lowerSorterState);
      lower_sorter.setState(lowerSorterState);

      upperSorterState = (upperSorterState + 1) % 3;
      upper_sorter.setState(upperSorterState);

      lastStateChangeTime = currentTime;
    }

    lastUpdateTime = currentTime;
  }
}