#ifndef Gains_h
#define Gains_h

#include "CommDelegate.h"

class Gains: public CommDelegate {
    
    public:
    
        Gains(){
            setGains(12, 4.5, 200, 3);
        }
        
        void setGains(float k1, float d1, float k2, float d2){
            setK1(k1);
            setD1(d1);
            setK2(k2);
            setD2(d2);
        };
        
        void setK1(float k1){
            _k1 = k1;
        };
        void setD1(float d1){
            _d1 = d1;
        };
        void setK2(float k2){
            _k2 = k2;
        };
        void setD2(float d2){
            _d2 = d2;
        };
        
        float getK1(){
            return _k1;
        };
        float getD1(){
            return _d1;
        };
        float getK2(){
            return _k2;
        };
        float getD2(){
            return _d2;
        };
    
    private:
    
        float _k1;
        float _d1;
        float _k2;
        float _d2;
    
};

#endif
