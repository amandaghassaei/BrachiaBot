#ifndef Target_h
#define Target_h

#define M_PI 3.14159265358979323846
//#include <math.h>
#include "Kinematics.h"


class Target{
//            1   2   3
//            4   5   6
//            7   8   9

    public:
    
        Target():_myled(LED1){
            _latticePitch = 0.350;
            setTargetingStarted(false);
            setFinalDTh1(0);
        }
        
        void setPC(Serial *pc){
            _pc = pc;
        }
    
        void setPosition(int position, float p[10]){
            if (position != 4 && position != 6) position = 6;
            _position = position;
            _th1Final = finalAngleTh1(position, p[0]);//p[0] = linkLength
            _th2Final = finalAngleTh2(position, p[0]);
            float z[4] = {_th1Final, _th2Final, 0, 0};
            _energy = getEnergy(z, p);
        }
    
        int getPosition(){
            return _position;
        }
        
        float getTargetEnergy(){
            return _energy;
        }
        
        float getFinalTh1(volatile float z[4]){
            return _th1Final*finalAngleSign(z, _position);
        }
        
        float getFinalTh2(volatile float z[4]){
            return _th2Final*finalAngleSign(z, _position);
        }
        
        void setFinalDTh1(float dth1Final){
            _dth1Final = dth1Final;
        }
        
        float getFinalDTh1(){
            return _dth1Final;
        }
        
        bool getTargetingStarted(){
            return _isTargeting;
        }
        
        void setTargetingStarted(bool state){
            _isTargeting = state;
            _myled = state;
        }
        
        bool shouldSwitchToTargetingController(volatile float z[4], float p[10]){

            float th1 = z[0];
            float th2 = z[1];
            float dth1 = z[2];
//            float dth2 = z[3];
            
            float currentEnergy = getEnergy(z, p);
            float th1Final = getFinalTh1(z);
            float th2Final = getFinalTh2(z);
            
            float targetEnergy = getTargetEnergy();
            
            
            if (currentEnergy < targetEnergy) return false;
//            if (abs(dth1) < getFinalDTh1()/2.0) return false;
                
            float targetApproachDir = 1;
            if (dth1<0) targetApproachDir = -1;
            float desiredTargetApproachDirection = targetDirection(_position);
            if (desiredTargetApproachDirection != 0 && targetApproachDir != desiredTargetApproachDirection) return false;   
            
//            float th2TargetApproachDir = 1;
//            if (th2<0) th2TargetApproachDir = -1;
//            if (th2TargetApproachDir != targetApproachDir) return false;    
            
//            float th1Rel = boundTheta(th1);
            
            if (targetApproachDir*th1 > targetApproachDir*th1Final-M_PI/4) return false;        
            if (targetApproachDir*th1 > targetApproachDir*th1Final-2*M_PI/3) return true;
            return false;
        }
        
        bool shouldOverrideTargetingMode(volatile float z[4], float p[10]){
                        
            float th1 = z[0];
            float th2 = z[1];
            float dth1 = z[2];
            float dth2 = z[3];
            
            float th1Final = getFinalTh1(z);
            
            float targetApproachDirection = 1.0;
            if (th2<0) targetApproachDirection = -1.0;
            
            float th1Direction = 1.0;
            if (dth1<0) th1Direction = -1;
        
            if (targetApproachDirection*th1 > targetApproachDirection*th1Final - M_PI/8.0) return false;
                
            if (th1Direction != targetApproachDirection) return true;
            
            return false;
        }
        
        float calcDistTotarget(volatile float z[4], float p[10]){
            float th1 = z[0];
            float th2 = z[1];
            float dth1 = z[2];
            float dth2 = z[3];
                               
            float targetPosition[2];
            targetPosition[0] = targetXPosition(_position);
            targetPosition[1] = targetYPosition(_position);
            
            float gripperPosition[2];
            getGripperPosition(gripperPosition, z, p);
            
            return sqrt((gripperPosition[0]-targetPosition[0])*(gripperPosition[0]-targetPosition[0]) + 
                (gripperPosition[1]-targetPosition[1])*(gripperPosition[1]-targetPosition[1]));
        }
        
        void calcTargetingTrajectoryParams(float mags[2], float direction[2], volatile float z[4], float p[10]){
            float th1 = z[0];
            float th2 = z[1];
            float dth1 = z[2];
            float dth2 = z[3];
               
            float th1Final = getFinalTh1(z);
            float th2Final = getFinalTh2(z);
                
            float targetPosition[2];
            targetPosition[0] = targetXPosition(_position);
            targetPosition[1] = targetYPosition(_position);
            
            float mAngle = th1Final;
            if (mAngle > M_PI/2.0) mAngle -= M_PI/2.0;
            else if (mAngle < -M_PI/2.0) mAngle += M_PI/2.0;
            float m = 1.0/tan(mAngle);
            float a = -m;
            float b = 1.0;
            float c = m*targetPosition[0]-targetPosition[1];
            
            float gripperPosition[2];
            getGripperPosition(gripperPosition, z, p);
            float gripperVelocity[2];
            getGripperVelocity(gripperVelocity, z, p);
            
            float x = (b*(b*gripperPosition[0] - a*gripperPosition[1])-a*c)/(a*a + b*b)-gripperPosition[0];
            float y = (a*(-b*gripperPosition[0] + a*gripperPosition[1])-b*c)/(a*a + b*b)-gripperPosition[1];
            float norm = sqrt(x*x + y*y);
            float xUnit = x/norm;
            float yUnit = y/norm;
            float dNorm = gripperVelocity[0]*xUnit + gripperVelocity[1]*yUnit;
            
            mags[0] = norm;
            mags[1] = dNorm;
            direction[0] = xUnit;
            direction[1] = yUnit;
        }
        
        float calcTargetingForce(volatile float z[4], float p[10], float K, float D){
                        
            float mags[2];
            float direction[2];
            calcTargetingTrajectoryParams(mags, direction, z, p);
            
            float norm = mags[0];
            float dNorm = mags[1];
            float xUnit = direction[0];
            float yUnit = direction[1];
            
            float forceMag = (K*norm - D*dNorm);
            float forceTaskSp[2] = {forceMag*xUnit, forceMag*yUnit};
            float Jtrans[2][2];
            getGripperJacobianTranspose(Jtrans, z, p);            
        
            return Jtrans[0][1]*forceTaskSp[0]+Jtrans[1][1]*forceTaskSp[1];
        }
        
        float calcTargetingForceAlongGradient(volatile float z[4], float p[10], float K, float D){
                        
            float th1 = z[0];
            float th2 = z[1];
            float dth1 = z[2];
            float dth2 = z[3];
               
            float th1Final = getFinalTh1(z);
            float th2Final = getFinalTh2(z);
                
            float targetPosition[2];
            targetPosition[0] = targetXPosition(_position);
            targetPosition[1] = targetYPosition(_position);
            
            float gripperPosition[2];
            getGripperPosition(gripperPosition, z, p);
            float gripperVelocity[2];
            getGripperVelocity(gripperVelocity, z, p);
            
            float x = targetPosition[0]-gripperPosition[0];
            float y = targetPosition[1]-gripperPosition[1];
            float norm = sqrt(x*x + y*y);
            float xUnit = x/norm;
            float yUnit = y/norm;
            float dNorm = gripperVelocity[0]*xUnit + gripperVelocity[1]*yUnit;
            
            float forceMag = (K*norm - D*dNorm);
            float forceTaskSp[2] = {forceMag*xUnit, forceMag*yUnit};
            float Jtrans[2][2];
            getGripperJacobianTranspose(Jtrans, z, p);  
            
            float A[2][2];
            getMassMatrix(A, z, p);            
            float jointSp0 = Jtrans[0][0]*forceTaskSp[0]+Jtrans[1][0]*forceTaskSp[1];
            float jointSp1 = Jtrans[0][1]*forceTaskSp[0]+Jtrans[1][1]*forceTaskSp[1];
        
            return jointSp1-A[1][0]*jointSp0/A[0][0];         
        }
    
    
    private:
    
        Serial *_pc;
        
        bool _isTargeting;
        
        DigitalOut _myled;
    
        int _position;
        float _energy;
        float _th1Final;
        float _th2Final;
        float _dth1Final;
        float _latticePitch;
        
        float finalAngleTh1(float targetPosition, float armLength){
            float th1;
            if (targetIsCardinal(targetPosition)) th1 = asin(1/2.0*_latticePitch/armLength);
            else th1 = asin(1/2.0*_latticePitch*sqrt(double(2))/armLength);
            th1 += finalAngleTh1Rotation(targetPosition);
            return th1;
        }
        
        float finalAngleTh1Rotation(float targetPosition){
            if (targetPosition == 2) return M_PI/2.0;
            if (targetPosition == 8) return -M_PI/2.0;
            if (targetPosition == 1 || targetPosition == 3) return M_PI/4.0;
            if (targetPosition == 7 || targetPosition == 9) return -M_PI/4.0;
            return 0;
        }
        
        float finalAngleTh2(float targetPosition, float armLength){
            if (targetIsCardinal(targetPosition)) return M_PI-2.0*asin(1/2.0*_latticePitch/armLength);
            return M_PI-2.0*asin(1/2.0*_latticePitch*sqrt(double(2.0))/armLength);
        }
        
        bool targetIsCardinal(float targetPosition){
            if (fmod(targetPosition,2) == 0) return true;
            return false;
        }
        
        float finalAngleSign(volatile float z[4], float targetPosition){
            float approachDirection = targetDirection(targetPosition);
            if (approachDirection<0 || (approachDirection==0 && z[3]<0)) return -1;
            return 1;
        }
        
        float targetDirection(float targetPosition){
            if (targetPosition == 1 || targetPosition == 4 || targetPosition == 7) return -1;
            if (targetPosition == 3 || targetPosition == 6 || targetPosition == 9) return 1;
            return 0;
        }
        
        float targetXPosition(float targetPosition){
            if (targetPosition == 1 || targetPosition == 4 || targetPosition == 7) return -_latticePitch;
            if (targetPosition == 2 || targetPosition == 5 || targetPosition == 8) return 0;
            if (targetPosition == 3 || targetPosition == 6 || targetPosition == 9) return _latticePitch;
            _pc->printf("invalid target position %f\n", targetPosition);
            return _latticePitch;
        }
        
        float targetYPosition(float targetPosition){
            if (targetPosition < 4) return _latticePitch;
            if (targetPosition < 7) return 0;
            if (targetPosition < 10) return -_latticePitch;
            _pc->printf("invalid target position %f\n", targetPosition);
            return 0;
        }
    
};

#endif