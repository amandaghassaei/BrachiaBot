#include "mbed.h"
#include "mbed_rpc.h" 
#include "Comm.h"
#include "Controls.h"

Controls controls;
Comm comm(&controls);

long serialCounter = 0;


Ticker controlsInterrupt;


int main() {
    controls.setPC(comm.getPC());
    controls.setup();
//    comm.printPosition();
    comm.printGains();

    controlsInterrupt.attach_us(&controls, &Controls::loop, 1000);

    while(1) {
        controls.updateIMUS();
        comm.check();
        
        
        if (serialCounter++>100) {
//            comm.printPosition();
//            comm.getPC()->printf("%f\n", controls.getTheta1());
//            comm.getPC()->printf("%f", controls.motor.getPWM());
            serialCounter = 0;
           // float z[4] = {1,2,0,0};
//            comm.getPC()->printf("%f\n",controls.target.getTheta2ForTarget(z));
        }
    }
}





//wrappers for comm stack
void openGripper1Wrapper(Arguments * input, Reply * output){
    comm.openGripper1(input, output);
};
RPCFunction OpenGripper1(&openGripper1Wrapper, "OpenGripper1");
void closeGripper1Wrapper(Arguments * input, Reply * output){
    comm.closeGripper1(input, output);
};
RPCFunction CloseGripper1(&closeGripper1Wrapper, "CloseGripper1");


void openGripper2Wrapper(Arguments * input, Reply * output){
    comm.openGripper2(input, output);
};
RPCFunction OpenGripper2(&openGripper2Wrapper, "OpenGripper2");
void closeGripper2Wrapper(Arguments * input, Reply * output){
    comm.closeGripper2(input, output);
};
RPCFunction CloseGripper2(&closeGripper2Wrapper, "CloseGripper2");


void setSwingUpKWrapper(Arguments * input, Reply * output){
    comm.setSwingUpK(input, output);
};
RPCFunction SetSwingUpK(&setSwingUpKWrapper, "SetSwingUpK");
void setSwingUpDWrapper(Arguments * input, Reply * output){
    comm.setSwingUpD(input, output);
};
RPCFunction SetSwingUpD(&setSwingUpDWrapper, "SetSwingUpD");


void setDesiredThetaPWrapper(Arguments * input, Reply * output){
    comm.setDesiredThetaP(input, output);
};
RPCFunction SetDesiredThetaP(&setDesiredThetaPWrapper, "SetDesiredThetaP");
void setSoftLimitsPWrapper(Arguments * input, Reply * output){
    comm.setSoftLimitsP(input, output);
};
RPCFunction SetSoftLimitsP(&setSoftLimitsPWrapper, "SetSoftLimitsP");


void setTargetWrapper(Arguments * input, Reply * output){
    comm.setTarget(input, output);
};
RPCFunction SetTarget(&setTargetWrapper, "SetTarget");

void setTargetingKWrapper(Arguments * input, Reply * output){
    comm.setTargetingK(input, output);
};
RPCFunction SetTargetingK(&setTargetingKWrapper, "SetTargetingK");
void setTargetingDWrapper(Arguments * input, Reply * output){
    comm.setTargetingD(input, output);
};
RPCFunction SetTargetingD(&setTargetingDWrapper, "SetTargetingD");




void setThetaWrapper(Arguments * input, Reply * output){
    comm.setTheta(input, output);
};
RPCFunction SetTheta(&setThetaWrapper, "SetTheta");


void printGainsWrapper(Arguments * input, Reply * output){
    comm.printGains();
};
RPCFunction PrintGains(&printGainsWrapper, "PrintGains");
void printPositionWrapper(Arguments * input, Reply * output){
    comm.printPosition();
};
RPCFunction PrintPosition(&printPositionWrapper, "PrintPosition");






