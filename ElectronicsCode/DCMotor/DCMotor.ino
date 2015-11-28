#include "low_pass_filter.h"
#include "MicroGearMotor.h"
#include <PinChangeInt.h>


#define encA1 2
#define encB1 5

MicroGearMotor *motor1 = new MicroGearMotor(4, 9, A0, encA1, encB1, 6, 298);//byte dirPin, byte pwmPin, byte currentPin, byte encoderAPin, byte encoderBPin, boolean invertDirection

void setup() {
  
  pinMode(13, OUTPUT);  
  
  Serial.begin(9600);
  
  motor1->init();
  motor1->setCurrentPIDGains(20.8, 2.3);//proportional, derivativeGain
  motor1->setSpeedPIDGains(5, 0.05);
  
  attachInterrupt(digitalPinToInterrupt(encA1), encA1trig, CHANGE);
  
  boolean successfulCalibration = motor1->calibrate();
  if (!successfulCalibration) {
    Serial.println("bad calibration");
    while(1){};
  }
}

void loop() {
  
  if (Serial.available()) {
    float input = Serial.parseFloat();
    motor1->moveTo(input, 50);
  }
  
  motor1->update();
//  Serial.println(motor1->getTicks());
 
  
}

void encA1trig() {
  motor1->interruptRoutine();
}
