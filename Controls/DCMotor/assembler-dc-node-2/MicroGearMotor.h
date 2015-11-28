
#ifndef MicroGearMotor_h
#define MicroGearMotor_h

#include "Arduino.h"
#include "low_pass_filter.h"
#include "PID.h"

//keep in safe range
#define MAX_CURRENT 1300//mA (datasheet says 1600 at 6V)
#define MAX_PWM 100


class MicroGearMotor
{
  public:
  
    MicroGearMotor(byte dirPin, byte pwmPin, byte currentPin, byte encoderAPin, byte encoderBPin, boolean invertDirection);
    void init();//call from setup()
    
    void setSpeedPIDGains(float proportionalGain, float integralGain);
    void setCurrentPIDGains(float proportionalGain, float integralGain);

    void moveTo(long targetPosition, float targetSpeed);
    boolean targetReached();
    void zero();
    void motorStop();
    long getPosition();
    long getTargetPosition();
    float getTargetSpeed();
    
    float getCurrent();
    boolean currentLimitHit();
    
    void update(float speedCorrection);//call from loop
    
    void interruptRoutine();
  
  private:
  
    boolean _currentLimitHit;
  
    boolean _invertDirection;//in case motors are pointed in different directions
  
    byte _dirPin, _pwmPin, _currentPin, _encoderAPin, _encoderBPin;
    
    volatile long _position;//measured in encoder ticks (3000 ticks per inch)
    long _targetPosition;
    
    float _rawSpeed;//measured in ticks per ms
    long _lastSpeedPosition;//use this to get delta position for speed calc
    long _lastSpeedCalcTime;//use this to calc dt for measuring speed from delta position
    float _speed;
    float _targetSpeed;//this is always a positive number - absolute speed
    LPFilter *_speedFilter;
    PID *_speedPID;
    
    float _current;//mA
    float _targetCurrent;
    LPFilter *_currentFilter;
    PID *_currentPID;
    float _measureCurrent();
};


#endif
