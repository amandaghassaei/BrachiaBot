#include "MicroGearMotor.h"


MicroGearMotor::MicroGearMotor(byte dirPin, byte pwmPin, byte currentPin, byte encoderAPin, byte encoderBPin, boolean invertDirection, int encoderTicks, int gearRatio)
{ 
  _encoderTicks = encoderTicks;
  _gearRatio = gearRatio;
  
  _currentLimitHit = false;
  
  _invertDirection = invertDirection;
  
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
  _targetCurrent = int(0.8/0.009775);//we'll want to set this to the current needed to place vox
  _currentFilter = new LPFilter();
  _currentPID = new PD();
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

void MicroGearMotor::setSpeedPIDGains(float proportionalGain, float derivativeGain)
{
  _speedPID->setGains(proportionalGain, derivativeGain);
}

void MicroGearMotor::setCurrentPIDGains(float proportionalGain, float derivativeGain)
{
  _currentPID->setGains(proportionalGain, derivativeGain);
}

void MicroGearMotor::moveTo(float targetPosition, float targetSpeed)
{
  _targetPosition = targetPosition/TWO_PI*_gearRatio*_encoderTicks*2;
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
  
  float rampLength = 50.0;
  float rampedSpeed = _targetSpeed/rampLength*constrain(_targetPosition-_position, -rampLength, rampLength);
  
  int pwm = _speedPID->calc(_speed, rampedSpeed);
  pwm = constrain(pwm, -MAX_PWM, MAX_PWM);
  
  if (_invertDirection) digitalWrite(_dirPin, pwm < 0);
  else digitalWrite(_dirPin, pwm > 0);
  analogWrite(_pwmPin, abs(pwm));
  
  _current = _currentFilter->step(this->_measureCurrent());
  if (_current > MAX_CURRENT) this->motorStop();  
  else _currentLimitHit = false;
}


void MicroGearMotor::motorStop()
{
//  Serial.println("stop");
  _currentLimitHit = true;
  digitalWrite(13, HIGH);
  
  _targetSpeed = 0;
  _targetPosition = _position;
}

float MicroGearMotor::getPosition()
{
  float positionInRad = _position*TWO_PI/(_gearRatio*_encoderTicks*2);
  if (_invertDirection) return -positionInRad;
  return positionInRad;
}

float MicroGearMotor::getTargetPosition()
{
  return _targetPosition*TWO_PI/_gearRatio/_encoderTicks;
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
