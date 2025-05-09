#include "PIDController.hpp"
#include <math.h>

PIDController::PIDController() 
    : lastMeasurement_(0.0), lastSetpoint_(0.0), output_(0.0), enabled_(true), angleWrapping_(false) {
    // Initialize the PID controller with default values
    pid_ = new PID(&lastMeasurement_, &output_, &lastSetpoint_, 0.0, 0.0, 0.0, DIRECT);
     
    // Set the mode and output limits
    pid_->SetMode(AUTOMATIC);
    pid_->SetOutputLimits(-1.0, 1.0);
}

PIDController::PIDController(float kp, float ki, float kd, float outputMin, float outputMax)
    : lastMeasurement_(0.0), lastSetpoint_(0.0), output_(0.0), enabled_(true), angleWrapping_(false) {
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
        return 0.0f;
    }
    
    // If angle wrapping is enabled, wrap the measurement and setpoint
    if (angleWrapping_) {
        // Normalize angles to [-180, 180] range
        measurement = fmod(measurement + M_PI, 2 * M_PI);
        if (measurement < 0) measurement += 2 * M_PI;
        measurement -= M_PI;

        setpoint = fmod(setpoint + M_PI, 2 * M_PI);
        if (setpoint < 0) setpoint += 2 * M_PI;
        setpoint -= M_PI;

        // Calculate the error with wrapping
        float error = setpoint - measurement;
        if (error > M_PI) {
            error -= 2 * M_PI;
        } else if (error < -M_PI) {
            error += 2 * M_PI;
        }
        
        // Store the wrapped values
        lastMeasurement_ = (double)measurement;
        lastSetpoint_ = (double)setpoint;
        
        // Compute the PID output
        pid_->Compute();
        
        return (float)output_;
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

void PIDController::setAngleWrapping(bool enabled) {
    angleWrapping_ = enabled;
}

bool PIDController::isAngleWrappingEnabled() const {
    return angleWrapping_;
} 