/**
 * LARC 2025
 *
 * @Roborregos
 */

#include <Arduino.h>
#include <Wire.h>
#include "pose2d.hpp"
#include "robot/statemanager.hpp"

const unsigned long UPDATE_INTERVAL = 20;

StateManager state_manager_;

double state_start_time = 0;

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

  if (millis() - state_start_time > 3000) {
  } else {

    state_manager_.setState(RobotState::PICK_LOW_LEVEL);
  }

  delay(UPDATE_INTERVAL);
}