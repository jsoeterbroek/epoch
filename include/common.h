#include <Arduino.h>

// status flags
bool STATUS_WIFI_OK = false;
bool STATUS_WIFI_MGR_OK = false;
bool STATUS_WIFI_MGR_CONFIG_MODE_OK = false;
bool STATUS_TIME_OK = false;
bool STATUS_NTP_OK = false;


const char* ntpServer = "europe.pool.ntp.org";
#define NTP_TIMEZONE  "UTC+1"
String timezone = "CET-1CEST,M3.5.0,M10.5.0/3";

// WiFi
const char* wifi_mngr_networkname = "m5paper";
const char* wifi_mngr_password = "password";

//time variables
String h, m, s;
int day, month, year, sol;
int8_t hour = 0;
int8_t minute = 0;
int8_t second = 0;