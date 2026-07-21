#ifndef PID_HHH
#define PID_HHH

#include <stdlib.h>
#include <AccelStepper.h>


const int STEP_PIN = 3;
const int DIR_PIN  = 2;
long MAX_POS = 1750;
long MIN_POS = 0;

const double MAX_SPEED = 150.0;  // steps/second

// PID tuning values
double kp = 5.0;
double ki = 0.0;
double kd = 0.0;

double targetHeightInches = 8.0;

// Persistent PID state
double previousError = 0.0;
double integral = 0.0;

// Persistent motor command
double commandedSpeed = 0.0;

AccelStepper stepper(AccelStepper::DRIVER, STEP_PIN, DIR_PIN);


double applySpeedLimit(double requestedspeed);
double PID(double kp, double ki, double kd, double setpoint, double input, double*prev_err, double*integral, double dt);
void PID_setup();

#endif