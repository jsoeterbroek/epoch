#include <Arduino.h>
#include <M5StickCPlus2.h>
#include <common.h>

#include <astro.h>
#include <calendar.h>
#include <WiFiManager.h>
#include <time.h>
#include <TFT_eSPI.h>
#include "NotoSansBold15.h"
#include "bigFont.h"
#include "secFont.h"
#include "smallFont.h"

#include "serialTest.h"

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite sprite = TFT_eSprite(&tft);

// WiFi Manager
WiFiManager wm;


struct tm timeinfo;

void setTimezone(String timezone) {
    Serial.printf("  Setting Timezone to %s\n",timezone.c_str());
    setenv("TZ",timezone.c_str(),1);  //  Now adjust the TZ.  Clock settings are adjusted to show the new local time
    tzset();
}

void initTime(String timezone) {
    Serial.println(" ");
    Serial.print("connecting to time server ");
    Serial.println(" ");
    // Init and get the time
    configTime(0, 0, ntpServer);
    delay(500);
    setTimezone(timezone);
    delay(100);
    if(!getLocalTime(&timeinfo)){
        Serial.println("ERROR: failed to obtain time");
        delay(10000);
    } else {
        Serial.println("OK: obtained time");
        Serial.println(&timeinfo, " %A, %B %d %Y %H:%M:%S");
        STATUS_NTP_OK = true;
    }
}

void drawTime() {
    // time
    struct tm timeinfo;
    static constexpr const char* const wd_en[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    auto dt = StickCP2.Rtc.getDateTime();
    // ESP32 internal timer
    auto t = time(nullptr);
    auto tm = localtime(&t);  // for local timezone.
    char timebuffer[30];
    char daybuffer[30];
    snprintf(daybuffer, sizeof(daybuffer), "%s",
        wd_en[tm->tm_wday]);
    snprintf(timebuffer, sizeof(timebuffer), "%02d:%02d",
        dt.time.hours,
        dt.time.minutes);

    sprite.loadFont(NotoSansBold15);
    sprite.fillRect(116, 40, 120, 20, RIGHT_RECT_BG_COLOR_2);
    sprite.setTextColor(RIGHT_RECT_TEXT_COLOR_2, RIGHT_RECT_BG_COLOR_2);
    sprite.drawString(daybuffer, 118, 44);
    sprite.drawString(timebuffer, 196, 44);
    sprite.unloadFont();
}


void drawMain() {

    StickCP2.Display.powerSaveOff();
    StickCP2.Display.setBrightness(32);
    sprite.createSprite(MY_WIDTH, MY_HEIGHT);
    sprite.fillSprite(BG_COLOR);
    drawTime();

    sprite.unloadFont();
    StickCP2.Display.pushImage(0, 0, MY_WIDTH, MY_HEIGHT, (uint16_t*)sprite.getPointer());

}

void configModeCallback(WiFiManager *myWiFiManager) {

    Serial.println("******************");
    Serial.println("Webportal started: ");
    Serial.println(WiFi.softAPIP().toString());
    Serial.println("SSID: ");
    Serial.println(myWiFiManager->getConfigPortalSSID());
    Serial.println("******************");

}


void setup() {

    Serial.begin(115200);
    auto cfg = M5.config();
    StickCP2.begin(cfg);
    StickCP2.Display.setRotation(3);
    StickCP2.Display.fillScreen(TFT_WHITE);
    wm.setConfigPortalTimeout(5000);
    wm.setAPCallback(configModeCallback);
    bool res;
    res = wm.autoConnect(wifi_mngr_networkname, wifi_mngr_password);

    if (!res) {
        Serial.println("Failed to connect and hit timeout");
        delay(3000);
        ESP.restart();
    } else {
        STATUS_WIFI_MGR_OK = true;
        Serial.println("WiFi connected.");
    }
            
    // set NTP time
    initTime(timezone);

    // set NTP time to rtc clock
    if (STATUS_NTP_OK) {
        Serial.println("set rtc clock from NTP");
        while (!getLocalTime(&timeinfo, 1000)) {
            Serial.print('.');
        };
        time_t t = time(nullptr) + 1;  // Advance one second.
        while (t > time(nullptr))
            ;  /// Synchronization in seconds
        StickCP2.Rtc.setDateTime(gmtime(&t));
    } else {
        Serial.println("ERROR: rtc clock not set");
    }
}

void loop() {
    StickCP2.update();
    serialTest();
    //drawMain();
    delay(100);
}
