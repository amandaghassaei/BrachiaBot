#ifndef Kinematics_h
#define Kinematics_h

    
void getMassMatrix(float A[2][2], volatile float z[4], float p[10]);
float getEnergy(volatile float z[4], float p[10]);
void getGravity(float output[2], volatile float z[4], float p[10]);
void getCoriolisCentrip(float output[2], volatile float z[4], float p[10]);
void getGripperPosition(float position[2], volatile float z[4], float p[10]);
void getGripperVelocity(float velocity[2], volatile float z[4], float p[10]);
void getGripperJacobianTranspose(float Jtrans[2][2], volatile float z[4], float p[10]);
float boundTheta(float theta);
int fix(float val);//round toward zero


#endif