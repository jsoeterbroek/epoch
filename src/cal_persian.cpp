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
// Persian
//
double persian_to_jd(int year, int month, int day) {
  int epbase = (year >= 0) ? (year - 474) : (year - 473);
  int epyear = 474 + (epbase % 2820);

  return day + ((month <= 7) ? ((month - 1) * 31) : (((month - 1) * 30) + 6)) + std::floor((epyear * 682 - 110) / 2816.0) + (epyear - 1) * 365
         + std::floor(epbase / 2820.0) * 1029983 + (PERSIAN_EPOCH - 1);
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
  int month = (yday <= 186) ? static_cast<int>(std::ceil(yday / 31.0)) : static_cast<int>(std::ceil((yday - 6) / 30.0));
  int day = static_cast<int>(jd - persian_to_jd(year, month, 1) + 1);

  return {year, month, day};
}

std::string format_persian_date(double jd) {
  auto date = jd_to_persian(jd);
  return "Persian: " + std::to_string(date[2]) + "/" + std::to_string(date[1]) + "/" + std::to_string(date[0]);
}
