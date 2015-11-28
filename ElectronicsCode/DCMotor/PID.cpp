

#include "PID.h"


PID::PID()
{
  _proportionalGain = 0;
  _integralGain = 0;
  _error = 0;
}

void PID::setGains(float proportionalGain, float integralGain)
{
  _proportionalGain = proportionalGain;
  _integralGain = integralGain;
}

float PID::calc(long currentVal, long target)
{
  _error += target-currentVal;
  _error = constrain(_error, -100, 100);
  return _proportionalGain*(target-currentVal)+_integralGain*_error;
}

