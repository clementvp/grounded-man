#include "M5StickCPlus2.h"

void setup()
{
    auto cfg = M5.config();
    StickCP2.begin(cfg);
}

void flashScreenAndBeep()
{
    StickCP2.Display.fillCircle(StickCP2.Display.width() / 2, StickCP2.Display.height() / 2, 50, RED);
    delay(600);
    StickCP2.Display.clear();
    delay(600);
}

void loop()
{
    static unsigned long previousTime = 0;
    static bool manDown = false;
    static bool alarm = false;

    unsigned long currentTime = millis();
    if (StickCP2.Imu.update())
    {
        auto data = StickCP2.Imu.getImuData();
        manDown = abs(data.accel.y) < 0.60;
    }

    if (manDown)
    {
        if (!alarm && (currentTime - previousTime >= 5000))
        {
            alarm = true;
        }
    }
    else
    {
        alarm = false;
        previousTime = currentTime;
    }

    if (alarm)
    {
        flashScreenAndBeep();
    }

    delay(100);
}