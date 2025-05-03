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

//
// Hebrew
//
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

std::string format_hebrew_date(double jd) {
    auto date = jd_to_hebrew(jd);
    return "Hebrew: " + std::to_string(date[2]) + "/" +
           std::to_string(date[1]) + "/" +
           std::to_string(date[0]);
}