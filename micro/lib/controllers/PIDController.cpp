#include "PIDController.hpp"

PIDController::PIDController(float kp, float ki, float kd, float outputMin, float outputMax)
    : lastMeasurement_(0.0), lastSetpoint_(0.0), output_(0.0), enabled_(true) {
    // Initialize the PID controller with pointers to our variables
    pid_ = new PID(&lastMeasurement_, &output_, &lastSetpoint_, (double)kp, (double)ki, (double)kd, DIRECT);
     
    // Set the mode and output limits
    pid_->SetMode(AUTOMATIC);
    pid_->SetOutputLimits((double)outputMin, (double)outputMax);
}

PIDController::~PIDController() {
    // Clean up the PID controller
    delete pid_;
}

float PIDController::update(float measurement, float setpoint) {
    if (!enabled_) {
        Serial.println("PID Controller is disabled");
        return 0.0f;
    }
    
    // Store the current values
    lastMeasurement_ = (double)measurement;
    lastSetpoint_ = (double)setpoint;
    
    // Compute the PID output
    pid_->Compute();
    
    return (float)output_;
}

void PIDController::reset() {
    // Reset our variables
    lastMeasurement_ = 0.0;
    lastSetpoint_ = 0.0;
    output_ = 0.0;
    
    // Reinitialize the PID controller
    pid_->SetMode(MANUAL);
    pid_->SetMode(AUTOMATIC);
}

void PIDController::setGains(float kp, float ki, float kd) {
    pid_->SetTunings((double)kp, (double)ki, (double)kd);
}

void PIDController::setOutputLimits(float min, float max) {
    pid_->SetOutputLimits((double)min, (double)max);
}

void PIDController::setEnabled(bool enabled) {
    enabled_ = enabled;
    Serial.println("PID Controller " + String(enabled ? "enabled" : "disabled"));
    if (!enabled) {
        reset();
    }
}

bool PIDController::isEnabled() const {
    return enabled_;
}

float PIDController::getError() const {
    return (float)(lastSetpoint_ - lastMeasurement_);
}

float PIDController::getOutput() const {
    return (float)output_;
} 