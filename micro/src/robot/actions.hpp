#pragma once

#include "subsystem/Drive/Drive.hpp"
#include "subsystem/Elevator/Elevator.hpp"
#include "subsystem/Gripper/Gripper.hpp"
#include "subsystem/LowerSorter/LowerSorter.hpp"
#include "subsystem/UpperSorter/UpperSorter.hpp"
#include "subsystem/Vision/CameraLower.hpp"
#include "subsystem/Vision/CameraUpper.hpp"
#include "PID_v1.h"

extern Drive drive_;
extern Elevator elevator_;
extern Gripper gripper_;
extern LowerSorter lower_sorter_;
extern UpperSorter upper_sorter_;
extern CameraLower cam_low_;
extern CameraUpper cam_up_;

PIDController centerPID_(VisionConstants::kCenterPIDKp, VisionConstants::kCenterPIDKi, VisionConstants::kCenterPIDKd, VisionConstants::kCenterPIDOutputMin, VisionConstants::kCenterPIDOutputMax);

bool centerWithObject(double elapsed_time);
bool exitStart(double elapsed_time);
bool searchForTrees(double elapsed_time);
bool goStorageMudo(double elapsed_time);
bool goStoreGrown(double elapsed_time);
bool goStorageOvergrown(double elapsed_time);
bool dropBeans(double elapsed_time);
bool goLeftLine(double elapsed_time);
bool goRightLine(double elapsed_time);
bool pickMidLevelBean();
bool pickLowLevelBean();

