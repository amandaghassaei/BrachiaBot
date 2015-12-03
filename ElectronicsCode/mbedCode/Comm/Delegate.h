#ifndef Delegate_h
#define Delegate_h

class Delegate//parent class
{
    public:
    
      Delegate(){}//constructor method
      
      //imu
      float virtual getTheta(){return 0.0;}
      float virtual getDtheta(){return 0.0;}
      
    protected:
         
};

#endif