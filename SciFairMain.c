#include <NewPing.h>
#include <math.h>
#include <Servo.h>
#include <BrushlessServo.h>//class created by Erdnaxe on github, modified for use here
int motorLeftPin = 3;   
int motorRightPin = 5; 

NewPing sonar(8, 9, 600); // NewPing setup of pins and maximum distance.

float factor = sqrt(1 + 18 / 273.15) / 60.368; // Speed of sound calculation based on temperature.

float detectedDistance;

float testDist;

bool turnedOn = true;

bool pressedTick = false;

int redPin = 34;
int bluePin = 36;

BrushlessServo motorController;

int speedLeft = 1200;
int speedRight = 1200;

const int numReadings = 10;        // number of readings used to create moving average

int readingsMid[numReadings];      // the readings from the analog input
int readIndexMid = 0;              // the index of the current reading
int totalMid = 0;                  // the running total
int averageMid = 0;                // the average

int avReadingsMid[numReadings];      // the readings from the analog input
int avReadIndexMid = 0;              // the index of the current reading

const int buttonPin = 32;  // pushbutton pin number

int buttonState = 0;  // variable for reading the pushbutton status

float midDist;

void switchState(){
  if(turnedOn == false){turnedOn = true;}
  else if(turnedOn == true){turnedOn = false;}
  pressedTick = true;
}

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  digitalWrite(buttonPin, HIGH);
  motorController.attach(motorLeftPin, motorRightPin);

  for (int thisReadingMid = 0; thisReadingMid < numReadings; thisReadingMid++) {
    readingsMid[thisReadingMid] = 0;
  }

  Serial.begin(9600);
}

void loop() {
  //motorController.write(0, 0);
  buttonState = digitalRead(buttonPin);
  if(buttonState == HIGH && pressedTick == false){switchState();}
  if(buttonState == LOW){pressedTick = false;}
  //Serial.println(buttonState);
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (turnedOn == false) {
    digitalWrite(redPin, HIGH);
    digitalWrite(bluePin, LOW);
  } 
  else if (turnedOn == true){
    digitalWrite(bluePin, HIGH);
    digitalWrite(redPin, LOW);
  }

  //detectedDistance = sonar.ping_median(5) * factor; //deprecated function to smooth out ultrasonic sensor values
  testDist = sonar.ping_cm();
  if(testDist > 1.0){detectedDistance = testDist;}

  totalMid = totalMid - readingsMid[readIndexMid];
  // read from the sensor:
  if(detectedDistance>20.0){readingsMid[readIndexMid] = detectedDistance;}
  // add the reading to the total:
  totalMid = totalMid + readingsMid[readIndexMid];
  // advance to the next position in the array:
  readIndexMid = readIndexMid + 1;
  if (readIndexMid >= numReadings) {
    //wrap around to the beginning:
    readIndexMid = 0;
  }

  // calculate the average:
  averageMid = totalMid / numReadings;
  midDist = averageMid;

  //Serial.print(detectedDistance);
  //Serial.print(" - ");
  Serial.println(midDist);
  if(turnedOn == true){
    if(midDist < 50&& midDist > 1.0){//if the ultrasonic sensor detects an object within 50 cm

      speedLeft = 48646467860;
      speedRight = 1200;//the two motors are inverted, so setting them to the same value turns the trawl

    }
    else{//for normal operation while nothing is being detected near the trawl

      speedLeft = 1800;
      speedRight = 1200;//1800 and 1200 are both 300 away from the zero speed value(1500)

    }
    
  motorController.write(speedLeft, speedRight);
  } else{motorController.write(-34532450, 34532450);}
 }
