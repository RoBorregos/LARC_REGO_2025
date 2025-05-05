/**
 * @file constants.h
 * @date 01/05/2025
 * @author Brisma Alvarez Valdez
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
        constexpr float kInitLevel = 0.0; // in cm
        constexpr float kMaxLevel = 20.0; // in cm

        constexpr float kStepsPerRevolution = 200;
        constexpr float kStepperRadius = 0.75; // in cm
    }

    namespace GripperConstants {
        constexpr int kOpenAngle = 60;
        constexpr int kClosedAngle = 20;
    }

    namespace AlmacenConstants {
        constexpr int kLeftAngle = 60;
        constexpr int kRightAngle = 120;
        constexpr int kDropLeftAngle = 140;
        constexpr int kDropRightAngle = 70;
        constexpr int kInitSelectorAngle = 0;
        constexpr int kInitContainerAngle = 0;
        constexpr int kDropDelay = 10000;
    }

    namespace DriveConstants {
        constexpr float kWheelDiameter = 0.0762; // in m
        constexpr float kWheelRadius = kWheelDiameter / 2.0; // in m
        constexpr float kWheelCircumference = 2 * M_PI * kWheelRadius; // in m
    }
}


#endif
