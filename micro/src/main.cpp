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

StateManager state_manager_;
void setup()
{
  Serial.begin(9600);
  Wire.begin();

  state_manager_.setState(RobotState::INIT);

  interrupts();
}

void loop()
{

  state_manager_.update();
  delay(UPDATE_INTERVAL);
}