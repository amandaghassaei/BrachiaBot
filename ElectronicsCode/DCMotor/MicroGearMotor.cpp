#include "MicroGearMotor.h"


MicroGearMotor::MicroGearMotor(byte dirPin, byte pwmPin, byte currentPin, byte encoderAPin, byte encoderBPin, boolean invertDirection)
{ 
   _currentLimitHit = false;
  
  _invertDirection = invertDirection;
  
  _dirPin = dirPin;
  _pwmPin = pwmPin;
  _currentPin = currentPin;
  _encoderAPin = encoderAPin;
  _encoderBPin = encoderBPin;
  
  _position = 0;
  _targetPosition = this->getPosition();
  
  _rawSpeed = 0;
  _speed = _rawSpeed;
  _targetSpeed = _rawSpeed;
  _speedFilter = new LPFilter();
  _speedPID = new PID();
  
  _current = 0;
  _targetCurrent = int(0.8/0.009775);//we'll want to set this to the current needed to place vox
  _currentFilter = new LPFilter();
  _currentPID = new PID();
}

void MicroGearMotor::init()
{
  pinMode(_dirPin, OUTPUT);
  pinMode(_pwmPin, OUTPUT);
  pinMode(_currentPin, INPUT);
  pinMode(_encoderAPin, INPUT);
  pinMode(_encoderBPin, INPUT);
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  
  _lastSpeedCalcTime = micros();
  _lastSpeedPosition = this->getPosition();
  _currentFilter->init(2.5, this->_measureCurrent());
  _speedFilter->init(2.5, _speed);
}

void MicroGearMotor::setSpeedPIDGains(float proportionalGain, float integralGain)
{
  _speedPID->setGains(proportionalGain, integralGain);
}

void MicroGearMotor::setCurrentPIDGains(float proportionalGain, float integralGain)
{
  _currentPID->setGains(proportionalGain, integralGain);
}

void MicroGearMotor::moveTo(long targetPosition, float targetSpeed)
{
  _targetPosition = targetPosition;
  _targetSpeed = targetSpeed;
}

void MicroGearMotor::motorStop()
{
//  Serial.println("stop");
  _currentLimitHit = true;
  digitalWrite(13, HIGH);

  //back off a bit
  
//  _targetSpeed = 0;
//  _targetPosition = this->getPosition();
}

long MicroGearMotor::getPosition()
{
  if (_invertDirection) return -_position;
  return _position;
}

long MicroGearMotor::getTargetPosition()
{
  return _targetPosition;
}

float MicroGearMotor::getTargetSpeed()
{
  return _targetSpeed;
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

void MicroGearMotor::update(float speedCorrection)
{
  float deltaT = micros() - _lastSpeedCalcTime;
  if (deltaT > 0) {//protects against overflow of _lastSpeedCalcTime, happens every 70 minutes
    _rawSpeed = (this->getPosition() - _lastSpeedPosition)*1000/deltaT;
    _speed = _speedFilter->step(_rawSpeed);
  }
  _lastSpeedCalcTime = micros();
  _lastSpeedPosition = this->getPosition();
  
  if (_targetPosition-this->getPosition() < 0) speedCorrection *= -1;
  float correctedTargetSpeed = _targetSpeed + 0.1*speedCorrection;
  
  float rampLength = 50.0;
  float rampedSpeed = correctedTargetSpeed/rampLength*constrain(_targetPosition-this->getPosition(), -rampLength, rampLength);
  
  int pwm = _speedPID->calc(_speed, rampedSpeed);
  pwm = constrain(pwm, -MAX_PWM, MAX_PWM);
  
  if (_invertDirection) digitalWrite(_dirPin, pwm < 0);
  else digitalWrite(_dirPin, pwm > 0);
  analogWrite(_pwmPin, abs(pwm));
  
  _current = _currentFilter->step(this->_measureCurrent());
  if (_current > MAX_CURRENT) this->motorStop();  
  else _currentLimitHit = false;
}

boolean MicroGearMotor::targetReached()
{
   return abs(this->getPosition()-_targetPosition) < 10;
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
