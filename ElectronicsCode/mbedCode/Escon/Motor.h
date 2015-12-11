#ifndef Motor_h
#define Motor_h

#include "mbed.h"
//#include "qeihw.h"
#include "qeihw.h"
#define ENCODER_RES 1024
#define M_PI 3.14159265358979323846
#define Kt 0.0534// [ Nm/A ]

#define PWM_MAX 0.4
#define PPR 1024


class Motor {
    
    public:
    
        Motor(): motorEN(p25), motorPWM(p26), motorCurrent(p20), encoder(QEI_DIRINV_NONE, QEI_SIGNALMODE_QUAD, QEI_CAPMODE_4X, QEI_INVINX_NONE)
        {
            _gearRatio = 9.629;
            _maxCurrent = 15.0;
            _pwmSlope = -(0.9 - 0.1) / (_maxCurrent + _maxCurrent);   // slope for desired current to PWM
            
            motorPWM.period_us(200);     // set motor PWM 5kHz (this is max val)
            motorEN.write(0);            // turn off motor driver (high active)
            motorPWM.write(0.5f);        // zero current to motor, coasting mode
            encoder.Reset(QEI_RESET_POS);             // clear the encoder
            setupEncoder();
            motorEnable();
        };
        
        void setGearRatio(float gearRatio){
            _gearRatio = gearRatio;
        }
        
        void setupEncoder()
        {   
            encoder.SetDigiFilter(480UL);
            encoder.SetMaxPosition(0xFFFFFFFF);
            encoder.SetVelocityTimerReload(1000000);
        } 
        
        void setPC(Serial *pc){
            _pc = pc;
        }
        
        float getTheta(){
            int32_t counts = encoder.GetPosition();    
            float angle = (float)counts / (4.0*PPR) * 2.0 * M_PI / _gearRatio;// - 2.583;
            return angle;
        }
        
        float getDTheta(){
            int32_t countVel = encoder.CalculateRPM( encoder.GetVelocityCap(), 4.0*PPR );
            float angularVel = countVel * 2.0 * M_PI / 60.0 / _gearRatio;
            if (encoder.Direction()) angularVel *= -1.0;
            return angularVel; 
        }
        
        void setTorque(float desTorque){
            // Desired torque should be signed. 
            // There is no direction pin on this controller, instead,
            // current is defined by a PWM % centered at 0.5, 0.1 is full reverse, 0.9 is full foward
            float desCurrent = (desTorque*1.04/_gearRatio)/Kt;//104% bump to make up for gear efficiency
            float pwm = _pwmSlope * desCurrent + 0.5f;    // corrected pwm range
           
            // check bounds on current output
            if (pwm < (0.5f-PWM_MAX)) pwm = 0.5f-PWM_MAX;
            else if (pwm > (0.5f+PWM_MAX)) pwm = 0.5f+PWM_MAX;
               
            //set motor current
            motorPWM.write(pwm);
            _pwm = pwm;
//            _pc->printf("motor PWM Command: %f\n", pwm);
        }
        
        float getTorque(){
            return Kt * motorCurrent.read()*10.0 * _gearRatio;//10 translates V to pwm max
        }
        
        float getPWM(){
            return _pwm;
        }
        
    
    
    private:
    
        Serial *_pc;
    
        float _maxCurrent;
        float _pwmSlope;
        
        float _gearRatio;
        
        float _pwm;
        
        DigitalOut motorEN;// enable motor, high is Enables
        PwmOut motorPWM;// Motor PWM output, 0.1 <-> 0.9 = -10A <-> +10A
        AnalogIn motorCurrent;// "Actual Current" from ESCON

        QEIHW encoder;
        
        
        void motorEnable(){
            motorEN.write(1);
        }
        
        void motorDisable(){
            motorEN.write(0);
        }

};

#endif