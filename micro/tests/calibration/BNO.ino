/*
 * @date 07/04/2025
 * @author Hector Tovar
 *
 * @brief Implementation of the correct usage for the BNO since it didn't work on the PCB and has to be configured differently
 */

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

// Uses Wire1 because you we are on SDA 17, SCL 16
Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28, &Wire1);

void setup(void)
{
  Wire1.begin();  // Initializes secondary I2C bus

  Serial.begin(9600);
  while (!Serial); // Waits for the serial port (important for Teensy)
  Serial.println("Orientation Sensor Test");
  Serial.println("");

  /* Initializes the sensor */
  if (!bno.begin())
  {
    Serial.println("Ooops, no BNO055 detected ... Check the wiring or I2C ADDRESS!");
    while (1);
  }

  delay(1000);
  bno.setExtCrystalUse(true);  // Uses the external crystal for better precision
}

void loop(void)
{
  sensors_event_t event;
  bno.getEvent(&event);

  /* Displays orientation data */
  Serial.print("X: ");
  Serial.print(event.orientation.x, 4);
  Serial.print("\tY: ");
  Serial.print(event.orientation.y, 4);
  Serial.print("\tZ: ");
  Serial.print(event.orientation.z, 4);
  Serial.println("");

  Serial.print("Orientation in degrees - ");
  Serial.print("Roll: ");
  Serial.print(event.orientation.x);
  Serial.print("\tPitch: ");
  Serial.print(event.orientation.y);
  Serial.print("\tYaw: ");
  Serial.print(event.orientation.z);
  Serial.println("");

  delay(100);
}
