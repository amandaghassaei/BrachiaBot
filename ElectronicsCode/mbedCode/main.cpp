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
//    comm.printGains();

    controlsInterrupt.attach_us(&controls, &Controls::loop, 1000);

    while(1) {
        controls.updateIMUS();
        comm.check();
        if (serialCounter++>1000000) {
//            comm.getPC()->printf("%f\n", controls.getTheta1());
//            comm.getPC()->printf("%f", controls.motor.getPWM());
            serialCounter = 0;
//            comm.getPC()->printf("%f\n", controls.motor.getTorque());
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
void setCurrentPWrapper(Arguments * input, Reply * output){
    comm.setCurrentP(input, output);
};
RPCFunction SetCurrentP(&setCurrentPWrapper, "SetCurrentP");
void setCurrentDWrapper(Arguments * input, Reply * output){
    comm.setCurrentD(input, output);
};
RPCFunction SetCurrentD(&setCurrentDWrapper, "SetCurrentD");
void setTargetWrapper(Arguments * input, Reply * output){
    comm.setTarget(input, output);
};
RPCFunction SetTarget(&setTargetWrapper, "SetTarget");
void setTorqueWrapper(Arguments * input, Reply * output){
    comm.setTorque(input, output);
};
RPCFunction SetTorque(&setTorqueWrapper, "SetTorque");
void printGainsWrapper(Arguments * input, Reply * output){
    comm.printGains();
};
RPCFunction PrintGains(&printGainsWrapper, "PrintGains");
void printPositionWrapper(Arguments * input, Reply * output){
    comm.printPosition();
};
RPCFunction PrintPosition(&printPositionWrapper, "PrintPosition");






