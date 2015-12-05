#ifndef Target_h
#define Target_h


class Target{

    public:
    
        Target(){
            setPosition(6);
        }
        
        void setPC(Serial *pc){
            _pc = pc;
        }
    
        void setPosition(int position){
            _position = position;
        }
    
        int getPosition(){
            return _position;
        }
    
    
    private:
    
        Serial *_pc;
    
        int _position;
    
};

#endif