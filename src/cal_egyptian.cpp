#include "calendar.h"
#include "cal_egyptian.h"
#include <cmath>
#include <string>


//
// Ancient Egypt
//
static const double EGYPTIAN_EPOCH = 1825029.5; // Thoth 1, Year 1 (Julian Day)

// Month names (civil calendar, 12x30 + 5)
static const char* EGYPTIAN_MONTHS[13] = {
    "Thoth", "Phaophi", "Athyr", "Koiak", "Tybi", "Mechir",
    "Phamenoth", "Pharmuthi", "Pachons", "Payni", "Epiphi", "Mesore",
    "Epagomenal"
};

// Fortune day pattern (simplified mockup: 365-day rotating lucky/unlucky pattern)
static const char* EGYPTIAN_DAY_FORTUNE[7] = {
    "Lucky", "Unlucky", "Very Lucky", "Neutral", "Unlucky", "Lucky", "Neutral"
};

// --- Core Conversion ---
std::array<int, 3> jd_to_egyptian(double jd) {
    int days = static_cast<int>(std::floor(jd - EGYPTIAN_EPOCH));
    int year = days / 365 + 1;
    int day_of_year = days % 365;

    int month, day;
    if (day_of_year < 360) {
        month = day_of_year / 30 + 1;
        day = day_of_year % 30 + 1;
    } else {
        month = 13; // Epagomenal
        day = day_of_year - 359;
    }
    return { year, month, day };
}

// --- Formatters ---
std::string format_egyptian_date_day(double jd) {
    // Determine the lunar day number (1–30) based on jd
    int lunar_day = calendar::calculate_lunar_day(jd);

    // Array of lunar day names
    static const char* lunar_day_names[30] = {
        // "psḏntyw", "dnit", "ḥꜣw", "ḥꜣw-nfr", "dḥwty", "sḫt",
        // "sḫt-nfr", "ḥmnw", "psḏntyw-nfr", "dnit-nfr", "ḥꜣw-nfr",
        // "dḥwty-nfr", "sḫt-nfr", "ḥmnw-nfr", "sḏt", "psḏntyw-ḥry",
        // "dnit-ḥry", "ḥꜣw-ḥry", "dḥwty-ḥry", "sḫt-ḥry", "ḥmnw-ḥry",
        // "psḏntyw-ḥry-nfr", "dnit-ḥry-nfr", "ḥꜣw-ḥry-nfr", "dḥwty-ḥry-nfr",
        // "sḫt-ḥry-nfr", "ḥmnw-ḥry-nfr", "sḏt-nfr", "psḏntyw-ḥry-nfr", "dnit-ḥry-nfr"
        "psdntyw", "dnit", "h3w", "h3w-nfr", "dhwty", "sht",
        "sht-nfr", "hmnw", "psdntyw-nfr", "dnit-nfr", "h3w-nfr",
        "dhwty-nfr", "sht-nfr", "hmnw-nfr", "sdt", "psdntyw-hry",
        "dnit-hry", "h3w-hry", "dhwty-hry", "sht-hry", "hmnw-hry",
        "psdntyw-hry-nfr", "dnit-hry-nfr", "hꜣw-hry-nfr", "dhwty-hry-nfr",
        "sht-hry-nfr", "hmnw-hry-nfr", "sdt-nfr", "psdntyw-hry-nfr", "dnit-hry-nfr"
    };

    // Array of lunar day meanings
    static const char* lunar_day_meanings[30] = {
        "Shining Ones", "Second Day", "Third Day", "Good Fourth Day", "Thoth's Day", "Sixth Day",
        "Good Seventh Day", "Eighth Day", "Good Shining Ones", "Good Second Day", "Good Third Day",
        "Good Thoth's Day", "Good Sixth Day", "Good Eighth Day", "Full Moon", "Shining Ones Above",
        "Second Day Above", "Third Day Above", "Thoth's Day Above", "Sixth Day Above", "Eighth Day Above",
        "Good Shining Ones Above", "Good Second Day Above", "Good Third Day Above", "Good Thoth's Day Above",
        "Good Sixth Day Above", "Good Eighth Day Above", "Good Full Moon", "Good Shining Ones Above",
        "Good Second Day Above"
    };

    if (lunar_day >= 1 && lunar_day <= 30) {
        //return std::string(lunar_day_names[lunar_day - 1]) + ", " + lunar_day_meanings[lunar_day - 1];
        return std::string(lunar_day_meanings[lunar_day - 1]);
    } else {
        return "Invalid lunar day";
    }
}

std::string format_egyptian_date_month(double jd) {
    auto date = jd_to_egyptian(jd);
    return EGYPTIAN_MONTHS[date[1] - 1];
}

std::string format_egyptian_date_year(double jd) {
    auto date = jd_to_egyptian(jd);
    return "Year " + std::to_string(date[0]);
}

std::string format_egyptian_date_weekday(double jd) {
    // No 7-day week in original system; we simulate a 10-day week
    static const char* DECAN_DAYS[10] = {
        "Day 1 (Decan)", "Day 2", "Day 3", "Day 4", "Day 5",
        "Day 6", "Day 7", "Day 8", "Day 9", "Day 10"
    };
    int decan_day = static_cast<int>(std::floor(jd)) % 10;
    return DECAN_DAYS[decan_day];
}

std::string egyptian_day_fortune(double jd) {
    // Rotating 7-day pattern: mock lucky/unlucky rotation
    int index = static_cast<int>(jd) % 7;
    return EGYPTIAN_DAY_FORTUNE[index];
}