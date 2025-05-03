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
//#include "cal_gregorian.h"
#include <cmath>
#include <array>
#include "astro.h"
#include <string>

//
// Islamic
//
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

std::string format_islamic_date(double jd) {
    auto date = jd_to_islamic(jd);
    return "Islamic: " + std::to_string(date[2]) + "/" +
           std::to_string(date[1]) + "/" +
           std::to_string(date[0]);
}
