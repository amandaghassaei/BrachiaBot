#include "Dynamics.h"
#include <math.h>
# define M_PI           3.14159265358979323846

float calcTau(float output[2], volatile float z[4], float p[10], Gains *gains, Target *target, Serial *pc){
    
    float th1 = z[0];
    float th2 = z[1];
    float dth1 = z[2];
    float dth2 = z[3];
    
    float A[2][2];
    getMassMatrix(A, z, p);
    float AHat = A[1][1]-A[1][0]*A[0][1]/A[0][0];
    
    float corrCentripComp[2];
    getCoriolisCentrip(corrCentripComp, z, p);
    float corrCentripCompHat = corrCentripComp[1]-A[1][0]*corrCentripComp[0]/A[0][0];
    
    float gravityComp[2];
    getGravity(gravityComp, z, p);
    float gravityCompHat = gravityComp[1]-A[1][0]*gravityComp[0]/A[0][0];
    
    
    
    float force = 0;
//    if (target->getTargetingStarted() && target->shouldOverrideTargetingMode(z, p)){
//        target->setTargetingStarted(false);
//    } else if (target->getTargetingStarted() || target->shouldSwitchToTargetingController(z, p)) {
//        target->setTargetingStarted(true);
//        float K = gains->getTargetingK();
//        float D = gains->getTargetingD();
//        force = target->calcTargetingForce(z, p, K, D);
//    } else {
        float K = gains->getSwingUpK();
        float D = gains->getSwingUpD();
        float softLimit = 2.3;//2.5;//143 degrees
//        float th2Des = output[1];
//        if (abs(dth1)>3.0) 
        float th2Des = thetaDesiredForSwingUp(-softLimit, softLimit, z);
        th2Des = obstacleAvoidance(z, p, th2Des);
        float P = overallGainForSwingUp(z, th2Des, gains);
        force = P*(K*(th2Des - th2) - D*dth2);//AHat*
//        output[1] = th2Des;
//    }

//    output[0] = force + corrCentripCompHat + gravityCompHat;
    return force + corrCentripCompHat + gravityCompHat;
}

float obstacleAvoidance(volatile float z[4], float p[10], float theta){
    
    float armLength = p[0];
    float latticePitch = p[9];
    
    float safeRad = 0.02;
    float th2MinMin = M_PI-2.0*asin((latticePitch-safeRad)/(2.0*armLength));
    float th2MinMax = M_PI-2.0*asin((latticePitch*sqrt(2.0)-safeRad)/(2.0*armLength));
    
    float th2MinAvg = (th2MinMin+th2MinMax)/2.0;
    float th2MinAmp = (th2MinMin-th2MinAvg);
    
    float th1 = z[0];
    float th2 = z[1];
    
    float direction = 1;
    if (th2<0) direction = -1;
    
    float th2MinPhase = direction*th2MinMin;
    float th2Min = th2MinAvg+th2MinAmp*cos(4.0*(th1+th2MinPhase));
    
    if (direction*theta < th2Min) return direction*th2Min;
    return theta;
}

float thetaDesiredForSwingUp(float rangeMin, float rangeMax, volatile float z[4]){
    
    float th1 = z[0];
    float dth1 = z[2];
//    float th1Rel = boundTheta(th1);
    
    if (dth1<0) return rangeMin*abs(cos(th1/2.0));//-abs(th1Rel));//*cos(th1)
    return rangeMax*abs(cos(th1/2.0));
}


float overallGainForSwingUp(volatile float z[4], float th2Des, Gains *gains){
    float th2 = z[1];
    float dth1 = z[2];
    if ((dth1<0 && th2<th2Des) || (dth1>0 && th2>th2Des)) return gains->getSoftLimitsP();
    return gains->getDesiredThetaP();
}