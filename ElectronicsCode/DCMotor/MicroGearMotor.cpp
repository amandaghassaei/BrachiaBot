#include "MicroGearMotor.h"


MicroGearMotor::MicroGearMotor(byte dirPin, byte pwmPin, byte currentPin, byte encoderAPin, byte encoderBPin, int encoderTicks, int gearRatio)
{ 
  _encoderTicks = encoderTicks;
  _gearRatio = gearRatio;
  
  _currentLimitHit = false;
    
  _dirPin = dirPin;
  _pwmPin = pwmPin;
  _currentPin = currentPin;
  _encoderAPin = encoderAPin;
  _encoderBPin = encoderBPin;
  
  _position = 0;
  _targetPosition = _position;
  
  _rawSpeed = 0;
  _speed = _rawSpeed;
  _targetSpeed = _rawSpeed;
  _speedFilter = new LPFilter();
  _speedPID = new PD();
  
  _current = 0;
  _currentFilter = new LPFilter();
}

void MicroGearMotor::init()
{
  pinMode(_dirPin, OUTPUT);
  pinMode(_pwmPin, OUTPUT);
  pinMode(_currentPin, INPUT);
  pinMode(_encoderAPin, INPUT);
  pinMode(_encoderBPin, INPUT);
  
  _lastSpeedCalcTime = micros();
  _lastSpeedPosition = _position;
  _currentFilter->init(2.5, this->_measureCurrent());
  _speedFilter->init(2.5, _speed);
}

boolean MicroGearMotor::calibrate()
{
  float zero = 0;
  float maxCurrent = 0;
  long timeout = millis();
  for (float i=0.2;i<TWO_PI*3/2;i+=0.2){
    this->moveTo(i, 40);
    while(!this->targetReached()){
      if (millis()-timeout>700) {
        Serial.println("stop");
        return false;
      }
      this->update();
    }
    this->motorStop();
    delay(500);
    
    float current = this->getCurrent();
    if (current>maxCurrent) {
        zero = this->getPosition();
        maxCurrent = current;
      }
    timeout = millis();
  }
  Serial.println(zero);
  this->moveTo(zero, 40);
  while(!this->targetReached()){
    this->update();
  }
  this->motorStop();
  
  
  return true;

//  while(!this->targetReached()){
//    if (micros()-timeout>700) {
//        Serial.println("stop");
//        stopHit = true;
//        break;
//      }
//    this->update();
//  }
//  Serial.println("here");
//  this->moveTo(1, 50);
//  while(!this->targetReached()){
//    this->update();
//  }
}


void MicroGearMotor::setSpeedPIDGains(float proportionalGain, float derivativeGain)
{
  _speedPID->setGains(proportionalGain, derivativeGain);
}

void MicroGearMotor::moveTo(float targetPosition, float targetSpeed)
{
  _targetPosition = targetPosition/TWO_PI*_gearRatio*_encoderTicks;
  _targetSpeed = targetSpeed;
}

void MicroGearMotor::update()
{
  float deltaT = micros() - _lastSpeedCalcTime;
  if (deltaT > 0) {//protects against overflow of _lastSpeedCalcTime, happens every 70 minutes
    _rawSpeed = (_position - _lastSpeedPosition)*1000/deltaT;
    _speed = _speedFilter->step(_rawSpeed);
  }
  _lastSpeedCalcTime = micros();
  _lastSpeedPosition = _position;
  
  
//  if (this->targetReached()) return;
  float rampLength = 50.0;
  float rampedSpeed = _targetSpeed/rampLength*constrain(_targetPosition-_position, -rampLength, rampLength);
  
  int pwm = _speedPID->calc(_speed, rampedSpeed);
  pwm = constrain(pwm, -MAX_PWM, MAX_PWM);
  
  digitalWrite(_dirPin, pwm > 0);
  analogWrite(_pwmPin, abs(pwm));
    
  _current = _currentFilter->step(this->_measureCurrent());
  if (_current > MAX_CURRENT) this->motorStop();  
  else _currentLimitHit = false;
}


void MicroGearMotor::motorStop()
{
  Serial.println("stop");
  _currentLimitHit = true;
  digitalWrite(13, HIGH);
  
  _targetSpeed = 0;
  _targetPosition = _position;
  this->update();
}

long MicroGearMotor::getTicks()
{
  return _position;
}

float MicroGearMotor::getPosition()
{
  return _position*TWO_PI/(_gearRatio*_encoderTicks);
}

float MicroGearMotor::getTargetPosition()
{
  return _targetPosition*TWO_PI/(_gearRatio*_encoderTicks);
}

float MicroGearMotor::getTargetSpeed()
{
  return _targetSpeed;
}

float MicroGearMotor::getSpeed()
{
  return _speed;
}

float MicroGearMotor::getCurrent()
{
  return _current;
}

boolean MicroGearMotor::currentLimitHit()
{
  return _currentLimitHit;
}

void MicroGearMotor::zero()
{
  _position = 0;
}

boolean MicroGearMotor::targetReached()
{
   return abs(_position-_targetPosition) < 10;
}

float MicroGearMotor::_measureCurrent()//returns mA
{
  return analogRead(_currentPin)*10/1.023;//~500mV per Amp
}

void MicroGearMotor::interruptRoutine()
{
  if (digitalRead(_encoderAPin)) {
    if (!digitalRead(_encoderBPin)) {
      _position++;
    } else {
      _position--;
    }
  } else {
    if (!digitalRead(_encoderBPin)) {
      _position--;
    } else {
      _position++;
    }
  }
}
