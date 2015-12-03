#ifndef Comm_h
#define Comm_h

//#include "mbed.h"
#include "json.h"
#include "Gains.h"
#include "Target.h"
#include "Delegate.h"   
//#include "MODSERIAL.h"


class Comm{
    
    public:
    
        Comm(Gains *gains, Target *target, Delegate *myMPU6050_1);
        
        void openGripper1();
        void closeGripper1();
        void printGripper1State(bool state);
        void openGripper2();
        void closeGripper2();
        void printGripper2State(bool state);
        
        void setGains(float k1, float d1, float k2, float d2);
        void printGains();
        
        void setTarget(int targetPosition);
        void printTarget();
        
        void printPosition();
        
//        void check();
        
            
    private:
    
        Serial _pc;
        JSON _json;
        Gains *_gains;
        Target *_target;
        Delegate *_myMPU6050_1;
//        volatile bool newline_detected = false;
 
};

#endif