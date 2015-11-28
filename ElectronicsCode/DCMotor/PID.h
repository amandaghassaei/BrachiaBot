
#ifndef PID_h
#define PID_h

#include <Arduino.h>

class PID
{
  public:
    
    PID();
    void setGains(float proportianalGain, float integralGain);
    
    //return a pwn to set for dc motor
    float calc(long currentVal, long target);
 
  private:
  
    float _proportionalGain;
    float _integralGain;
   
    float _error;
};

#endif

