
#include "MyMPU6050.h"    
#include "Comm.h"
#include "Gains.h"
#include "Target.h"

Gains gains;
Target target;

MyMPU6050 myMPU6050_1(p9, p10);//I2C_SDA, I2C_SCL

Comm comm(&gains, &target, &myMPU6050_1);

int main() {
    
    while(1) {
        myMPU6050_1.loop();
        comm.printTarget();
    }
}