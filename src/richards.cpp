#include "richards.h"

namespace richards {

// Days in Gregorian month (M = 1..12, leap = true/false)
int gregorian_month_length(int m, bool leap) {
  if (m == 2) {
    return leap ? 29 : 28;
  }
  // L = 31 - MOD(MOD(M+9,12),5) % 2
  int mprime = rearranged_month(m);
  return 31 - (imod(imod(mprime, 5), 2));
}

// Day-of-year for Gregorian date (Y, M, D, leap)
int gregorian_day_of_year(int year, int month, int day, bool leap) {
  // T = (153*M'+2)/5 + D for year starting March 1
  int mprime = rearranged_month(month);
  int t = (153 * mprime + 2) / 5 + day;
  // Adjust for Jan/Feb
  if (month < 3) {
    t += (leap ? 60 : 59) - 306;
  }
  return t;
}

// Zeller's congruence for day-of-week (0=Saturday, 1=Sunday, ..., 6=Friday)
int zeller_weekday(int year, int month, int day) {
  if (month < 3) {
    month += 12;
    year -= 1;
  }
  int K = year % 100;
  int J = year / 100;
  int h = (day + (13 * (month + 1)) / 5 + K + K / 4 + J / 4 + 5 * J) % 7;
  return h;
}

// Table 23.2: Embolismic years in Metonic cycle
int metonic_common_years(int n) {
  // C = (12n + 17) / 19
  return (12 * n + 17) / 19;
}

// Utility: rearranged month number M' = MOD(M+9,12)
int rearranged_month(int m) {
  return imod(m + 9, 12);
}

// Utility: excess days X for Gregorian months (see Table 23.1)
int gregorian_month_excess(int m) {
  // Table 23.1: X = L - 28
  static const int X[12] = {3, 0, 3, 2, 3, 2, 3, 3, 2, 3, 2, 3};
  return X[imod(m - 1, 12)];
}

// Utility: sum of excess days Z up to month m (starting from March)
int gregorian_month_excess_sum(int m) {
  // Table 23.1: Z for months Mar(3)..Feb(2)
  static const int Z[14] = {0, 3, 5, 8, 10, 13, 16, 18, 21, 23, 26, 29, 0, 0};
  // m = 3..14 (Mar=3, Feb=14)
  if (m < 3) {
    m += 12;
  }
  return Z[m - 3];
}

}  // namespace richards
