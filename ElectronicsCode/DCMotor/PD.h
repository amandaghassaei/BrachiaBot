
#ifndef PID_h
#define PID_h

#include <Arduino.h>

class PD
{
  public:
    
    PD();
    void setGains(float proportianalGain, float derivativeGain);
    
    //return a pwn to set for dc motor
    float calc(long currentVal, long target);
 
  private:
  
    float _proportionalGain;
    float _derivativeGain;
   
    float _error;
};

#endif

