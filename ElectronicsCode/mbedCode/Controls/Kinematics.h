#ifndef Kinematics_h
#define Kinematics_h

    
void getMassMatrix(float A[2][2]);
float getPositionOfFoot();
float getEnergy(float z[4], float p[10]);
float getGravity(float z[4], float p[10]);
float getCoriolis(float z[4], float p[10]);


#endif