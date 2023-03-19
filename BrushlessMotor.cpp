// Brushless motor library

#include "BrushlessMotor.h"

void BrushlessMotor::attach(int p1, int p2)
{
  // Set output pins
  pins[0] = p1;
  pins[1] = p2;

  pinMode(p1, OUTPUT);
  pinMode(p2, OUTPUT);
 

  // Generate sin table for faster control
  sinArray.generate();
}

void BrushlessMotor::write(int speed1, int speed2)
{
  float real_angle1 = n_cycles * speed1;
  float real_angle2 = n_cycles * speed2;


  int pwm1 = (float)power * (sinArray.getSinDegree(real_angle1) + 1.) / 2.;
  int pwm2 = (float)power * (sinArray.getSinDegree(real_angle2 + 120) + 1.) / 2.;


  // Set PWMs
  analogWrite(pins[0], pwm1);
  analogWrite(pins[1], pwm2);

}

void BrushlessMotor::setOutputPower(int p)
{
  power = p;
}

void BrushlessMotor::setCycles(int n)
{
  n_cycles = n;
}
