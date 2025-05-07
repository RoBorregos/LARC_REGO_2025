/*
 * @file CameraUpper.cpp
 * @date 01/05/2025
 * @author Dana E. Torres Estrada
 *
 * @brief Implementation file for receiving Upper Camera data from serial
 */

#include "CameraUpper.hpp"

//* Constructor
CameraUpper::CameraUpper() {
}

void CameraUpper::update() {
    if (Serial.available()) {
        String received = Serial.readStringUntil('\n');
        received.trim();

        if (!received.startsWith("Type:")) { // Ignore if received message doesn't start with "Type:"
            return;
        }
    
        int typeIndex = received.indexOf("Type:");
        int offsetXIndex = received.indexOf("OffsetX:");
        int offsetYIndex = received.indexOf("OffsetY:");
    
        // Process type
        BeanConstants::BeanType newType = BeanConstants::NONE;
        if (typeIndex != -1) {
            int commaIndex = received.indexOf(",", typeIndex);
            String typeStr = (commaIndex != -1) ?
                             received.substring(typeIndex + 5, commaIndex) :
                             received.substring(typeIndex + 5);
            typeStr.trim();
    
            if (typeStr == "MADURO") newType = BeanConstants::MADURO;
            else if (typeStr == "SOBREMADURO") newType = BeanConstants::SOBREMADURO;
        }
    
        current_bean_type_ = newType;
    
        // If type=NONE, offsets are 0.0
        if (current_bean_type_ == BeanConstants::NONE) {
            current_offset_x_ = 0.0;
            current_offset_y_ = 0.0;
            return;
        }
    
        // Process OffsetX
        if (offsetXIndex != -1) {
            int commaIndex = received.indexOf(",", offsetXIndex);
            String value = (commaIndex != -1) ?
                           received.substring(offsetXIndex + 8, commaIndex) :
                           received.substring(offsetXIndex + 8);
            value.trim();
            current_offset_x_ = value.toFloat();
        }
    
        // Process OffsetY
        if (offsetYIndex != -1) {
            int commaIndex = received.indexOf(",", offsetYIndex);
            String value = (commaIndex != -1) ?
                           received.substring(offsetYIndex + 8, commaIndex) :
                           received.substring(offsetYIndex + 8);
            value.trim();
            current_offset_y_ = value.toFloat();
        }
    }
}

BeanConstants::BeanType CameraUpper::beanPresent() {
    return current_bean_type_;
}

float CameraUpper::getBeanOffset_X() {
    return current_offset_x_;
}

float CameraUpper::getBeanOffset_Y() {
    return current_offset_y_;
}