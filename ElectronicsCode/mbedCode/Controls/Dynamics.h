#ifndef Dynamics_h
#define Dynamics_h

#include "Kinematics.h"


float calcTau(float z[4], float p[10]);
float thetaDesired(float range, float th1, float th2, float dth1, float dth2);
int fix(float val);//round toward zero
int signNonZero(float val);





#endif