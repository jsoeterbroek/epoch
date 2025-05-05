// datetime.h
#ifndef DATETIME_H
#define DATETIME_H
#include <Arduino.h>


typedef struct RTC_Time;
typedef struct RTC_Date;

void initTime(String timezone);
void setTimezone(String timezone);

#endif