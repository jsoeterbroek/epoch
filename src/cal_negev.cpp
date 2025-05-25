#include "cal_negev.h"
#include "venus.h"
#include <string>
#include <cmath>

/* 
https://www.negevrockart.co.il/posts/venuscalendar.html
*/

std::string format_nergev_venus(double jd) {
  int day = venus::day_in_cycle(jd);
  double angle = venus::phase_angle(jd);
  int phase = static_cast<int>(angle / 45.0);  // divide 360° into 8
  return "NRAV Phase " + std::to_string(phase);
}

// Returns 1-12: month counter (12 stones = 1 lunar year)
int format_negev_wheel(double jd) {
  // Each lunar year: 12 lunar months of 29.5 days each
  constexpr double LUNAR_MONTH = 29.5;
  constexpr int MONTHS_IN_YEAR = 12;
  double days_in_8_years = 8 * 12 * LUNAR_MONTH + 3 * 30; // 8 lunar years + 3 leap months = 2922 days
  double days_since_cycle_start = std::fmod(jd, days_in_8_years);
  int month = static_cast<int>(std::fmod(days_since_cycle_start / LUNAR_MONTH, MONTHS_IN_YEAR)) + 1;
  return month;
}

// Returns 1-8: year counter (8 stones = 8-year Venus cycle)
int format_negev_branch(double jd) {
  // Each Venus cycle: 8 lunar years + 3 leap months = 2922 days
  constexpr double DAYS_IN_8_YEARS = 2922.0;
  constexpr int YEARS_IN_CYCLE = 8;
  double days_since_cycle_start = std::fmod(jd, DAYS_IN_8_YEARS);
  double year_length = DAYS_IN_8_YEARS / YEARS_IN_CYCLE; // 365.25
  int year = static_cast<int>(days_since_cycle_start / year_length) + 1;
  return year;
}
