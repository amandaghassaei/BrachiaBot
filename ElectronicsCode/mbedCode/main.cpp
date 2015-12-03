#include "mbed.h"
#include "mbed_rpc.h" 
#include "Comm.h"
#include "Controls.h"

Controls controls;
Comm comm(&(controls.gains), &(controls.target));

int main() {
    
    while(1) {
        controls.loop();
        comm.check();
        comm.printPosition(&controls);
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
void setGains(Arguments * input, Reply * output){
    comm.setGains(input, output);
};
RPCFunction SetGains(&setGains, "SetGains");
void setTarget(Arguments * input, Reply * output){
    comm.setTarget(input, output);
};
RPCFunction SetTarget(&setTarget, "SetTarget");





* input, Reply * output){
    comm.setTarget(input, output);
};
RPCFunction SetTarget(&setTarget, "SetTarget");





