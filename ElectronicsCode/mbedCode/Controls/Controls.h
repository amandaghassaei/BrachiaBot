#ifndef Controls_h
#define Controls_h

#include <math.h>
#include "Gains.h"
#include "Target.h"
#include "MyMPU6050.h" 
#include "Motor.h"  
#include "Dynamics.h"

#define controlTimerPeriod 0.001

class Controls: public CommDelegate{
    
    public:
    
        Controls():myMPU6050_1(p28, p27, p18), myMPU6050_2(p9, p10, p11){//I2C_SDA, I2C_SCL, int_pin
        }
        
        void setup(){
            setInverted(false);
            
            _softLimit = 2.35;
            _lastTh2Desired = _softLimit;
            
            float m1 = 0.93159230;
            float m2 = 0.45433433;
            float l1 = 0.275;//length of links
            float l2 = l1;
            float I1 = 0.03736067;
            float I2 = 0.01778165;
            float c1 = l1-0.08567346;//location of center of mass along link
            float c2 = 0.17594269;
            float g = 9.81;
            float lattice_pitch  = 0.35;
            _parameters[0] = l1;
            _parameters[1] = l2;
            _parameters[2] = c1;
            _parameters[3] = c2;
            _parameters[4] = m1;
            _parameters[5] = m2;
            _parameters[6] = I1;
            _parameters[7] = I2;
            _parameters[8] =  g;
            _parameters[9] = lattice_pitch;
            
            _manualTheta = 0;
            
            setTargetPosition(6);//only 4 and 6 for now
        }
        
        void setInverted(bool inverted){
            _inverted = inverted;
            if (!_inverted) {
                myMPU6050_2.disable();
                myMPU6050_1.enable();
//                motor.setGearRatio(10.164);
            } else {
                myMPU6050_1.disable();
                myMPU6050_2.enable();
//                motor.setGearRatio(11.164);
            }
        }
        
        void setPC(Serial *pc){
            _pc = pc;
            motor.setPC(pc);
            gains.setPC(pc);
            target.setPC(pc);
            myMPU6050_1.setPC(pc);
            myMPU6050_2.setPC(pc);
        }
    
        Gains gains;
        void setSwingUpK(float k){
            gains.setSwingUpK(k);
        };
        void setSwingUpD(float d){
            gains.setSwingUpD(d);
        };
        void setDesiredThetaP(float p){
            gains.setDesiredThetaP(p);
        };
        void setSoftLimitsP(float p){
            gains.setSoftLimitsP(p);
        };
        float getSwingUpK(){
            return gains.getSwingUpK();
        };
        float getSwingUpD(){
            return gains.getSwingUpD();
        };
        float getDesiredThetaP(){
            return gains.getDesiredThetaP();
        };
        float getSoftLimitsP(){
            return gains.getSoftLimitsP();
        };
        
        Target target;
        void setTargetPosition(int position){
            target.setPosition(position, _parameters);
        };
        int getTargetPosition(){
            return target.getPosition();
        };
        
        void setTargetingK(float k){
            gains.setTargetingK(k);
        };
        void setTargetingD(float d){
            gains.setTargetingD(d);
        };
        float getTargetingK(){
            return gains.getTargetingK();
        };
        float getTargetingD(){
            return gains.getTargetingD();
        };
        
        Motor motor;
        void setTheta(float theta){
            _manualTheta = theta;
        };
        
        float _manualTheta;
    
        //imu
        MyMPU6050 myMPU6050_1;
        MyMPU6050 myMPU6050_2;
        
        void updateIMUS(){
            getActiveIMU()->loop();
        }
    
        void loop(){

            getActiveIMU()->disableInterrupt();
            updateThetas();
            
            float output[2];
//            output[1] = _lastTh2Desired;
            float tau = calcTau(output, _z, _parameters, &gains, &target, _pc);

//            float K = gains.getSwingUpK();
//            float D = gains.getSwingUpD();
//            
//            float th1 = _z[0];
//            float th2 = _z[1];
//            float dth1 = _z[2];
//            float dth2 = _z[3];
//            float tau = (K*(_manualTheta - th2) - D*dth2);
//            float tau = output[0];
//            _lastTh2Desired = output[1];
            motor.setTorque(tau);
            
            getActiveIMU()->enableInterrupt();
        }
        
        MyMPU6050* getActiveIMU(){
            if (_inverted) return &myMPU6050_2;
            return &myMPU6050_1;
        }
        
        float getTheta1(){
            return _z[0];
        }
        float getDTheta1(){
            return _z[2];
        }
        float getTheta2(){
            return _z[1];
        }
        float getDTheta2(){
            return _z[3];
        }
        
        
    
    private:
    
        Serial *_pc;
    
        float _parameters[10];
        volatile float _z[4];//theta1, theta2, dtheta2, dtheta2
        
        float _lastTh2Desired;
        float _softLimit;
                
        void updateThetas(){
            _z[0] = _getTheta1();
            _z[2] = _getDTheta1();
            _z[1] = _getTheta2();
            _z[3] = _getDTheta2();
            
        }
        float _getTheta1(){
            return getActiveIMU()->getTheta();
        }
        float _getDTheta1(){
            return getActiveIMU()->getDTheta();
        }
        float _getTheta2(){
            if (_inverted) return -motor.getTheta();
            return motor.getTheta();
        }
        float _getDTheta2(){
            if (_inverted) return -motor.getDTheta();
            return motor.getDTheta();
        }
        
        bool _inverted;
    
};

#endif