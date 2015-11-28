#include "low_pass_filter.h"
#include <PinChangeInt.h>
//#include <PinChangeIntConfig.h>

#define encA1 2
#define encB1 3
#define encA1_int 2
#define encB1_int 3

LPFilter lpfilter1;

volatile long motor_pos1 = 0;

uint8_t led_pin = 13;
uint8_t dir1 = 4;
uint8_t pwm1 = 9;
uint8_t c_sense1 = A0;

uint16_t setCurrent1 = uint16_t(0.8/0.009775);
float thisCurrent1 = 0;
uint16_t motor_pwr1 = 0;
int error1 = 0;
float kp1 = 20.8;
float ki1= 2.3;
uint8_t max_pwm = 100;

uint16_t t_start = 0;

boolean off = true;

void setup() {
  Serial.begin(9600);
  Serial.println("started...");
  
  pinMode(led_pin, OUTPUT); 
  pinMode(dir1, OUTPUT);
  pinMode(pwm1, OUTPUT);
  
  pinMode(encA1, INPUT);
  pinMode(encB1, INPUT);
  pinMode(c_sense1, INPUT);
  
  attachInterrupt(encA1_int, encA1trig, CHANGE);
  
  lpfilter1.init(2.5, measureCurrentInt1());
}

void loop() {
//  //DEBUG
//  analogWrite(pwm1, 50);
//  digitalWrite(dir1, LOW);
//  analogWrite(pwm2, 50);
//  digitalWrite(dir2, LOW);
//  
//  Serial.print("M1: ");
//  Serial.print(motor_pos1);
//  Serial.print(", ");
//  Serial.print(thisCurrent1);
//  Serial.print("   M2: ");
//  Serial.print(motor_pos2);
//  Serial.print(", ");
//  Serial.print(thisCurrent2);
//  Serial.println();
  
  
  if (Serial.available()) {
    char input = Serial.read();
    if (input == 'u') {
      digitalWrite(led_pin, LOW);
      digitalWrite(dir1, HIGH);
      digitalWrite(pwm1, HIGH);
      Serial.println("up");
      error1 = 0;
      t_start = millis();
    } else if (input == 'd') {
      digitalWrite(led_pin, HIGH);
      digitalWrite(dir1, LOW);
      digitalWrite(pwm1, HIGH);
      Serial.println("down");
      t_start = millis();
      error1 = 0;
    } else {
    }
  }

////  //Check activate pin
//  
//  thisCurrent1 = lpfilter1.step(measureCurrentInt1());
//  error1 += setCurrent1-thisCurrent1;
//  error1 = constrain(error1,-100,100);
//  motor_pwr1 = constrain(kp1*(setCurrent1-thisCurrent1)+ki1*error1,0,max_pwm);
//  
//  thisCurrent2 = lpfilter2.step(measureCurrentInt2());
//  error2 += setCurrent2-thisCurrent2;
//  error2 = constrain(error2,-100,100);
//  motor_pwr2 = constrain(kp2*(setCurrent2-thisCurrent2)+ki2*error2,0,max_pwm);
////  Serial.print(motor_pwr1);
////  Serial.print(", ");
////  Serial.print(error1);
////  Serial.print(", ");
////  Serial.print(setCurrent1);
////  Serial.print(", ");
////  Serial.println(thisCurrent1);
//  
//  uint16_t dt = millis()-t_start;
//  if (dt < 1000) {
//    analogWrite(pwm1, motor_pwr1);
//    analogWrite(pwm2, motor_pwr2);
//  } else {
////    Serial.println("off");
//    analogWrite(pwm1, 0);
//    analogWrite(pwm2, 0);
//  }
}

float measureCurrent1() {
  // about 500mV per Amp
  return (analogRead(c_sense1)*0.009775); //adc to A
}

uint16_t measureCurrentInt1() {
  // about 500mV per Amp
  return analogRead(c_sense1);
}

void encA1trig() {
  if (digitalRead(encA1) == HIGH) {
    if (digitalRead(encB1) == LOW) {
      motor_pos1++;
    } else {
      motor_pos1--;
    }
  } else {
    if (digitalRead(encB1) == LOW) {
      motor_pos1--;
    } else {
      motor_pos1++;
    }
  }
}

