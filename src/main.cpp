#include <common.h>
#include "M5Unified.h"
#include <astro.h>
#include <calendar.h>
#include <WiFiManager.h>
#include <TFT_eSPI.h>
//#include "NotoSansBold15.h"
//#include "bigFont.h"
//#include "secFont.h"
//#include "smallFont.h"
#include <serialTest.h>

#include <Arduino.h>

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite sprite = TFT_eSprite(&tft);

// WiFi Manager
//WiFiManager wm;

struct tm timeinfo;

//void setTimezone(String timezone) {
//    Serial.printf("  Setting Timezone to %s\n",timezone.c_str());
//    setenv("TZ",timezone.c_str(),1);  //  Now adjust the TZ.  Clock settings are adjusted to show the new local time
//    tzset();
//}

//void initTime(String timezone) {
//    Serial.println(" ");
//    Serial.print("connecting to time server ");
//    Serial.println(" ");
//    // Init and get the time
//    configTime(0, 0, ntpServer);
//    delay(500);
//    setTimezone(timezone);
//    delay(100);
//    if(!getLocalTime(&timeinfo)){
//        Serial.println("ERROR: failed to obtain time");
//        delay(10000);
//    } else {
//        Serial.println("OK: obtained time");
//        Serial.println(&timeinfo, " %A, %B %d %Y %H:%M:%S");
//        STATUS_NTP_OK = true;
//    }
//}

// void drawTime() {
//     // time
// }


void drawMain() {

     sprite.createSprite(MY_WIDTH, MY_HEIGHT);
     sprite.fillSprite(BG_COLOR);
//     drawTime();

     sprite.unloadFont();
     tft.pushImage(0, 0, MY_WIDTH, MY_HEIGHT, (uint16_t*)sprite.getPointer());

}

void setup() {

    Serial.begin(115200);
    Serial.println("foo");
    tft.init();
    tft.setRotation(0);
    tft.fillScreen(BG_COLOR);
    // wm.setConfigPortalTimeout(5000);
    // wm.setAPCallback(configModeCallback);
    // bool res;
    // res = wm.autoConnect(wifi_mngr_networkname, wifi_mngr_password);

    // if (!res) {
    //     Serial.println("Failed to connect and hit timeout");
    //     delay(3000);
    //     ESP.restart();
    // } else {
    //     STATUS_WIFI_MGR_OK = true;
    //     Serial.println("WiFi connected.");
    // }
            
    // // set NTP time
    // initTime(timezone);

}

void loop() {
    serialTest();
    drawMain();
    delay(100);
}