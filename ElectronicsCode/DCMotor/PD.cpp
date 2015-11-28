

#include "PD.h"


PD::PD()
{
  _proportionalGain = 0;
  _derivativeGain = 0;
  _error = 0;
}

void PD::setGains(float proportionalGain, float derivativeGain)
{
  _proportionalGain = proportionalGain;
  _derivativeGain = derivativeGain;
}

float PD::calc(long currentVal, long target)
{
  float newError = _error + target-currentVal;
  newError = constrain(newError, -100, 100);
  float val = _proportionalGain*(target-currentVal)+_derivativeGain*(_error-newError);
  _error = newError;
  return val;
}

