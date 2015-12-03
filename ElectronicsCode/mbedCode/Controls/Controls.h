#ifndef Controls_h
#define Controls_h

#include <math.h>
#include "Gains.h"
#include "Target.h"
#include "MyMPU6050.h" 
#include "Motor.h"  
#include "Dynamics.h"

class Controls: public CommDelegate{
    
    public:
    
        Controls():myMPU6050_1(p9, p10, p11), myMPU6050_2(p28, p27, p18){//I2C_SDA, I2C_SCL, int_pin
        
            _inverted = false;
            
            float m1 = 0.55;
            float m2 = m1;
            float l1 = 0.30;//length of links
            float l2 = l1;
            float I1 = 1/3*m1*pow(l1,2);//model as rod rotating around one end
            float I2 = 1/3*m2*pow(l2,2);
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
            
        }
    
        Gains gains;
        Target target;
        
        Motor motor;
    
        //imu
        MyMPU6050 myMPU6050_1;
        MyMPU6050 myMPU6050_2;
    
        void loop(){
            if (_inverted) myMPU6050_2.loop();
            else myMPU6050_1.loop();
            updateThetas();
            
            float tau = calcTau(_z, _parameters);
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
    
        float _parameters[10];
    
        float _z[4];//theta1, theta2, dtheta2, dtheta2
        
        void updateThetas(){
            _z[0] = _getTheta1();
            _z[2] = _getDTheta1();
            _z[1] = _getTheta2();
            _z[3] = _getDTheta2();
            
        }
        float _getTheta1(){
            if (_inverted) return myMPU6050_2.getTheta();
            return myMPU6050_1.getTheta();
        }
        float _getDTheta1(){
            if (_inverted) return myMPU6050_2.getDTheta();
            return myMPU6050_1.getDTheta();
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