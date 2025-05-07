#include "CameraLower.hpp"

CameraLower::CameraLower() {}

void CameraLower::update() {
    if (!Serial.available()) return;

    String received = Serial.readStringUntil('\n');
    received.trim();

    // Auxiliar function to reset values to 0
    auto resetValues = [&]() {
        object_present_ = false;
        object_too_close_ = false;
        current_distance_ = 0.0f;
        current_offset_x_ = 0.0f;
        current_offset_y_ = 0.0f;
        bean_storage_type = false;
    };

    switch (camera_state_) {
    case static_cast<CameraLowerState>(0): { // OBSTACLE
        if (!received.startsWith("OBSTACLE:")) return;

        if (received == "OBSTACLE: False") {
            resetValues();
            return;
        }

        object_present_ = true;

        int idx = received.indexOf("DISTANCE:");
        if (idx != -1)
            current_distance_ = received.substring(idx + 9, received.indexOf(',', idx)).toFloat();

        idx = received.indexOf("TOO_CLOSE:");
        if (idx != -1)
            object_too_close_ = received.substring(idx + 10, received.indexOf(',', idx)).trim() == "True";

        idx = received.indexOf("OFFSET_X:");
        if (idx != -1)
            current_offset_x_ = received.substring(idx + 9, received.indexOf(',', idx)).toFloat();

        idx = received.indexOf("OFFSET_Y:");
        if (idx != -1)
            current_offset_y_ = received.substring(idx + 9).toFloat();

        break;
    }
    case static_cast<CameraLowerState>(1): { // TREE
        if (!received.startsWith("TREE:")) return;

        if (received == "TREE: False") {
            resetValues();
            return;
        }

        object_present_ = true;

        int idx = received.indexOf("DISTANCE:");
        if (idx != -1)
            current_distance_ = received.substring(idx + 9, received.indexOf(',', idx)).toFloat();

        idx = received.indexOf("TOO_CLOSE:");
        if (idx != -1)
            object_too_close_ = received.substring(idx + 10, received.indexOf(',', idx)).trim() == "True";

        idx = received.indexOf("OFFSET_X:");
        if (idx != -1)
            current_offset_x_ = received.substring(idx + 9, received.indexOf(',', idx)).toFloat();

        idx = received.indexOf("OFFSET_Y:");
        if (idx != -1)
            current_offset_y_ = received.substring(idx + 9).toFloat();

        break;
    }
    case static_cast<CameraLowerState>(2):
    case static_cast<CameraLowerState>(3): { // STORAGE
        if (!received.startsWith("STORAGE:")) return;

        if (received == "STORAGE: False") {
            resetValues();
            return;
        }

        object_present_ = true;

        int idx = received.indexOf("TYPE:");
        if (idx != -1) {
            String type = received.substring(idx + 5, received.indexOf(',', idx)).trim();
            bean_storage_type = (type == "SOBREMADURO");
        }

        idx = received.indexOf("DISTANCE:");
        if (idx != -1)
            current_distance_ = received.substring(idx + 9, received.indexOf(',', idx)).toFloat();

        idx = received.indexOf("TOO_CLOSE:");
        if (idx != -1)
            object_too_close_ = received.substring(idx + 10, received.indexOf(',', idx)).trim() == "True";

        idx = received.indexOf("OFFSET_X:");
        if (idx != -1)
            current_offset_x_ = received.substring(idx + 9, received.indexOf(',', idx)).toFloat();

        idx = received.indexOf("OFFSET_Y:");
        if (idx != -1)
            current_offset_y_ = received.substring(idx + 9).toFloat();

        break;
    }
    default:
        break;
    }
}

void CameraLower::setState(int state) {
    camera_state_ = static_cast<CameraLowerState>(state);
    Serial.print("CameraLower state: ");
    Serial.println(state);
}

float CameraLower::getOffset_X() {
    return current_offset_x_;
}

float CameraLower::getOffset_Y() {
    return current_offset_y_;
}

float CameraLower::getObjectDistance() {
    return current_distance_;
}

bool CameraLower::objectPresent() {
    return object_present_ = false;
}

bool CameraLower::isObjectTooClose() {
    return object_too_close_ || current_distance_ <= 10.0;
}