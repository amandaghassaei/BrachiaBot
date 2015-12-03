#include "Kinematics.h"
#include <math.h>


void getMassMatrix(float A[2][2]){
    A[0][0] = 0;
    A[0][1] = 0;
    A[1][0] = 0;
    A[1][1] = 0;
}

float getPositionOfFoot(){
    return 0;
}

float getEnergy(float z[4], float p[10]){
    float I1 = p[6];
    float I2 = p[7];
    float c1 = p[2];
    float c2 = p[3];
    float dth1 = z[2];
    float dth2 = z[3];
    float g = p[8];
    float l1 = p[0];
    float m1 = p[4];
    float m2 = p[5];
    float th1 = z[0];
    float th2 = z[1];
    float t2 = pow(dth1,2);
    float t3 = pow(c2,2);
    float t4 = pow(dth2,2);
    float t5 = cos(th1);
    float t6 = cos(th2);
    return I1*t2*(1.0/2.0)+I2*t2*(1.0/2.0)+I2*t4*(1.0/2.0)+pow(c1,2)*m1*t2*(1.0/2.0)+pow(l1,2)*m2*t2*(1.0/2.0)-g*m2*(l1*t5+c2*cos(th1+th2))+m2*t2*t3*(1.0/2.0)+m2*t3*t4*(1.0/2.0)+dth1*dth2*m2*t3-c1*g*m1*t5+c2*l1*m2*t2*t6+c2*dth1*dth2*l1*m2*t6;
}

float getGravity(float z[4], float p[10]){
//    c1 = p(3,:);
    float c2 = p[3];
    float g = p[8];
//    l1 = p(1,:);
//    m1 = p(5,:);
    float m2 = p[5];
    float th1 = z[0];
    float th2 = z[1];
//    t2 = sin(th1);
    float t3 = th1+th2;
    float t4 = sin(t3);
    return c2*g*m2*t4;
}

float getCoriolis(float z[4], float p[10]){
    float c2 = p[3];
    float dth1 = z[2];
//    float dth2 = z[3];
    float l1 = p[0];
    float m2 = p[5];
    float th2 = z[1];
    float t2 = sin(th2);
    return c2*pow(dth1,2)*l1*m2*t2;
}