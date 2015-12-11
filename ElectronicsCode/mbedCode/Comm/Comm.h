#ifndef Comm_h
#define Comm_h

#include "json.h"
#include "CommDelegate.h"  
#include "mbed_rpc.h" 


class Comm{
    
    public:
    
        Comm(CommDelegate *controls);
        
        void openGripper1(Arguments* input, Reply* output);
        void closeGripper1(Arguments* input, Reply* output);
        void printGripper1State(bool state);
        void openGripper2(Arguments* input, Reply* output);
        void closeGripper2(Arguments* input, Reply* output);
        void printGripper2State(bool state);
        
        void setSwingUpK(Arguments* input, Reply* output);
        void setSwingUpD(Arguments* input, Reply* output);
        void setDesiredThetaP(Arguments* input, Reply* output);
        void setSoftLimitsP(Arguments* input, Reply* output);
        void printGains();
        
        void setTargetingK(Arguments* input, Reply* output);
        void setTargetingD(Arguments* input, Reply* output);
        
        void setTarget(Arguments* input, Reply* output);
        void printTarget();
        
        void setTheta(Arguments * input, Reply * output);
        
        void printPosition();
        void printVelocity();
        
        void check();
        
        Serial* getPC();
            
    private:
    
        Serial _pc;
    
        void throwNotEnoughArgsError();
        
        char buf[256], outbuf[256];
        
        JSON _json;
        CommDelegate *_controls;
//        volatile bool newline_detected = false;
 
};

#endif