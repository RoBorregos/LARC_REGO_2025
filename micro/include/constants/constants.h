/**
 * @file constants.h
 * @date 24/04/2025
 * @author Juan Pablo Gutiérrez
 * 
 * @brief Constants for the robot.
 */

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <cmath>

namespace Constants {

    namespace ElevatorConstants {
        constexpr float kUpperLevel = 15.0; // in cm
        constexpr float kMidLevel = 10.0; // in cm
        constexpr float kLowerLevel = 5.0; // in cm
        constexpr float kIdleLevel = 0.0; // in cm

        constexpr float kStepsPerRevolution = 200;
        constexpr float kStepperRadius = 0.75; // in cm

        constexpr float kP = 0.01;
        constexpr float kI = 0.00;
        constexpr float kD = 0.00;
    }

    namespace GripperConstants {
        constexpr int kOpenAngle = 60;
        constexpr int kClosedAngle = 20;
    }

    namespace IntakeConstants {
        constexpr int kIntakeSpeed = 200;
        constexpr int kOuttakeSpeed = -200;
    }

    namespace DriveConstants {
        constexpr float kWheelDiameter = 0.0762; // in m
        constexpr float kWheelRadius = kWheelDiameter / 2.0; // in m
        constexpr float kWheelCircumference = 2 * M_PI * kWheelRadius; // in m
    }
}


#endif