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
Drive drive = Drive();
Gripper gripper = Gripper();
Intake intake = Intake();

// Timing variables
unsigned long lastUpdateTime = 0;
const unsigned long UPDATE_INTERVAL = 50; // 50ms update interval

void setup()
{
  Serial.begin(9600);
  Wire.begin();

  drive.setState(0);
  gripper.setState(0);
  intake.setState(0);
  drive.acceptHeadingInput(Rotation2D(0));
  interrupts();
}

void loop()
{
  /*unsigned long currentTime = millis();
  drive.update();
  gripper.update();
  intake.update();

  // Check if it's time to update
  if (currentTime - lastUpdateTime >= UPDATE_INTERVAL)
  {
    Serial.println("HII");
    gripper.setState(1);
    intake.setState(1);

  }*/

  /*for (int velocidad = 200; velocidad >= -200; velocidad--) {
    if (velocidad > 0) {
      drive.moveForward(velocidad);
    } else if (velocidad < 0) {
      drive.moveBackward(-velocidad); // usamos valor positivo para velocidad
    } 
    delay(10); // Delay para observar los cambios
  }*/
    /*for (int velocidad = -200; velocidad <= 200; velocidad++) {
    if (velocidad < 0) {
      drive.moveBackward(-velocidad); // usar valor positivo
    } else if (velocidad > 0) {
      drive.moveForward(velocidad);
    }
    delay(10); 
  }

  while (true); */
  drive.moveForward(100);
}