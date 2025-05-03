#include <colors.h>

#define PD_VERSION_MAJOR 1
#define PD_VERSION_MINOR 3
#define PD_VERSION_PATCH 1

static inline int pd_version_major(void) {
    return PD_VERSION_MAJOR;
}
static inline int pd_version_minor(void) {
    return PD_VERSION_MINOR;
}
static inline int pd_version_patch(void) {
    return PD_VERSION_PATCH;
}

// status flags
boolean STATUS_WIFI_OK = false;
boolean STATUS_WIFI_MGR_OK = false;
boolean STATUS_WIFI_MGR_CONFIG_MODE_OK = false;
boolean STATUS_TIME_OK = false;
boolean STATUS_NTP_OK = false;
boolean STATUS_CONFIG_DATA_OK = false;
boolean STATUS_BLE_OK = false;
boolean STATUS_GET_CONFIG_DATA_SPIFF_OK = false;
boolean STATUS_SET_CONFIG_DATA_SPIFF_OK = false;
boolean STATUS_GET_CONFIG_DATA_HTTP_OK = false;

boolean GET_CONFIG_DATA_HTTP = false;
boolean GET_CONFIG_DATA_SPIFF = true;

const char* ntpServer = "europe.pool.ntp.org";
#define NTP_TIMEZONE  "UTC+1"
String timezone = "CET-1CEST,M3.5.0,M10.5.0/3";

// WiFi
const char* wifi_mngr_networkname = "pictostick";
const char* wifi_mngr_password = "password";

#define MY_WIDTH  TFT_HEIGHT
#define MY_HEIGHT TFT_WIDTH

//time variables
String h, m, s;
int day, month, year, sol;
int8_t hour = 0;
int8_t minute = 0;
int8_t second = 0;

//b,,,,,,
int vol;
int volE;

//sleep variables
int sleepTime = 50;
int ts, tts = 0;
bool slp = false;

#define BUTTON_PRESSED LOW
#define BUTTON_RELEASED HIGH

int cursor = 0;