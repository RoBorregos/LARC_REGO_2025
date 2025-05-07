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
    }

    namespace GripperConstants {
        constexpr int kOpenAngle = 60;
        constexpr int kClosedAngle = 5;
    }

    namespace UpperSorterConstants {
        constexpr int kLeftAngle = 0;
        constexpr int kCenterAngle = 90;
        constexpr int kRightAngle = 180;
    }

    namespace LowerSorterConstants {
        constexpr int kLeftAngle = 180;
        constexpr int kCenterAngle = 90;
        constexpr int kRightAngle = 0;
    }

    namespace DriveConstants {
        constexpr float kWheelDiameter = 0.0762; // in m
        constexpr float kWheelRadius = kWheelDiameter / 2.0; // in m
        constexpr float kWheelCircumference = 2 * M_PI * kWheelRadius; // in m

        constexpr float kHeadingControllerKp = 365.0f;
        constexpr float kHeadingControllerKi = 80.0f;
        constexpr float kHeadingControllerKd = 0.0f;
    }

    namespace VisionConstants {
        constexpr float kCenterPIDKp = 0.0f;
        constexpr float kCenterPIDKi = 0.0f;
        constexpr float kCenterPIDKd = 0.0f;
        constexpr float kCenterPIDOutputMin = -255.0f;
        constexpr float kCenterPIDOutputMax = 255.0f;

        constexpr float kCenterOffsetX = 0.0f;
        constexpr float kCenterOffsetY = 10.0f;

    }
}


#endif