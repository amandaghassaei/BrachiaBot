#include "Dynamics.h"
#include <math.h>
# define M_PI           3.14159265358979323846

float calcTau(volatile float z[4], float p[10], Gains *gains, Serial *pc){
            
    float A[2][2];
    getMassMatrix(A, z, p);
    
    float th1 = z[0];
    float th2 = z[1];
    float dth1 = z[2];
    float dth2 = z[3];
    
    float E = getEnergy(z, p);
    
    float A_hat22 = A[1][1]-A[1][0]*A[0][1]/A[0][0];
    float K = gains->getSwingUpK();
    float D = gains->getSwingUpD();
    
    float th2Des = thetaDesired(3*M_PI/6, th1, th2, dth1, dth2);
    
    float v = K*(th2Des - th2) - D*dth2;// + k3*u_hat;
    float energyIncr = A_hat22*v;

    float obstacleAvoidance = 0;//%obstacle_avoidance(z, p);

    //Compute virtual foce
//%     J = gripper_jacobian;
//%     lambda = A*J_inv;

    float gravityComp = 0;//getGravity(z, p);

    //todo coriolis/cetripedal compensation
    float corCentripComp = 0;//getCoriolis(z, p);// - A_hat22*gripper_jacobian(z,p)*dth2;

    return obstacleAvoidance + energyIncr + gravityComp + corCentripComp;
}

float thetaDesired(float range, float th1, float th2, float dth1, float dth2){
    
//    int numTurns = fix(th1/(2*M_PI));
    float th1Rel = th1;//-numTurns*2*M_PI;
    
    return signNonZero(dth1)*(range-abs(th1Rel));//*cos(th1)
}

int fix(float val){//round toward zero
    return val/1;
}

int signNonZero(float val){
    if (val < 0) return -1;
    return 1;
}