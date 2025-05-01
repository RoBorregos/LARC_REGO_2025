/*
 * @file RobotState.cpp
 * @date 02/04/2025
 * @author  Dana E. Torres Estrada
 *
 * @brief Defines the RobotState enumeration representing different states of the robot.
 */

#ifndef ROBOTSTATE_H
#define ROBOTSTATE_H

enum class RobotState {
    INIT,
    IDLE,
    CAIBRATE,
    CALC_TRACK,
    FOLLOW_TRACK,
    FETCH_BEAN,
    PICK_BEAN,
    DROP_BEAN,
    FINISH
};

#endif //ROBOTSTATE_H