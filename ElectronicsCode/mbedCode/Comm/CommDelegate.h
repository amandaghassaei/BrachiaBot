#ifndef CommDelegate_h
#define CommDelegate_h

class CommDelegate//parent class
{
    public:
    
      CommDelegate(){}//constructor method
      
        //thetas
        float virtual getTheta1(){return 0.0;}
        float virtual getDTheta1(){return 0.0;}
        float virtual getTheta2(){return 0.0;}
        float virtual getDTheta2(){return 0.0;}
      
        //gains
        void virtual setSwingUpK(float k){};
        void virtual setSwingUpD(float d){};
        void virtual setDesiredThetaP(float p){};
        void virtual setSoftLimitsP(float p){};
        void virtual setTargetingK(float k){};
        void virtual setTargetingD(float d){};
        float virtual getSwingUpK(){return 0;};
        float virtual getSwingUpD(){return 0;};
        float virtual getDesiredThetaP(){return 0;};
        float virtual getSoftLimitsP(){return 0;};
        float virtual getTargetingK(){return 0;};
        float virtual getTargetingD(){return 0;};
        
        //target
        void virtual setTargetPosition(int position){};
        int virtual getTargetPosition(){return 0;};
        
        //motor
        void virtual setTheta(float theta){};
      
    protected:
    
        
         
};

#endif