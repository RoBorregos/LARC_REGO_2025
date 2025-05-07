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

// StateManager state_manager_;
DCMotor front_left_(Pins::kUpperMotors[0], Pins::kUpperMotors[1], Pins::kPwmPin[0],
                    false, Pins::kEncoders[0], LOW, 1, DriveConstants::kWheelDiameter);
DCMotor front_right_(Pins::kUpperMotors[2], Pins::kUpperMotors[3], Pins::kPwmPin[1],
                     true, Pins::kEncoders[1], LOW, 2, DriveConstants::kWheelDiameter);
DCMotor back_left_(Pins::kLowerMotors[0], Pins::kLowerMotors[1], Pins::kPwmPin[2],
                   false, Pins::kEncoders[2], HIGH, 3, DriveConstants::kWheelDiameter);
DCMotor back_right_(Pins::kLowerMotors[2], Pins::kLowerMotors[3], Pins::kPwmPin[3],
                    true, Pins::kEncoders[3], LOW, 4, DriveConstants::kWheelDiameter);
void setup()
{
  Serial.begin(9600);
  Wire.begin();
  // state_manager_.setState(RobotState::INIT);

  interrupts();
}

void loop()
{
  // state_manager_.update();
  front_left_.move(100);
  delay(2000);
  front_left_.stop();
  delay(2000);
  front_right_.move(100);
  delay(2000);
  front_right_.stop();
  delay(2000);
  back_left_.move(100);
  delay(2000);
  back_left_.stop();
  delay(2000);
  back_right_.move(100);
  delay(2000);
  back_right_.stop();
  delay(2000);
}