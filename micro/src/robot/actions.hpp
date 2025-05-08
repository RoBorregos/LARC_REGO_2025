#pragma once

#include "../subsystem/Drive/Drive.hpp"
#include "../subsystem/Elevator/Elevator.hpp"
#include "../subsystem/Gripper/Gripper.hpp"
#include "../subsystem/LowerSorter/LowerSorter.hpp"
#include "../subsystem/UpperSorter/UpperSorter.hpp"
#include "../subsystem/LineSensor/LineSensor.h"
#include "../subsystem/Vision/Camera.hpp"
#include "PID_v1.h"

extern Drive drive_;
extern Elevator elevator_;
extern Gripper gripper_;
extern LowerSorter lower_sorter_;
extern UpperSorter upper_sorter_;
extern PIDController centerPID_;
extern LineSensor line_sensor_;
extern Camera camera_;

bool centerWithObject(double elapsed_time);
bool initStart();
bool exitStart(double elapsed_time);
bool goTreeZone(double elapsed_time);
bool goLeftLimit(double elapsed_time);
bool goRightLimit(double elapsed_time);
bool searchForTrees(double elapsed_time);
bool goStorageMudo(double elapsed_time);
bool goStoreGrown(double elapsed_time);
bool goStorageOvergrown(double elapsed_time);
bool dropBeans(double elapsed_time);
bool goLeftLine(double elapsed_time);
bool goRightLine(double elapsed_time);
bool pickBean(double elapsed_time, int level);
bool dropBeans(double elapsed_time);
bool globalUpdate();