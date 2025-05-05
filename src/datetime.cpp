#include "config.h"
#include "datetime.h"
#include <time.h>


typedef struct RTC_Time {
    int8_t hour;
    int8_t min;
    int8_t sec;
    RTC_Time() : hour(), min(), sec() {}
    RTC_Time(int8_t h, int8_t m, int8_t s) : hour(h), min(m), sec(s) {}
} rtc_time_t;
 
typedef struct RTC_Date {
    int8_t week;
    int8_t mon;
    int8_t day;
    int16_t year;
    RTC_Date() : week(), mon(), day(), year() {}
    RTC_Date(int8_t w, int8_t m, int8_t d, int16_t y)
        : week(w), mon(m), day(d), year(y) {}
} rtc_date_t;

void setTimezone(String timezone) {
    Serial.printf("  Setting Timezone to %s\n", timezone.c_str());
    setenv("TZ", timezone.c_str(), 1);  //  Now adjust the TZ.  Clock settings are adjusted to show the new local time
    tzset();
}

void initTime(String timezone) {
    Serial.println(" ");
    Serial.print("connecting to time server ");
    Serial.println(" ");
    // Init and get the time
    configTime(0, 0, NTP_SERVER_1);
    delay(500);
    setTimezone(timezone);
}
