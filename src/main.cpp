#include "M5StickCPlus2.h"

void setup()
{
    auto cfg = M5.config();
    StickCP2.begin(cfg);
    StickCP2.Display.setTextColor(WHITE);
    StickCP2.Display.setCursor(39, 109);
    StickCP2.Display.setFont(&fonts::Font2);
    StickCP2.Display.setTextSize(1);
    StickCP2.Display.print("Working");
    delay(5000);
    StickCP2.Display.sleep();
}

void flashScreenAndBeep()
{
    StickCP2.Display.fillCircle(StickCP2.Display.width() / 2, StickCP2.Display.height() / 2, 50, RED);
    StickCP2.Speaker.tone(4000, 600);
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
        manDown = abs(data.accel.y) < 0.40 && abs(data.accel.x) < 0.40;
    }

    if (manDown)
    {
        if (!alarm && (currentTime - previousTime >= 10000))
        {
            StickCP2.Display.wakeup();
            alarm = true;
        }
    }
    else
    {
        if (alarm)
        {
            StickCP2.Display.sleep();
            alarm = false;
        }
        previousTime = currentTime;
    }

    if (alarm)
    {
        flashScreenAndBeep();
    }

    delay(100);
}