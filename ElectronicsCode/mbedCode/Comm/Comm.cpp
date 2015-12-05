#include "Comm.h"

    
Comm::Comm(CommDelegate *controls):_pc(USBTX, USBRX), _json(&_pc)
{
    _pc.baud(9600);
    _controls = controls;
}

void Comm::openGripper1(Arguments* input, Reply* output){
    printGripper1State(true);
}

void Comm::closeGripper1(Arguments* input, Reply* output){
    printGripper1State(false);
}

void Comm::printGripper1State(bool state){
    _json.open();
    if (state) _json.print("gripper1", "true");
    else _json.print("gripper1", "false");
    _json.close();
}

void Comm::openGripper2(Arguments* input, Reply* output){
    printGripper2State(true);
}

void Comm::closeGripper2(Arguments* input, Reply* output){
    printGripper2State(false);
}

void Comm::printGripper2State(bool state){
    _json.open();
    if (state) _json.print("gripper2", "true");
    else _json.print("gripper2", "false");
    _json.close();
}

void Comm::setSwingUpK(Arguments* input, Reply* output){
    if (input->argc < 1){
        throwNotEnoughArgsError();
        return;
    }
    float k = input->getArg<float>(); 
    _controls->setSwingUpK(k);
    printGains();
}

void Comm::setSwingUpD(Arguments* input, Reply* output){
    if (input->argc < 1){
        throwNotEnoughArgsError();
        return;
    }
    float d = input->getArg<float>(); 
    _controls->setSwingUpD(d);
    printGains();
}
void Comm::setCurrentP(Arguments* input, Reply* output){
    if (input->argc < 1){
        throwNotEnoughArgsError();
        return;
    }
    float p = input->getArg<float>(); 
    _controls->setCurrentP(p);
    printGains();
}

void Comm::setCurrentD(Arguments* input, Reply* output){
    if (input->argc < 1){
        throwNotEnoughArgsError();
        return;
    }
    float d = input->getArg<float>(); 
    _controls->setCurrentD(d);
    printGains();
}



void Comm::printGains(){
    _json.open();
    _json.print("swingUpK", _controls->getSwingUpK());
    _json.sepItem();
    _json.print("swingUpD", _controls->getSwingUpD());
    _json.sepItem();
    _json.print("currentP", _controls->getCurrentP());
    _json.sepItem();
    _json.print("currentD", _controls->getCurrentD());
    _json.close();
}

void Comm::setTarget(Arguments* input, Reply* output){
    if (input->argc < 1){
        throwNotEnoughArgsError();
        return;
    }
    int targetPosition = input->getArg<int>(); 
    _controls->setTargetPosition(targetPosition);
    printTarget();
}

void Comm::printTarget(){
    _json.open();
    _json.print("target", _controls->getTargetPosition());
    _json.close();
}

void Comm::setTorque(Arguments * input, Reply * output){
    if (input->argc < 1){
        throwNotEnoughArgsError();
        return;
    }
    float torque = input->getArg<float>(); 
    _pc.printf("%f\n", torque);
    _controls->setTorque(torque);
}

void Comm::printPosition(){
    _json.open();
    _json.print("th1", _controls->getTheta1());
    _json.sepItem();
//    _json.print("dth1", controls->getDTheta1());
//    _json.sepItem();
    _json.print("th2", _controls->getTheta2());
//    _json.sepItem();
//    _json.print("dth2", _controls->getDTheta2());
    _json.close();
}

void Comm::check(){
    if(!_pc.readable()) return;
    _pc.gets(buf, 256);
    //Call the static call method on the RPC class
    RPC::call(buf, outbuf); 
//    _pc.printf("%s\n", outbuf);
}

Serial* Comm::getPC(){
    return &_pc;
}

void Comm::throwNotEnoughArgsError(){
    _json.open();
    _json.print("error", "not enough input arguments");
    _json.close();
}
