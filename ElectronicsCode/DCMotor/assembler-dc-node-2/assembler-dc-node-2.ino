#include "low_pass_filter.h"
#include "MicroGearMotor.h"
#include <PinChangeInt.h>

/*
IMPORTANT

some motors seem to have the direction pin wired backwards - they will not stop
G4 P0.05 between M3/M4/M5 commands

*/

//routines
byte CURRENT_ROUTINE = 0;
int homeQueue[][2] = {{10000, 10}};//000
int getStockQueue[][2] ={{-4000, 10}, {-5807, 6}, {-5000, 6}, {-200, 10}};//001
int placeLowerQueue[][2] ={{-11500, 10}, {-13225, 6}, {-11500, 6}, {-200, 10}};//010
int placeUpperQueue[][2] ={{-11500, 10}, {-13225, 6}, {-11500, 6}, {-200, 10}};//011

byte queuePosition = 0;
boolean shouldGo = false;
boolean waitingForFinish = false;
int zStopCountDown = 0;
byte zStopPin = 15;

boolean doBackOff = false;


#define encA1_int 3
#define encB1_int 2
#define encA2_int 0
#define encB2_int 1

MicroGearMotor *motor1 = new MicroGearMotor(4, 9, A0, 1, 0, true);//byte dirPin, byte pwmPin, byte currentPin, byte encoderAPin, byte encoderBPin, boolean invertDirection
MicroGearMotor *motor2 = new MicroGearMotor(5, 10, A1, 3, 2, false);

void setup() {
  
  Serial.begin(9600);
  
  pinMode(zStopPin, OUTPUT);
  
  initTinyGComm();
  
  motor1->init();
  motor2->init();
  motor1->setCurrentPIDGains(20.8, 2.3);//proportional, integral
  motor2->setCurrentPIDGains(20.8, 2.3);
  motor1->setSpeedPIDGains(10, 0.15);
  motor2->setSpeedPIDGains(10, 0.15);
  
  attachInterrupt(encA1_int, encA1trig, CHANGE);
  attachInterrupt(encA2_int, encA2trig, CHANGE);
  
}

void loop() {
  
  checkTinyG();
  
  manageMoveQueue();
  
  float positionDiff = motor2->getPosition()-motor1->getPosition();
//  Serial.print(motor1->getPosition());
//  Serial.print("  ");
//  Serial.println(motor2->getPosition());
  motor1->update(positionDiff);
  motor2->update(-positionDiff);
  
  if (!doBackOff && (motor1->currentLimitHit() || motor2->currentLimitHit())){
    doBackOff = true;//only do this once per item in queue
    if (motor1->getTargetPosition()-motor1->getPosition() > 0){
      motor1->moveTo(motor1->getPosition() - 200, motor1->getTargetSpeed());
      motor2->moveTo(motor1->getPosition() - 200, motor2->getTargetSpeed());
    } else {
      motor1->moveTo(motor1->getPosition() + 200, motor1->getTargetSpeed());
      motor2->moveTo(motor1->getPosition() + 200, motor2->getTargetSpeed());
    }
  }
  
}

void manageMoveQueue(){
  
  if (shouldGo && motor1->targetReached() && motor2->targetReached()) {
    doBackOff = false;
    int nextPosition = getNextPosition(CURRENT_ROUTINE, queuePosition);
    int nextSpeed = getNextSpeed(CURRENT_ROUTINE, queuePosition);
    motor1->moveTo(nextPosition, nextSpeed);
    motor2->moveTo(nextPosition, nextSpeed);
    if (++queuePosition >= getQueueLength(CURRENT_ROUTINE)) {
      shouldGo = false;
      queuePosition = 0;
      waitingForFinish = true;
    }
  }  
  if (waitingForFinish && motor1->targetReached() && motor2->targetReached()){
    waitingForFinish = false;
    zStopCountDown = 1000;
  }
  if (zStopCountDown>0){
    zStopCountDown--;
    digitalWrite(zStopPin, HIGH);
  } else {
    digitalWrite(zStopPin, LOW);
  }
}

void handleTinyGMessage(byte message){
  if (queuePosition != 0) {
    Serial.println("previous routine not finished");
    return;
  }
    switch (message){
      case B000://home
      shouldGo = true;
      break;
      case B001://get stock
      shouldGo = true;
      break;
      case B010://get lower
      shouldGo = true;
      break;
      case B011://get upper
      shouldGo = true;
      break;
    }
    CURRENT_ROUTINE = message;
}

int getNextPosition(byte routine, byte pos){
  switch (routine){
      case B000://home
      return homeQueue[pos][0];
      case B001://get stock
      return getStockQueue[pos][0];
      case B010://get lower
      return placeLowerQueue[pos][0];
      case B011://get upper
      return placeUpperQueue[pos][0];
    }
}

int getNextSpeed(byte routine, byte pos){
  switch (routine){
      case B000://home
      return homeQueue[pos][1];
      case B001://get stock
      return getStockQueue[pos][1];
      case B010://get lower
      return placeLowerQueue[pos][1];
      case B011://get upper
      return placeUpperQueue[pos][1];
    }
}

int getQueueLength(byte routine){
  switch (routine){
      case B000://home
      return sizeof(homeQueue)/sizeof(int)/2;
      case B001://get stock
      return sizeof(getStockQueue)/sizeof(int)/2;
      case B010://get lower
      return sizeof(placeLowerQueue)/sizeof(int)/2;
      case B011://get upper
      return sizeof(placeUpperQueue)/sizeof(int)/2;
    }
}

void encA1trig() {
  motor1->interruptRoutine();
}

void encA2trig() {
  motor2->interruptRoutine();
}
