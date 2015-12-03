#include "Comm.h"

    
Comm::Comm(Gains *gains, Target *target, Delegate *myMPU6050_1):_pc(USBTX, USBRX), _json(&_pc)
{
    _pc.baud(115200);
    _gains = gains;
    _target = target;
    _myMPU6050_1 = myMPU6050_1;
}

void Comm::openGripper1(){
    printGripper1State(true);
}

void Comm::closeGripper1(){
    printGripper1State(false);
}

void Comm::printGripper1State(bool state){
    _json.open();
    if (state) _json.print("gripper1", "true");
    else _json.print("gripper1", "false");
    _json.close();
}

void Comm::openGripper2(){
    printGripper2State(true);
}

void Comm::closeGripper2(){
    printGripper2State(false);
}

void Comm::printGripper2State(bool state){
    _json.open();
    if (state) _json.print("gripper2", "true");
    else _json.print("gripper2", "false");
    _json.close();
}

void Comm::setGains(float k1, float d1, float k2, float d2){
    _gains->setGains(k1, d1, k2, d2);
    printGains();
}

void Comm::printGains(){
    _json.open();
    _json.print("k1", _gains->getK1());
    _json.sepItem();
    _json.print("d1", _gains->getD1());
    _json.sepItem();
    _json.print("k2", _gains->getK2());
    _json.sepItem();
    _json.print("d2", _gains->getD1());
    _json.close();
}

void Comm::setTarget(int targetPosition){
    _target->setPosition(targetPosition);
    printTarget();
}

void Comm::printTarget(){
    _json.open();
    _json.print("target", _target->getPosition());
    _json.close();
}

void Comm::printPosition(){
    _json.open();
    _json.print("th1", _myMPU6050_1->getTheta());
    _json.sepItem();
    _json.print("dth1", _myMPU6050_1->getDtheta());
    _json.close();
}

//void Comm::check(){
//    if (newline_detected){
//        printTarget();
//    }
//}
//
//void rxCallback(MODSERIAL_IRQ_INFO *q) {
//    MODSERIAL *serial = q->serial;
//    if ( serial->rxGetLastChar() == '\n') {
//        newline_detected = true;
//    }
//}
