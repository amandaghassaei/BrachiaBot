
#include "MyMPU6050.h"    

Serial pc(USBTX, USBRX);

int main() {
    pc.baud(115200);
    MyMPU6050 myMPU6050(p9, p10);//I2C_SDA, I2C_SCL
    while(1) {
        myMPU6050.loop();
        pc.printf("%f\n", myMPU6050.getTheta());
    }
}
