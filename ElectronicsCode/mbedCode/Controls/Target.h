#ifndef Target_h
#define Target_h

class Target{

    public:
    
        Target(){
            setPosition(6);
        }
    
        void setPosition(int position){
            _position = position;
        }
    
        int getPosition(){
            return _position;
        }
    
    
    private:
    
        int _position;
    
};

#endif