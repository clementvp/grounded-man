#include "M5StickCPlus2.h"

void setup() {
    auto cfg = M5.config();
    StickCP2.begin(cfg);
    StickCP2.Display.setRotation(1);
}

bool flashed = false;


void flashScreenAndBeep(void){
        delay(500);
        StickCP2.Display.fillCircle(StickCP2.Display.width() / 2, StickCP2.Display.height() /2 , 50, RED);
        delay(500);
        StickCP2.Display.clear();
}

void loop(void) {
    auto imu_update = StickCP2.Imu.update();
    if (imu_update) {
        auto data = StickCP2.Imu.getImuData();
       
        if(abs(data.accel.y) < 0.60){
            if(!flashed){
                Serial.printf("flashed passe a true\n");
                flashed = true;
            }
        }else{
            Serial.printf("flashed passe a false\n");
            flashed = false;
        }

        if(flashed){
            flashScreenAndBeep();
        }
    }
    delay(100);
}