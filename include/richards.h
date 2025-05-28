#pragma once
#include <array>
#include <string>
#include <algorithm>

namespace richards {

// Integer division (truncating towards zero)
inline int idiv(int a, int b) {
  return a / b;
}

// MOD(A,B): remainder, always 0 <= result < B
inline int imod(int a, int b) {
  return ((a % b) + b) % b;
}

// MIN(A,B): minimum of two integers
inline int imin(int a, int b) {
  return std::min(a, b);
}

// Days in Gregorian month (M = 1..12, leap = true/false)
int gregorian_month_length(int month, bool leap);

// Day-of-year for Gregorian date (Y, M, D, leap)
int gregorian_day_of_year(int year, int month, int day, bool leap);

// Zeller's congruence for day-of-week (0=Saturday, 1=Sunday, ..., 6=Friday)
int zeller_weekday(int year, int month, int day);

// Table 23.2: Embolismic years in Metonic cycle
int metonic_common_years(int n);

// Utility: rearranged month number M' = MOD(M+9,12)
inline int rearranged_month(int m);

// Utility: excess days X for Gregorian months (see Table 23.1)
int gregorian_month_excess(int m);

// Utility: sum of excess days Z up to month m (starting from March)
int gregorian_month_excess_sum(int m);

}  // namespace richards
