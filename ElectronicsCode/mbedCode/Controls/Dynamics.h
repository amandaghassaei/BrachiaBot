#ifndef Dynamics_h
#define Dynamics_h


#include "Kinematics.h"
#include "Gains.h"
#include "Target.h"


float calcTau(float output[2], volatile float z[4], float p[10], Gains *gains, Target *target, Serial *pc);
float thetaDesiredForSwingUp(float rangeMin, float rangeMax, volatile float z[4]);
float obstacleAvoidance(volatile float z[4], float p[10], float theta);
float overallGainForSwingUp(volatile float z[4], float th2Des, Gains *gains);


#endif