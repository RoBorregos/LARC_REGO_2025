#include "Gripper.h"

#define SERVO_PIN 9
#define IN1 7
#define IN2 8
#define PWM 6

Gripper gripper(SERVO_PIN, IN1, IN2, PWM);

void setup() {
    gripper.attach();
}

void loop() {
    gripper.open();
    gripper.run();
    gripper.close();
    delay(2000);
}
