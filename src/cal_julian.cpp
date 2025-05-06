/* converted from */
/*
       JavaScript functions for the Fourmilab Calendar Converter

                  by John Walker  --  September, MIM
              http://www.fourmilab.ch/documents/calendar/

                This program is in the public domain.
*/

#include "calendar.h"
#include <cmath>
#include <array>
#include "astro.h"
#include <string>

//
// Julian
//
const char* julian_weekday_name(int day) {
    static const char* names[] = {
        WEEKDAY_MONDAY, WEEKDAY_TUESDAY, WEEKDAY_WEDNESDAY, WEEKDAY_THURSDAY, WEEKDAY_FRIDAY, WEEKDAY_SATURDAY, WEEKDAY_SUNDAY
    };
    return names[day % 7 -1];
};

const char* julian_month_name(int month) {
    static const char* names[] = {
        MONTH_JAN, MONTH_FEB, MONTH_MAR, MONTH_APR, MONTH_MAY, MONTH_JUN,
        MONTH_JUL, MONTH_AUG, MONTH_SEP, MONTH_OCT, MONTH_NOV, MONTH_DEC
    };
    if (month < 1 || month > 12) return "Invalid";
    return names[month - 1];
}

bool leap_julian(int year) {
    return astro::mod(year, 4) == ((year > 0) ? 0 : 3);
}

int julian_jd_to_weekday(double jd) {
    return static_cast<int>(std::fmod(std::floor(jd + 1.5), 7.0));
}

double julian_to_jd(int year, int month, int day) {
    if (year < 1) {
        year++;
    }
    if (month <= 2) {
        year--;
        month += 12;
    }

    return std::floor(365.25 * (year + 4716)) +
           std::floor(30.6001 * (month + 1)) +
           day - 1524.5;
}

std::array<int, 3> jd_to_julian(double jd) {
    int z, a, b, c, d, e, year, month, day;

    jd += 0.5;
    z = static_cast<int>(std::floor(jd));
    a = z;
    b = a + 1524;
    c = static_cast<int>(std::floor((b - 122.1) / 365.25));
    d = static_cast<int>(std::floor(365.25 * c));
    e = static_cast<int>(std::floor((b - d) / 30.6001));

    month = (e < 14) ? (e - 1) : (e - 13);
    year = (month > 2) ? (c - 4716) : (c - 4715);
    day = static_cast<int>(b - d - std::floor(30.6001 * e));

    if (year < 1) {
        year--;
    }

    return {year, month, day};
}

std::string format_julian_date(double jd) {
    auto date = jd_to_julian(jd);
    return "Julian: " + std::to_string(date[2]) + "/" +
           std::to_string(date[1]) + "/" +
           std::to_string(date[0]);
}

std::string format_julian_date_weekday(double jd) {
    auto julian = jd_to_julian(jd);
    int weekday = calendar::iso_day_of_week(jd);  // ISO: Mon=1, Sun=7

    const char* weekday_name = julian_weekday_name(julian_jd_to_weekday(jd));

    char buffer[20];
    snprintf(buffer, sizeof(buffer), "%s", weekday_name);
    return std::string(buffer);
}

std::string format_julian_date_day(double jd) {
    auto date = jd_to_julian(jd);
    return std::to_string(date[2]);
}
 
std::string format_julian_date_month(double jd) {
    auto date = jd_to_julian(jd);
    int month = date[1];
    const char* month_str = julian_month_name(month);
    char buffer[20];
    snprintf(buffer, sizeof(buffer), "%s", month_str);
    return std::string(buffer);
}

std::string format_julian_date_year(double jd) {
    auto date = jd_to_julian(jd);
    return std::to_string(date[0]) + " AD";
}
