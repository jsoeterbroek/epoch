#include <Arduino.h>
#include <astro.h>
#include <calendar.h>
#include <WiFiManager.h>
#include <TFT_eSPI.h>
#include "M5CoreS3.h"

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite sprite = TFT_eSprite(&tft);

// WiFi Manager
WiFiManager wm;

struct tm timeinfo;

void configModeCallback(WiFiManager *myWiFiManager) {

    CoreS3.Display.drawString("******************", 4, 28);
    CoreS3.Display.drawString("Webportal started: ", 4, 40);
    CoreS3.Display.drawString(WiFi.softAPIP().toString(), 4, 52);
    CoreS3.Display.drawString("SSID: ", 4, 64);
    CoreS3.Display.drawString(myWiFiManager->getConfigPortalSSID(), 4, 76);
    CoreS3.Display.drawString("******************", 4, 112);

}



void setup() {
    Serial.begin(115200);
    auto cfg = M5.config();
    CoreS3.begin(cfg);
}

void loop() {
}
