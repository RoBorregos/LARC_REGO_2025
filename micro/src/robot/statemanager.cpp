/*
 * @file statemanager.cpp
 * @date 01/04/2025
 * @author Juan Pablo Gutiérrez & Dana E. Torres Estrada
 *
 * @brief Implementation file for the StateManager class, which manages the robot's state and subsystems.
*/

#include "statemanager.hpp"

StateManager::StateManager() :
    elevator_(),
    gripper_(),
    drive_(),
    lower_sorter_(),
    upper_sorter_()
{}

void StateManager::setState(RobotState state) {
    state_ = state;
    state_start_time_ = 0; // reiniciar contador de tiempo del estado individual
}

RobotState StateManager::getState() {
    return state_;
}

unsigned long StateManager::getTimeSpent() {
    return millis() - start_time_;
}

void StateManager::centerWithObject() { // !!! TODO Añadir que centrarse debe quedar a x cm
    /* cam_low_->receiveData();
    float offsetX = cam_low_->getOffset_X();

    while (offsetX < -0.1f || offsetX > 0.1f) {
        if (offsetX < -0.1f) {
            drive_->moveLeft(100);
        } else if (offsetX > 0.1f) {
            drive_->moveRight(100);
        }

        delay(100); // pausa pequeña para dar tiempo al movimiento
        cam_low_->receiveData();
        offsetX = cam_low_->getOffset_X(); // Recalcula offset
    }

    drive_->moveForward(0); // Ya está centrado */
}

/*void StateManager::pickBean() {
    bool allBeansPicked = false;
            
    cam_up_->receiveData();
    int beanType = cam_up_->beanPresent();
    //cam_up_
    centerWithBean();
    state_start_time_

    acceptInput(0,100,0);

    allBeansPicked = (cam_up_->beanPresent() == 0);
}*/

void StateManager::stateAction() {
    switch (state_) {
        case RobotState::INIT: {
            /* 
            * Inicializar micros
            * Iniciar tiempo de partida
            */
            elevator_.setState(0);
            gripper_.setState(0);
            drive_.setState(0);
            drive_.update();
            start_time_ = millis();    
            break;
        }
        case RobotState::EXIT_START: {
            /* 
            * Avanzar por 2 segundos
            */
            drive_.acceptHeadingInput(Rotation2D::fromDegrees(0));
            unsigned long timeTraveled = millis();
            while (millis()-timeTraveled < 2000){
                drive_.acceptInput(0,100,0);
            }
            drive_.acceptInput(0,0,0);
            //start_pos_ = ; //?idk se puede?
            break;
        }
        case RobotState::GO_TREES: {
            /* 
            * La camara low comienza a detectar albercas
            * Robot avanza
            */
            /* cam_low_->receiveData();
            if (state_start_time_ == 0)
                state_start_time_ = millis();

            cam_low_->setState(0); // AVOID_OBSTACLES
            drive_->acceptInput(0,100,0); */
            break;
        }
        case RobotState::AVOID_LEFT_OBSTACLE: {//!checar, algo se ve muy sus
            /* 
            * si hay una alberca presente moverse a la izquierda para evitar obstaculo
            * sino, avanzar hacia adelante
            */
            /* cam_low_->receiveData();

            if (cam_low_->objectPresent()) {
                drive_->moveLeft(100);
            } else {
                if (state_start_time_ == 0)
                    state_start_time_ = millis();

                drive_->acceptInput(0,100,0);
            } */
            break;
        }
        case RobotState::AVOID_RIGHT_OBSTACLE: { //!checar, algo se ve muy sus
            /* 
            * si hay una alberca presente moverse a la derecha para evitar obstaculo
            * sino, avanzar hacia adelante
            */
            /* cam_low_->receiveData();

            if (cam_low_->objectPresent()) {
                    drive_->moveRight(100);
            } else {
                if (state_start_time_ == 0)
                    state_start_time_ = millis();

                drive_->acceptInput(0,100,0);
            } */
            break;
        }
        case RobotState::GO_LEFT_LINE: {
            /*
            * Buscar arboles
            * moverse a la izquierda
            */
            /* cam_low_->setState(1); // FETCH_TREES
            drive_->moveLeft(100);
            current_tree_ = 1; */
            break;
        }
        case RobotState::GO_RIGHT_LINE: {
            /*
            * Buscar arboles
            * moverse a la derecha
            */
            /* cam_low_->setState(1); // FETCH_TREES
            drive_->moveRight(100);
            current_tree_ = 3; */
            break;
        }
        case RobotState::PICK_MID_LEVEL: {
            /*
            * setear elevador a nivel mid
            * centrarse en el arbol
            * buscar pelota
            */
            elevator_.setState(2);
            
            centerWithObject();
            for (current_beans_=0; current_beans_<mid_level_beans_; ++current_beans_) {
                //pickBean();
            }
            break;
        }
        case RobotState::PICK_LOW_LEVEL: {
            /*
            * setear elevador a nivel mid
            * centrarse en el arbol
            * buscar pelota
            */
            elevator_.setState(1); //! si hay error, primero reiniciar en el cambio de estado

            centerWithObject();

            for (current_beans_=0; current_beans_<low_level_beans_; ++current_beans_) {
                //pickBean();
            }
            break;
        }
        case RobotState::GO_STORAGE_MADURO: {//TODO
            /*
            *
            */
            /* cam_low_->receiveData();
            
            drive_->setState(0); // HEADING_LOCK
            drive_->acceptHeadingInput(Rotation2D::fromDegrees(180)); */

            break;
        }
        case RobotState::GO_STORAGE_SOBREMADURO: {//TODO
            break;
        }
        case RobotState::DROP_BEANS: {
            /*
            * centrarse con el almacen
            * girar 180°
            * moverse hacia atras por 2 segs
            * soltar pelotas
            * moverse hacia adelante y girar 180 para prepararse a la siguiente caja
            */
            /* cam_low_->receiveData();
            centerWithObject(); // centar con el almacen

            drive_->setState(0); // HEADING_LOCK
            drive_->acceptHeadingInput(Rotation2D::fromDegrees(180));
            
            state_start_time_ = millis();
            while (millis()-state_start_time_ < 2000) {
                drive_->moveBackward(100);
            }
            drive_->moveForward(0);

            //almacen_->dropBalls(droped_SOBREMADURO) //Rego //0-MADURO, 1-SOBREMADURO
            //revolver_->dropBalls() //Robo
            delay(2000); //para asegurarse que toas las pelotas se hayan soltado

            while (millis()-state_start_time_ < 2000) {
                drive_->acceptInput(0,100,0);
            }
            drive_->moveForward(0);
            drive_->setState(0); // HEADING_LOCK
            drive_->acceptHeadingInput(Rotation2D::fromDegrees(180)); */
            break;
        }
        default:
            break;
    }
}

void StateManager::update() { //!checar
    elevator_.update();
    drive_.update();
    gripper_.update();
    lower_sorter_.update();
    upper_sorter_.update();
    //almacen_->update();
    //revolver->update();
    //line_sensor_->update();
    stateAction();
}

