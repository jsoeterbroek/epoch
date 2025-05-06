#include "calendar.h"
#include <cmath>
#include <array>
#include "astro.h"
#include <string>

//
// Old High German (Julian)
//
const char* oldhighgerman_weekday_name(int day) {
    static const char* names[] = {
        "Manetag",
        "Ziestag",
        "Wuotanestag",
        "Donarestag",
        "Frijatag",
        "Sambaztag",
        "Sunnuntag"
    };
    return names[(day + 6) % 7];  // Wrap 1 (Mon) to 7 (Sun) → 0–6
}

const char* oldhighgerman_month_name(int month) {
    static const char* names[] = {
        "Wintar-manod", "Hornung", "Lenzin-manod" , "Ostar-manod", "Winni-manod", "Brah-manod",
        "Hewi-manod", "Aran-manod", "Witu-manod", "Windume-manod", "Herbist-manod", "Hailag-manod"
    };
    return names[month - 1];
}

const char* oldhighgerman_month_desc(int month) {
    static const char* desc[] = {
        "", "", "Spring Month", "Easter Month", "Pasture Month", "Fallow Month",
        "Hay Month", "Harvest month", "Wood Month", "Vintage Month", "Autumn Month", "Holy Month"
    };
    return desc[month - 1];
}

int oldhighgerman_jd_to_weekday(double jd) {
    return static_cast<int>(std::fmod(std::floor(jd + 1.5), 7.0));
}

std::string format_oldhighgerman_date_weekday(double jd) {
    auto date = jd_to_julian(jd);
    int weekday = calendar::iso_day_of_week(jd);  // ISO: Mon=1, Sun=7

    const char* weekday_name = oldhighgerman_weekday_name(oldhighgerman_jd_to_weekday(jd));

    char buffer[20];
    snprintf(buffer, sizeof(buffer), "%s", weekday_name);
    return std::string(buffer);
}

std::string format_oldhighgerman_date_day(double jd) {
    auto date = jd_to_julian(jd);
    return std::to_string(date[2]);
}

std::string format_oldhighgerman_date_month(double jd) {
    auto date = jd_to_julian(jd);
    int month = date[1];
    const char* month_str = oldhighgerman_month_name(month);
    char buffer[20];
    snprintf(buffer, sizeof(buffer), "%s", month_str);
    return std::string(buffer);
}

std::string format_oldhighgerman_date_year(double jd) {
    auto date = jd_to_julian(jd);
    return std::to_string(date[0]);
}
