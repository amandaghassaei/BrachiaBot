#ifndef Comm_h
#define Comm_h

#include "json.h"
#include "CommDelegate.h"  
#include "mbed_rpc.h" 


class Comm{
    
    public:
    
        Comm(CommDelegate *gains, CommDelegate *target);
        
        void openGripper1(Arguments* input, Reply* output);
        void closeGripper1(Arguments* input, Reply* output);
        void printGripper1State(bool state);
        void openGripper2(Arguments* input, Reply* output);
        void closeGripper2(Arguments* input, Reply* output);
        void printGripper2State(bool state);
        
        void setGains(Arguments* input, Reply* output);
        void printGains();
        
        void setTarget(Arguments* input, Reply* output);
        void printTarget();
        
        void printPosition(CommDelegate *controls);
        
        void check();
        
        Serial _pc;
            
    private:
    
        void throwNotEnoughArgsError();
        
        char buf[256], outbuf[256];
        
        JSON _json;
        CommDelegate *_gains;
        CommDelegate *_target;
//        volatile bool newline_detected = false;
 
};

#endif