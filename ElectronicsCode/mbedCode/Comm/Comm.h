#ifndef Comm_h
#define Comm_h

//#include "mbed.h"
#include "json.h"
#include "Target.h"
#include "CommDelegate.h"   
//#include "MODSERIAL.h"


class Comm{
    
    public:
    
        Comm(CommDelegate *gains, CommDelegate *target, CommDelegate *myMPU6050_1);
        
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
        CommDelegate *_gains;
        CommDelegate *_target;
        CommDelegate *_myMPU6050_1;
//        volatile bool newline_detected = false;
 
};

#endif