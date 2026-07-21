#include "PID.h"

//apply software limits
double applySpeedLimit(double requestedspeed){
  long position = stepper.currentPosition();
  return ((requestedspeed>0.0 && position >= MAX_POS)||(requestedspeed<0.0 && position <= MIN_POS)) ? 0.0 : requestedspeed;
}


// Position PID:
// Input: measured height
// Setpoint: desired height
// Output: desired motor speed (-100% to +100%)
double PID(double kp, double ki, double kd, double setpoint, double input, double*prev_err, double*integral, double dt){//do pid on speed instead of distance. so do it on stepper speed
  //maybe add deadband near setpoint
  double err = setpoint-input;//setpoint and input are in inches

  *integral += err * dt;

  const double I_MAX = 50.0;//anti windup
  if (*integral > I_MAX) *integral = I_MAX;
  if (*integral < -I_MAX) *integral = -I_MAX;
    
  double deriv = 0.0;
  if (dt > 0.0) deriv = (err - *prev_err) / dt;

  double output = kp*err + ki*(*integral) + kd*deriv;

  *prev_err = err;

  return (output < -100.0) ? -100.0 : ((output > 100.0) ? 100.0 : output);
}

void PID_setup() {
  stepper.setMaxSpeed(MAX_SPEED);
  stepper.setMinPulseWidth(3);
  // Only valid after homing or manually establishing position.
  stepper.setCurrentPosition(0);
}