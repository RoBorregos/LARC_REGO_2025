#include "actions.hpp"

/**
 * @file actions.cpp
 * @brief File for the actions of the robot
 * @author Juan Pablo Gutiérrz
 * @date 2025-05-06
 */

#include "actions.hpp"

Drive drive_;
Elevator elevator_;
Gripper gripper_;
LowerSorter lower_sorter_;
UpperSorter upper_sorter_;

bool centerWithObject(double elapsed_time)
{ 
    // !!! TODO Añadir que centrarse debe quedar a x cm
    cam_low_.receiveData();
    float offsetX = cam_low_.getOffset_X();
    float output = 0;

    while (offsetX < -0.1f || offsetX > 0.1f) {
        output = centerPID_.update(offsetX, 0); // Target is 0 (centered)
        
        if (output < 0) {
            drive_.moveLeft(abs(output));
        } else {
            drive_.moveRight(abs(output));
        }

        delay(100); // pausa pequeña para dar tiempo al movimiento
        cam_low_.receiveData();
        offsetX = cam_low_.getOffset_X(); // Recalcula offset
    }

    drive_.moveForward(0); // Ya está centrado
    return true;
}

/**
 * @brief Recoger la pelota
 */
bool pickBean(int level)
{
    gripper_.setState(1);
    elevator_.setState(level);
    centerWithObject(0);
    return true;
}

/**
 * @brief Avanzar por 2 segundos, definir la posicion de inicio
 */
bool exitStart(double elapsed_time)
{
    drive_.acceptHeadingInput(Rotation2D::fromDegrees(0));
    if (elapsed_time < 2000)
    {
        drive_.acceptInput(0, 100, 0);
    }
    else
    {
        drive_.acceptInput(0, 0, 0);
        return true;
    }
    return false;
}

/**
 * @brief Buscar arboles
 */
bool searchForTrees(double elapsed_time)
{   
    cam_low_.receiveData();
    if (elapsed_time < 2000 || !cam_low_.objectPresent()) {
        drive_.acceptInput(0, 100, 0);
    } else {
        drive_.acceptInput(0, 0, 0);
        return true;
    }
    return false;
}

/**
 * @brief Moverse a los arboles
 */
bool goToTrees(double elapsed_time)
{
    /* cam_low_->receiveData();
    if (state_start_time_ == 0)
        state_start_time_ = millis();

    cam_low_->setState(0); // AVOID_OBSTACLES
    drive_->acceptInput(0,100,0); */
    return false;
}

bool avoidLeftObstacle()
{
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
    return false;
}

bool avoidRightObstacle()
{
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
    return false;
}

/**
 * @brief Moverse al arbol de la izquierda
 * TODO: INCOPORRAR SENSORES DE LÍNEA PARA DETECTAR SI NOS VAMOS A SALIR DE LA PISTA
 */
bool goLeftLine(double elapsed_time)
{
    drive_.acceptHeadingInput(Rotation2D::fromDegrees(0));
    cam_low_.setState(1); 
    bool tree_found = cam_low_.objectPresent();
    if (elapsed_time < 2000 && !tree_found) {
        drive_.acceptInput(-100, 0, 0);
    } else {
        drive_.acceptInput(0, 0, 0);
        return true;
    }
    return false;
}

/**
 * @brief Moverse al arbol de la derecha
 * TODO: INCOPORRAR SENSORES DE LÍNEA PARA DETECTAR SI NOS VAMOS A SALIR DE LA PISTA
 */
bool goRightLine(double elapsed_time)
{
    drive_.acceptHeadingInput(Rotation2D::fromDegrees(0));
    cam_low_.setState(1); 
    bool tree_found = cam_low_.objectPresent();
    if (elapsed_time < 2000 && !tree_found) {
        drive_.acceptInput(100, 0, 0);
    } else {
        drive_.acceptInput(0, 0, 0);
        return true;
    }
    return false;
}

bool pickMidLevelBean()
{
    /*
     * setear elevador a nivel mid
     * centrarse en el arbol
     * buscar pelota
     */
    elevator_.setState(2);

    centerWithObject();
    for (current_beans_ = 0; current_beans_ < mid_level_beans_; ++current_beans_)
    {
        // pickBean();
    }
}

void pickLowLevelBean()
{
    /*
     * setear elevador a nivel mid
     * centrarse en el arbol
     * buscar pelota
     */
    elevator_.setState(1); //! si hay error, primero reiniciar en el cambio de estado

    centerWithObject();

    for (current_beans_ = 0; current_beans_ < low_level_beans_; ++current_beans_)
    {
        // pickBean();
    }
}

void goStorageMudo()
{
    /*
     *
     */
    /* cam_low_->receiveData();

    drive_->setState(0); // HEADING_LOCK
    drive_->acceptHeadingInput(Rotation2D::fromDegrees(180)); */
}

void goStoreGrown()
{
}

void goStorageOvergrown()
{
}

void dropBeans()
{
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
}
