#ifndef Gains_h
#define Gains_h

#include "mbed.h"

class Gains {
    
    public:
    
        Gains(){
            setSwingUpK(10);
            setSwingUpD(1);
            setCurrentP(10);
            setCurrentD(0);
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
        void setCurrentP(float p){
            _currentP = p;
        };
        void setCurrentD(float d){
            _currentD = d;
        };
        
        float getSwingUpK(){
            return _swingUpK;
        };
        float getSwingUpD(){
            return _swingUpD;
        };
        float getCurrentP(){
            return _currentP;
        };
        float getCurrentD(){
            return _currentD;
        };
    
    private:
    
        Serial *_pc;
    
        float _swingUpK;
        float _swingUpD;
        float _currentP;
        float _currentD;
    
};

#endif
