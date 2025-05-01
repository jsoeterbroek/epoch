/* converted from */
/*
       JavaScript functions for the Fourmilab Calendar Converter

                  by John Walker  --  September, MIM
              http://www.fourmilab.ch/documents/calendar/

                This program is in the public domain.
*/

/*  You may notice that a variety of array variables logically local
    to functions are declared globally here.  In JavaScript, construction
    of an array variable from source code occurs as the code is
    interpreted.  Making these variables pseudo-globals permits us
    to avoid overhead constructing and disposing of them in each
    call on the function in which whey are used.  */

#include "calendar.h"
#include <cmath>
#include <array>
#include "astro.h"
#include <string>

namespace calendar {

bool leap_gregorian(int year) {
    return ((year % 4) == 0) &&
           (!(((year % 100) == 0) && ((year % 400) != 0)));
}

bool leap_julian(int year) {
    return astro::mod(year, 4) == ((year > 0) ? 0 : 3);
}

double gregorian_to_jd(int year, int month, int day) {
    return (GREGORIAN_EPOCH - 1) +
           (365 * (year - 1)) +
           std::floor((year - 1) / 4.0) +
           -std::floor((year - 1) / 100.0) +
           std::floor((year - 1) / 400.0) +
           std::floor((((367 * month) - 362) / 12.0) +
           ((month <= 2) ? 0 :
                          (leap_gregorian(year) ? -1 : -2)) +
           day);
}

std::array<int, 3> jd_to_gregorian(double jd) {
    double wjd, depoch, quadricent, dqc, cent, dcent, quad, dquad;
    int year, month, day, yindex;
    double leapadj;

    wjd = std::floor(jd - 0.5) + 0.5;
    depoch = wjd - GREGORIAN_EPOCH;
    quadricent = std::floor(depoch / 146097.0);
    dqc = astro::mod(depoch, 146097.0);
    cent = std::floor(dqc / 36524.0);
    dcent = astro::mod(dqc, 36524.0);
    quad = std::floor(dcent / 1461.0);
    dquad = astro::mod(dcent, 1461.0);
    yindex = static_cast<int>(std::floor(dquad / 365.0));
    year = static_cast<int>(quadricent * 400 + cent * 100 + quad * 4 + yindex);
    if (!(cent == 4 || yindex == 4)) {
        year++;
    }

    int yearday = static_cast<int>(wjd - gregorian_to_jd(year, 1, 1));
    leapadj = (wjd < gregorian_to_jd(year, 3, 1)) ? 0 :
              (leap_gregorian(year) ? 1 : 2);
    month = static_cast<int>(std::floor((((yearday + leapadj) * 12) + 373) / 367.0));
    day = static_cast<int>(wjd - gregorian_to_jd(year, month, 1)) + 1;

    return {year, month, day};
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


// Islamic
double islamic_to_jd(int year, int month, int day) {
    return (day +
           std::ceil(29.5 * (month - 1)) +
           (year - 1) * 354 +
           std::floor((3 + (11 * year)) / 30.0) +
           ISLAMIC_EPOCH - 1);
}

std::array<int, 3> jd_to_islamic(double jd) {
    jd = std::floor(jd) + 0.5;
    int year = static_cast<int>(
        std::floor((30 * (jd - ISLAMIC_EPOCH) + 10646) / 10631.0));
    int month = static_cast<int>(
        std::min(12.0, std::ceil((jd - islamic_to_jd(year, 1, 1) + 1) / 29.5)));
    int day = static_cast<int>(jd - islamic_to_jd(year, month, 1) + 1);

    return {year, month, day};
}


// Hebrew
double hebrew_to_jd(int year, int month, int day) {
    double jd = HEBREW_EPOCH + hebrew_delay_1(year) + day + 1;

    if (month < 7) {
        for (int m = 7; m <= hebrew_year_months(year); m++) {
            jd += hebrew_month_days(year, m);
        }
        for (int m = 1; m < month; m++) {
            jd += hebrew_month_days(year, m);
        }
    } else {
        for (int m = 7; m < month; m++) {
            jd += hebrew_month_days(year, m);
        }
    }

    return jd;
}

std::array<int, 3> jd_to_hebrew(double jd) {
    jd = std::floor(jd) + 0.5;

    int count = static_cast<int>((jd - HEBREW_EPOCH) / 365.246822206);
    int year = count;

    while (jd >= hebrew_to_jd(year + 1, 7, 1)) {
        year++;
    }

    int first = (jd < hebrew_to_jd(year, 1, 1)) ? 7 : 1;
    int month = first;

    while (jd > hebrew_to_jd(year, month, hebrew_month_days(year, month))) {
        month++;
    }

    int day = static_cast<int>(jd - hebrew_to_jd(year, month, 1) + 1);
    return {year, month, day};
}

bool is_hebrew_leap(int year) {
    return (((7 * year) + 1) % 19) < 7;
}

int hebrew_year_months(int year) {
    return is_hebrew_leap(year) ? 13 : 12;
}

double hebrew_delay_1(int year) {
    double months = std::floor((235 * year - 234) / 19.0);
    double parts = 12084 + 13753 * months;
    double day = months * 29 + std::floor(parts / 25920.0);
    if ((static_cast<int>(3 * (day + 1)) % 7) < 3) {
        day++;
    }
    return day;
}

double hebrew_delay_2(int year) {
    return hebrew_delay_1(year + 1) - hebrew_year_days(year);
}

int hebrew_year_days(int year) {
    return static_cast<int>(hebrew_to_jd(year + 1, 7, 1) -
                            hebrew_to_jd(year, 7, 1));
}

int hebrew_month_days(int year, int month) {
    if (month == 2 || month == 4 || month == 6 ||
        month == 10 || month == 13) {
        return 29;
    }
    if (month == 12 && !is_hebrew_leap(year)) {
        return 29;
    }
    if (month == 8 && ((hebrew_year_days(year) % 10) != 5)) {
        return 29;
    }
    if (month == 9 && ((hebrew_year_days(year) % 10) == 3)) {
        return 29;
    }

    return 30;
}

// Persian
double persian_to_jd(int year, int month, int day) {
    int epbase = (year >= 0) ? (year - 474) : (year - 473);
    int epyear = 474 + (epbase % 2820);

    return day +
           ((month <= 7) ? ((month - 1) * 31) : (((month - 1) * 30) + 6)) +
           std::floor((epyear * 682 - 110) / 2816.0) +
           (epyear - 1) * 365 +
           std::floor(epbase / 2820.0) * 1029983 +
           (PERSIAN_EPOCH - 1);
}

std::array<int, 3> jd_to_persian(double jd) {
    jd = std::floor(jd) + 0.5;

    double depoch = jd - persian_to_jd(475, 1, 1);
    double cycle = std::floor(depoch / 1029983.0);
    double cyear = fmod(depoch, 1029983.0);

    int ycycle;
    if (cyear == 1029982) {
        ycycle = 2820;
    } else {
        double aux1 = std::floor(cyear / 366.0);
        double aux2 = fmod(cyear, 366.0);
        ycycle = static_cast<int>(std::floor((2134.0 * aux1 + 2816.0 * aux2 + 2815.0) / 1028522.0) + aux1 + 1);
    }

    int year = ycycle + static_cast<int>(2820 * cycle) + 474;
    if (year <= 0) {
        year--;
    }

    double yday = jd - persian_to_jd(year, 1, 1) + 1;
    int month = (yday <= 186) ? static_cast<int>(std::ceil(yday / 31.0))
                              : static_cast<int>(std::ceil((yday - 6) / 30.0));
    int day = static_cast<int>(jd - persian_to_jd(year, month, 1) + 1);

    return {year, month, day};
}

// helper functions
int jd_to_weekday(double jd) {
    return static_cast<int>(std::fmod(std::floor(jd + 1.5), 7.0));
}

const char* day_of_week_name(int weekday) {
    static const char* names[] = {
        "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"
    };
    return names[weekday % 7];
}

int iso_day_of_week(double jd) {
    int dow = static_cast<int>(std::fmod(std::floor(jd + 1.5), 7.0));
    return dow == 0 ? 7 : dow;  // Convert Sunday (0) to 7
}

std::array<int, 3> jd_to_iso_week(double jd) {
    // Start by converting JD to Gregorian
    auto gdate = calendar::jd_to_gregorian(jd);
    int year = gdate[0];

    // Find JD of the Thursday of the current ISO week
    int weekday = iso_day_of_week(jd);
    double thursday_jd = jd + (4 - weekday);

    // Get the ISO week year (may differ from Gregorian year)
    auto thursday_date = calendar::jd_to_gregorian(thursday_jd);
    int week_year = thursday_date[0];

    // JD of January 4 of the ISO week year (guaranteed to be in week 1)
    double jan4 = calendar::gregorian_to_jd(week_year, 1, 4);
    int jan4_weekday = iso_day_of_week(jan4);

    // JD of the Monday of week 1
    double week1_start = jan4 - (jan4_weekday - 1);

    // Compute ISO week number
    int week = static_cast<int>(std::floor((jd - week1_start) / 7.0) + 1);

    return {week_year, week, weekday};
}

// French (Revolutionary)
//This calendar:
//Was used from 1793 to 1805.
//Has 12 months of 30 days + 5 or 6 "Sansculottides".
//Each month is divided into 3 décades (10-day weeks).
//Epoch starts on 22 September 1792 (Gregorian).
//
// Leap years were defined astronomically, but Walker used a simple "every 4 years" rule for approximation (like the Julian system).
// You may want to clamp or validate month ∈ [1, 13] (13 = Sansculottides), though Walker’s code didn’t enforce it strictly.
//
//
double french_to_jd(int year, int month, int day) {
    return FRENCH_REV_EPOCH - 1 +
           365 * (year - 1) +
           std::floor((year - 1) / 4.0) +
           30 * (month - 1) +
           day;
}

std::array<int, 3> jd_to_french(double jd) {
    jd = std::floor(jd) + 0.5;
    double depoch = jd - FRENCH_REV_EPOCH;
    int year = static_cast<int>(std::floor(depoch / 365.2425)) + 1;

    while (jd >= french_to_jd(year + 1, 1, 1)) {
        year++;
    }

    int month = static_cast<int>(std::floor((jd - french_to_jd(year, 1, 1)) / 30.0)) + 1;
    int day = static_cast<int>(jd - french_to_jd(year, month, 1)) + 1;

    return {year, month, day};
}

const char* french_weekday_name(int day) {
    static const char* names[] = {
        "Primidi", "Duodi", "Tridi", "Quartidi", "Quintidi",
        "Sextidi", "Septidi", "Octidi", "Nonidi", "Décadi"
    };
    return names[day % 10];
}

int french_jd_to_weekday(double jd) {
    return static_cast<int>(std::fmod(std::floor(jd + 1.5), 10.0));
}

//double jd = french_to_jd(5, 2, 10);  // Example: 10 Brumaire, Year 5
//int weekday = french_jd_to_weekday(jd);
//Serial.print("Décade weekday: ");
//Serial.println(french_weekday_name(weekday));
//
const char* french_month_name(int month) {
    static const char* names[] = {
        "Vendémiaire", "Brumaire", "Frimaire",      // Autumn
        "Nivôse", "Pluviôse", "Ventôse",            // Winter
        "Germinal", "Floréal", "Prairial",          // Spring
        "Messidor", "Thermidor", "Fructidor",       // Summer
        "Sansculottides"                            // Complementary days
    };

    // Clamp month to 1–13
    if (month < 1) month = 1;
    if (month > 13) month = 13;

    return names[month - 1];
}

// format functions
std::string format_french_date(double jd) {
    auto date = jd_to_french(jd);
    int year = date[0];
    int month = date[1];
    int day = date[2];

    const char* month_str = french_month_name(month);
    const char* weekday_str = french_weekday_name(french_jd_to_weekday(jd));

    return std::string(weekday_str) + " " +
           std::to_string(day) + " " +
           month_str + ", Year " +
           std::to_string(year);
}

std::string format_gregorian_date(double jd) {
    auto date = calendar::jd_to_gregorian(jd);
    return "Gregorian: " + std::to_string(date[2]) + "/" +
           std::to_string(date[1]) + "/" +
           std::to_string(date[0]);
}

std::string format_julian_date(double jd) {
    auto date = calendar::jd_to_julian(jd);
    return "Julian: " + std::to_string(date[2]) + "/" +
           std::to_string(date[1]) + "/" +
           std::to_string(date[0]);
}

std::string format_islamic_date(double jd) {
    auto date = calendar::jd_to_islamic(jd);
    return "Islamic: " + std::to_string(date[2]) + "/" +
           std::to_string(date[1]) + "/" +
           std::to_string(date[0]);
}

std::string format_hebrew_date(double jd) {
    auto date = calendar::jd_to_hebrew(jd);
    return "Hebrew: " + std::to_string(date[2]) + "/" +
           std::to_string(date[1]) + "/" +
           std::to_string(date[0]);
}

std::string format_persian_date(double jd) {
    auto date = calendar::jd_to_persian(jd);
    return "Persian: " + std::to_string(date[2]) + "/" +
           std::to_string(date[1]) + "/" +
           std::to_string(date[0]);
}

} // namespace calendar