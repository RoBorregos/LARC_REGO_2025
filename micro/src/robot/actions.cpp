/**
 * @file actions.cpp
 * @brief File for the actions of the robot
 * @author Juan Pablo Gutiérrz
 * @date 2025-05-06
 */
#include "actions.hpp"

bool init(){
    drive_.setState(0);
    gripper_.setState(0);
    elevator_.setState(0);
    lower_sorter_.setState(1);
    upper_sorter_.setState(1);
    return true;
}

bool globalUpdate(){
    drive_.update();
    gripper_.update();
    elevator_.update();
    lower_sorter_.update();
    upper_sorter_.update();
    camera_.update();

    return true;

}

bool centerWithObject(double elapsed_time) //Center in X offset
{
    float offsetX = camera_.getOffset_X();
    //float offsetY = camera_.getOffset_Y();
    if (offsetX > abs(0.1))
    {
        double outputX = centerPID_.update(offsetX, VisionConstants::kCenterOffsetX);
        //double outputY = centerPID_.update(offsetY, VisionConstants::kCenterOffsetY);
        drive_.acceptInput(-outputX, 0, 0);
        return false;
    }
    drive_.acceptInput(0, 0, 0);
    return true;
}

bool alignWithObject(double elapsed_time, float desired_distance=10.0) { //Acomodar robot to a certain distance //! incomplete method
    float distance = camera_.getObjectDistance();
    if (distance > desired_distance) {
        double outputY = centerPID_.update(100, 112); //TODO:
    }
}

/**
 * @brief Recoger la pelota
 */
bool pickBean(double elapsed_time, int level)
{
    static int state = 0;
    static double state_start_time = 0;

    bool beanType = false; // false = MADURO, true = SOBREMADURO

    if (state_start_time == 0) {
        state_start_time = elapsed_time;
    }

    switch (state) {
        case 0: // Set gripper and elevator
            gripper_.setState(1);
            elevator_.setState(level);
            state = 1;
            return false;

        case 1: // Center and pick
            if (centerWithObject(elapsed_time)) {
                state = 2;
                state_start_time = elapsed_time;
            }
            return false;
        
        case 2:
            if(elapsed_time - state_start_time < 750) {
                drive_.acceptInput(0,100,0);
            } else {
                drive_.acceptInput(0, 0, 0);
                gripper_.setState(0);
                state = 3;
                state_start_time = elapsed_time;
            }
            return false;

        case 3:
            if(elapsed_time - state_start_time < 1000) {
                drive_.acceptInput(0,-100,0);
            } else {
                drive_.acceptInput(0, 0, 0);
                state = 4;
                state_start_time = elapsed_time;
            }
            return false;
        
        case 4:
            upper_sorter_.setState(1);
            if(elapsed_time-state_start_time < 1500) {
                elevator_.setState(1);
            } else if (elapsed_time - state_start_time < 2000) {
                gripper_.setState(1);
            } else {
                upper_sorter_.setState(beanType*2);
                return true;
            }
            return false;

        default:
            state = 0;
            state_start_time = 0;
            return false;
    }
}

/**
 * @brief Sortear la pelota
 */
bool sortBean(double elapsed_time, int category)
{
    static int state = 0;
    static double state_start_time = 0;

    if (state_start_time == 0) {
        state_start_time = elapsed_time;
    }

    switch (state) {
        case 0: // Set elevator and sorter
            elevator_.setState(0);
            upper_sorter_.setState(category);
            state = 1;
            return false;

        case 1: // Wait and release
            if (elapsed_time - state_start_time > 1000) {
                gripper_.setState(0);
                state = 0;
                state_start_time = 0;
                return true;
            }
            return false;

        default:
            state = 0;
            state_start_time = 0;
            return false;
    }
}

bool initStart(){
    drive_.acceptHeadingInput(Rotation2D::fromDegrees(0));
    drive_.setState(0);
    gripper_.setState(0);
    elevator_.setState(0);
    lower_sorter_.setState(1);
    upper_sorter_.setState(1);
    return true;
}

/**
 * @brief Avanzar por 2 segundos, definir la posicion de inicio
 */
bool exitStart(double elapsed_time)
{
    static int state = 0;
    static double state_start_time = 0;

    if (state_start_time == 0) {
        state_start_time = elapsed_time;
    }

    switch (state) {
        case 0: // Set heading and move
            drive_.acceptHeadingInput(Rotation2D::fromDegrees(0));
            if (elapsed_time - state_start_time < 2000) {
                drive_.acceptInput(0, 100, 0);
                return false;
            }
            state = 1;
            return false;

        case 1: // Stop
            drive_.acceptInput(0, 0, 0);
            state = 0;
            state_start_time = 0;
            return true;

        default:
            state = 0;
            state_start_time = 0;
            return false;
    }
}

bool goTreeZone(double elapsed_time) { //! incomplete function, obstacle detection is missing
    drive_.acceptHeadingInput(Rotation2D::fromDegrees(0));
    drive_.setState(0);

    static int state = 0;
    static double state_start_time = 0;

    if (state_start_time == 0) {
        state_start_time = elapsed_time;
    }

    switch (state) {
        case 0: // Advance
            if (elapsed_time - state_start_time < 5000) {
                drive_.acceptInput(0, 100, 0);
                return false;
            }
        case 1: // Stop
            drive_.acceptInput(0, 0, 0);
            return true;
        default:
            state = 0;
            state_start_time = 0;
            return false;
    }
}

bool goLeftLimit(double elapsed_time){
    drive_.acceptHeadingInput(Rotation2D::fromDegrees(0));
    drive_.setState(0);

    static int state = 0;
    static double state_start_time = 0;

    if (state_start_time == 0) {
        state_start_time = elapsed_time;
    }

    switch (state) {
        case 0: // Search
            if (!line_sensor_.leftDetected()) {
                drive_.acceptInput(-100, 0, 0);
                return false;
            }
            state = 1;
            return false;

        case 1: // Stop
            drive_.acceptInput(0, 0, 0);
            state = 0;
            state_start_time = 0;
            return true;

        default:
            state = 0;
            state_start_time = 0;
            return false;
    }
}

bool goRightLimit(double elapsed_time){
    drive_.acceptHeadingInput(Rotation2D::fromDegrees(0));
    drive_.setState(0);

    static int state = 0;
    static double state_start_time = 0;

    if (state_start_time == 0) {
        state_start_time = elapsed_time;
    }

    switch (state) {
        case 0: // Search
            if (!line_sensor_.rightDetected()) {
                drive_.acceptInput(100, 0, 0);
                return false;
            }
            state = 1;
            return false;

        case 1: // Stop
            drive_.acceptInput(0, 0, 0);
            state = 0;
            state_start_time = 0;
            return true;

        default:
            state = 0;
            state_start_time = 0;
            return false;
    }
}
/**
 * @brief Buscar arboles
 */
bool searchForTrees(double elapsed_time, bool direction)
{
    static int state = 0;
    static double state_start_time = 0;

    if (state_start_time == 0) {
        state_start_time = elapsed_time;
    }

    camera_.setState(1); // FETCH_TREES

    switch (state) {
        case 0: // Search
            if (elapsed_time - state_start_time < 2000 && !camera_.objectPresent()) {
                drive_.acceptInput(direction ? 100 : -100, 0, 0);
                return false;
            }
            state = 1;
            return false;

        case 1: // Stop
            drive_.acceptInput(0, 0, 0);
            state = 0;
            state_start_time = 0;
            return true;

        default:
            state = 0;
            state_start_time = 0;
            return false;
    }
}

bool avoidLeftObstacle() //TODO:
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

bool avoidRightObstacle() //TODO:
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

bool goStorageZone(double elapsed_time) {
    drive_.acceptHeadingInput(Rotation2D::fromDegrees(180));
    drive_.setState(0);

    static int state = 0;
    static double state_start_time = 0;

    if (state_start_time == 0) {
        state_start_time = elapsed_time;
    }

    switch (state) {
        case 0: // Advance
            if (elapsed_time - state_start_time < 5000) {
                drive_.acceptInput(0, 100, 0);
                return false;
            }
        case 1: // Stop
            drive_.acceptInput(0, 0, 0);
            return true;
        default:
            state = 0;
            state_start_time = 0;
            return false;
    }
}

void goStorageMaduro()
{
    static int state = 0;
    static double state_start_time = 0;

    if (state_start_time == 0) {
        state_start_time = elapsed_time;
    }

    camera_.setState(2); // FETCH_STOREHOUSE_MADURO


    drive_.setState(0);
    drive_.acceptHeadingInput(Rotation2D::fromDegrees(180));

    camera_.setState();
}

void goStoreGrown()
{
    // Implementation needed
}

void goStorageOvergrown()
{
    // Implementation needed
}

bool dropBeans(double elapsed_time, int container_type)
{
    static int state = 0;
    static double state_start_time = 0;

    if (state_start_time == 0) {
        state_start_time = elapsed_time;
    }

    switch (state) {
        case 0: // Center with storage
            if (centerWithObject(elapsed_time)) {
                state = 1;
                state_start_time = elapsed_time;
            }
            return false;

        case 1: // Turn 180 degrees
            drive_.setState(0);
            drive_.acceptHeadingInput(Rotation2D::fromDegrees(180));
            if (elapsed_time - state_start_time > 1000) {
                state = 2;
                state_start_time = elapsed_time;
            }
            return false;

        case 2: // Move backwards
            if (elapsed_time - state_start_time < 2000) {
                drive_.acceptInput(0, -100, 0);
            } else {
                state = 3;
                state_start_time = elapsed_time;
            }
            return false;

        case 3: // Drop beans
            drive_.acceptInput(0, 0, 0);
            lower_sorter_.setState(container_type);
            if (elapsed_time - state_start_time > 1000) {
                state = 4;
                state_start_time = elapsed_time;
            }
            return false;

        case 4: // Move forward and turn back
            drive_.setState(0);
            drive_.acceptInput(0, 100, 0);
            drive_.acceptHeadingInput(Rotation2D::fromDegrees(0));
            if (elapsed_time - state_start_time > 2000) {
                state = 0;
                state_start_time = 0;
                return true;
            }
            return false;

        default:
            state = 0;
            state_start_time = 0;
            return false;
    }
}