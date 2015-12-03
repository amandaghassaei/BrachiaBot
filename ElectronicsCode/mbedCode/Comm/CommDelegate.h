#ifndef CommDelegate_h
#define CommDelegate_h

class CommDelegate//parent class
{
    public:
    
      CommDelegate(){}//constructor method
      
        //imu
        float virtual getTheta(){return 0.0;}
        float virtual getDtheta(){return 0.0;}
      
        //gains
        void virtual setGains(float k1, float d1, float k2, float d2){};
        void virtual setK1(float k1){};
        void virtual setD1(float d1){};
        void virtual setK2(float k2){};
        void virtual setD2(float d2){};
        float virtual getK1(){return 0;};
        float virtual getD1(){return 0;};
        float virtual getK2(){return 0;};
        float virtual getD2(){return 0;};
        int virtual numGains(){return 0;};
        
        //target
        void virtual setPosition(int position){};
        int virtual getPosition(){return 0;};
      
    protected:
         
};

#endif