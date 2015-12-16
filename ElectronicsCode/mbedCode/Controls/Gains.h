#ifndef Gains_h
#define Gains_h

#include "mbed.h"

class Gains {
    
    public:
    
        Gains(){
            setSwingUpK(30);
            setSwingUpD(4);
            setDesiredThetaP(0.3);
            setSoftLimitsP(0.3);
            setTargetingK(15);
            setTargetingD(2);
        }
        
        void setPC(Serial *pc){
            _pc = pc;
        }
        
        void setSwingUpK(float k){
            _swingUpK = k;
        };
        void setSwingUpD(float d){
            _swingUpD = d;
        };
        void setDesiredThetaP(float p){
            _desiredThetaP = p;
        };
        void setSoftLimitsP(float p){
            _softLimitsP = p;
        };
        void setTargetingK(float k){
            _targetingK = k;
        };
        void setTargetingD(float d){
            _targetingD = d;
        };
        
        float getSwingUpK(){
            return _swingUpK;
        };
        float getSwingUpD(){
            return _swingUpD;
        };
        float getDesiredThetaP(){
            return _desiredThetaP;
        };
        float getSoftLimitsP(){
            return _softLimitsP;
        };
        float getTargetingK(){
            return _targetingK;
        };
        float getTargetingD(){
            return _targetingD;
        };
    
    private:
    
        Serial *_pc;
    
        float _swingUpK;
        float _swingUpD;
        float _desiredThetaP;
        float _softLimitsP;
        float _targetingK;
        float _targetingD;
    
};

#endif
