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
            
            float m1 = 0.55;
            float m2 = m1;
            float l1 = 0.30;//length of links
            float l2 = l1;
            float I1 = 1/3.0*m1*l1*l1;//model as rod rotating around one end
            float I2 = 1/3.0*m2*l2*l2;
            float c1 = 0.5*l1;//location of center of mass along link
            float c2 = 0.5*l2;
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
            
            _lastTorque = motor.getTorque();
            _manualTau = 0;
        }
        
        void setInverted(bool inverted){
            _inverted = inverted;
            if (!_inverted) {
                myMPU6050_2.disable();
                myMPU6050_1.enable();
            } else {
                myMPU6050_1.disable();
                myMPU6050_2.enable();
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
        void setCurrentP(float p){
            gains.setCurrentP(p);
        };
        void setCurrentD(float d){
            gains.setCurrentD(d);
        };
        float getSwingUpK(){
            return gains.getSwingUpK();
        };
        float getSwingUpD(){
            return gains.getSwingUpD();
        };
        float getCurrentP(){
            return gains.getCurrentP();
        };
        float getCurrentD(){
            return gains.getCurrentD();
        };
        
        Target target;
        void setTargetPosition(int position){
            target.setPosition(position);
        };
        int getTargetPosition(){
            return target.getPosition();
        };
        
        Motor motor;
        void setTorque(float torque){
            _manualTau = torque;
        };
        
        float _manualTau;
    
        //imu
        MyMPU6050 myMPU6050_1;
        MyMPU6050 myMPU6050_2;
        
        void updateIMUS(){
            getActiveIMU()->loop();
        }
    
        void loop(){

//            getActiveIMU().disableInterrupt();
            
            updateThetas();
            
            float tau = calcTau(_z, _parameters, &gains, _pc);
//            float tau = getTheta1();
            
            motor.setTorque(tau);
            
//            getActiveIMU().enableInterrupt();
        }
        
        MyMPU6050* getActiveIMU(){
            if (_inverted) return &myMPU6050_2;
            return &myMPU6050_1;
        }
        
        float pdTorque(float desiredTorque, float deltaT){
            float torque = motor.getTorque();
            float newTorque = gains.getCurrentP()*(desiredTorque-torque) + gains.getCurrentD()*(torque-_lastTorque)/deltaT;
            _lastTorque = torque;//update _lastTorque
            return newTorque;
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
        
        float _lastTorque;
        
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