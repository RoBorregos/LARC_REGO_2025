/*
 * @file LineSensor.h
 * @date 07/05/2025
 * @author Brisma Alvarez Valdez
 *
 * @brief Head file of the Line Sensor
 */

#ifndef LINESENSOR_H
#define LINESENSOR_H

#include "constants/pins.h"
#include "Arduino.h"

class LineSensor {
  private:
    int leftPin;
    int rightPin;

  public:
    LineSensor();
    void begin();
    bool leftDetected();
    bool rightDetected();
};

#endif

