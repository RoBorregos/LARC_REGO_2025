/*
 * @file LineSensor.h
 * @date 07/05/2025
 * @author Brisma Alvarez Valdez
 *
 * @brief Head file of the Line Sensor
 */

#ifndef LINESENSOR_H
#define LINESENSOR_H

#include <Arduino.h>

/*class LineSensor {
  private:
    int leftPin;
    int rightPin;

  public:
    LineSensor();
    void begin();
    bool leftDetected();
    bool rightDetected();
};*/

class LineSensor {
private:
  bool left_detected_ = false;
  bool right_detected_ = false;

public:
  LineSensor();

  void update();

  bool leftDetected();
  bool rightDetected();
};

#endif

