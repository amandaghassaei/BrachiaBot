#ifndef Kinematics_h
#define Kinematics_h

    
void getMassMatrix(float A[2][2], volatile float z[4], float p[10]);
float getPositionOfFoot();
float getEnergy(volatile float z[4], float p[10]);
float getGravity(volatile float z[4], float p[10]);
float getCoriolis(volatile float z[4], float p[10]);


#endif