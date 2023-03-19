# BrushlessMotor
Creates a brushless motor controller which can individually control two different motors using PWM.

Library created by Zee for use in the ISEF project "A Novel Application of Filtration for the Collection of Microplastics in Waterways"

Defines a BrushlessMotor object which can be used to control two PWM motors using open-loop control. 

Adds 4 methods, .attach, .write, .setOutputPower, and .setCycles

.attach(int pin1, int pin2);
  - attaches motors with two separate pins to the BrushlessMotor object
  
.write(int speed1, int speed2);
  - takes in two PWM values and writes them to the motors previously attached to the BrushlessMotor object
  
.setOutputPower(int p);
  - sets the output power of the motors
  
.setCycles(int n);
  - sets the number of duty cycles for the two motors. This value is multiplied by the PWM values provided in .write() for control of the motors
