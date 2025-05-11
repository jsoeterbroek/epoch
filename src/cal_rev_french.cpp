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

#include "cal_rev_french.h"
#include <cmath>
#include <array>
#include "astro.h"
#include <string>

//
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
  return FRENCH_REV_EPOCH - 1 + 365 * (year - 1) + std::floor((year - 1) / 4.0) + 30 * (month - 1) + day;
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

const char *french_weekday_name(int day) {
  static const char *names[] = {"Primidi", "Duodi", "Tridi", "Quartidi", "Quintidi", "Sextidi", "Septidi", "Octidi", "Nonidi", "Decadi"};
  return names[day % 10];
}

int french_jd_to_weekday(double jd) {
  return static_cast<int>(std::fmod(std::floor(jd + 1.5), 10.0));
}

const char *french_month_name(int month) {
  static const char *names[] = {
    "Vendemiaire",   "Brumaire",  "Frimaire",   // Autumn
    "Nivose",        "Pluviose",  "Ventose",    // Winter
    "Germinal",      "Floreal",   "Prairial",   // Spring
    "Messidor",      "Thermidor", "Fructidor",  // Summer
    "Sansculottides"                            // Complementary days
  };

  // Clamp month to 1–13
  if (month < 1) {
    month = 1;
  }
  if (month > 13) {
    month = 13;
  }
  return names[month - 1];
}

// format functions
std::string format_french_date_weekday(double jd) {
  const char *weekday_str = french_weekday_name(french_jd_to_weekday(jd));
  return std::string(weekday_str);
}

std::string format_french_date(double jd) {
  auto date = jd_to_french(jd);
  int year = date[0];
  int month = date[1];
  int day = date[2];
  const char *month_str = french_month_name(month);
  return std::to_string(day) + " " + month_str + ", AN " + std::to_string(year);
}

std::string format_french_date_local(double jd) {
  auto date = jd_to_french(jd);
  int year = date[0];
  int month = date[1];
  int day = date[2];

  const char *month_str = french_month_name(month);

  return std::to_string(day) + " " + month_str + ", AN " + std::to_string(year);
}
