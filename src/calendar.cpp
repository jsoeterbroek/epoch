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
#include "cal_gregorian.h"
#include <cmath>
#include <array>
#include "astro.h"
#include <string>

namespace calendar {

// helper functions
int jd_to_weekday(double jd) {
    return static_cast<int>(std::fmod(std::floor(jd + 1.5), 7.0));
}

const char* calendar_name(int index) {
    static const char* calendar_names[] = {
        "gregorian",    //  0
        "babylonian",   //  1
        "julian",       //  2
        "hebrew",       //  3
        "islamic",      //  4
        "egyptian",     //  4
        "coptic",       //  6
        "mayan",        //  7
        "persian",      //  8
        "rev_french",   //  9
        "saka",         // 10
        "norse",        // 11
        "anglo-saxon",  // 12
        "armenian",     // 13
        "georgian",     // 14
        "mandaean",     // 15
        "chinese",      // 16
        "buddhist",     // 17
        "mongolian",    // 18
        "ethiopian",    // 19
        "norse",        // 20
        "anglo-saxon",  // 21
        "zoroastrian"   // 22
    };
    return calendar_names[index % 9];
};

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

double iso_to_jd(int year, int week, int day) {
    double jan4_jd = gregorian_to_jd(year, 1, 4);
    int jan4_dow = calendar::iso_day_of_week(jan4_jd);  // Monday = 1 ... Sunday = 7
    double week1_start = jan4_jd - (jan4_dow - 1);       // JD of Monday in ISO week 1

    return week1_start + (week - 1) * 7 + (day - 1);
}

std::array<int, 3> jd_to_iso(double jd) {
    int year = jd_to_gregorian(jd - 3)[0];

    // If this JD is in the next ISO year
    if (jd >= gregorian_to_jd(year + 1, 1, 4) - calendar::iso_day_of_week(gregorian_to_jd(year + 1, 1, 4)) + 1) {
        year++;
    }

    double jan4_jd = gregorian_to_jd(year, 1, 4);
    int jan4_dow = calendar::iso_day_of_week(jan4_jd);  // Monday=1..Sunday=7
    double week1_start = jan4_jd - (jan4_dow - 1);

    int week = static_cast<int>(std::floor((jd - week1_start) / 7.0)) + 1;

    int day = calendar::iso_day_of_week(jd);  // Monday=1..Sunday=7

    return {year, week, day};
}

std::array<int, 3> jd_to_iso_week(double jd) {
    // Start by converting JD to Gregorian
    auto gdate = jd_to_gregorian(jd);
    int year = gdate[0];

    // Find JD of the Thursday of the current ISO week
    int weekday = iso_day_of_week(jd);
    double thursday_jd = jd + (4 - weekday);

    // Get the ISO week year (may differ from Gregorian year)
    auto thursday_date = jd_to_gregorian(thursday_jd);
    int week_year = thursday_date[0];

    // JD of January 4 of the ISO week year (guaranteed to be in week 1)
    double jan4 = gregorian_to_jd(week_year, 1, 4);
    int jan4_weekday = iso_day_of_week(jan4);

    // JD of the Monday of week 1
    double week1_start = jan4 - (jan4_weekday - 1);

    // Compute ISO week number
    int week = static_cast<int>(std::floor((jd - week1_start) / 7.0) + 1);

    return {week_year, week, weekday};
}

const char* iso_weekday_name(int weekday) {
    static const char* names[] = {
        "Monday", "Tuesday", "Wednesday", "Thursday",
        "Friday", "Saturday", "Sunday"
    };
    if (weekday < 1 || weekday > 7) return "Invalid";
    return names[weekday - 1];
}

std::string format_iso_week(double jd) {
    auto date = calendar::jd_to_iso_week(jd);
    return "ISO week: " + std::to_string(date[2]) + "/" +
           std::to_string(date[1]) + "/" +
           std::to_string(date[0]);
}

std::string format_iso_date(double jd) {
    auto iso = jd_to_iso(jd);
    int year = iso[0];
    int week = iso[1];
    int weekday = iso[2];
    const char* name = iso_weekday_name(weekday);

    char buffer[40];
    snprintf(buffer, sizeof(buffer), "ISO: %d-W%02d-%d (%s)", year, week, weekday, name);
    return std::string(buffer);
}
} // namespace calendar