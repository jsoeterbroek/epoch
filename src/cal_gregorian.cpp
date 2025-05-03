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

#include "cal_gregorian.h"
#include <cmath>
#include <array>
#include "astro.h"
#include <string>

//
// Gregorian
//
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
std::string format_gregorian_date(double jd) {
    auto date = jd_to_gregorian(jd);
    return "Gregorian: " + std::to_string(date[2]) + "/" +
           std::to_string(date[1]) + "/" +
           std::to_string(date[0]);
}