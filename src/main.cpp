#include "M5StickCPlus2.h"

void setup() {
    auto cfg = M5.config();
    StickCP2.begin(cfg);
    StickCP2.Display.setRotation(1);
}


void flashScreenAndBeep(void){
    StickCP2.Display.fillCircle(StickCP2.Display.width() / 2, StickCP2.Display.height() /2 , 50, RED);
    StickCP2.Speaker.tone(4000, 500);
    delay(500);
    StickCP2.Display.clear();
    StickCP2.Speaker.tone(10000, 500);
    delay(500);
}

void loop(void) {
    auto imu_update = StickCP2.Imu.update();
    if (imu_update) {
        auto data = StickCP2.Imu.getImuData();
        Serial.printf("ax:%f  ay:%f  az:%f\r\n", data.accel.x, data.accel.y, data.accel.z);
        if(abs(data.accel.y) < 0.60){
            flashScreenAndBeep();
        }
        
    }
}