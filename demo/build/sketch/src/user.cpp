#line 1 "/home/kafcoppelia/WORK/BOARDS/M5StickC+/demo/src/user.cpp"
#include <M5StickCPlus.h>
#include "../include/user.h"

Sandglass sandglass;
Countdown_TypeDef CountdownStruct = {.mins = 0, .secs = 0};

static void Lcd_Setup(void);
static void Key_Handle(void);

void User_Setup(void) {
    pinMode(M5_LED, OUTPUT);
    ledarray_init();
    Lcd_Setup();
}

void User_Loop(void) {
    Key_Handle();

    while (1) {
        sandglass.update();
        if (sandglass.is_Activated() == false) {
            break;
        }
    }
    led_heartbeat();
    delay(1000);
}

static void Key_Handle(void) {
    while (1) {
        M5.update();
        if (sandglass.is_Activated() == false) {
            if (M5.BtnA.wasReleasefor(800)) {
                sandglass.start(&CountdownStruct);
                break;
            }
            else if (M5.BtnA.wasReleased()) {
                CountdownStruct.mins += 1;
            }
            else if (M5.BtnB.wasReleased()) {
                CountdownStruct.secs += 1;
            }
            else if (M5.BtnB.wasReleasefor(800)) {
                CountdownStruct.secs += 10;
            }
        }
        else {
            if (M5.BtnA.wasReleasefor(800)) {
                M5.Lcd.setCursor(30, 10);
                M5.Lcd.println("Here");
                sandglass.stop();
                break; // ?
            }
        }
        sandglass.Show_Countdown(&CountdownStruct);
        // If idle, can go into low-cost mode
        delay(50);
    }
}

void led_heartbeat(void) {
    digitalWrite(M5_LED, 1 - digitalRead(M5_LED));
}

static void Lcd_Setup(void) {
    M5.Lcd.setRotation(1);
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor(80, 80);
    M5.Lcd.print("Hello World\n");
    delay(500);
    M5.Lcd.fillScreen(BLACK);
}