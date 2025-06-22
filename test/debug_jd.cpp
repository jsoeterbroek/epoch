// ABOUTME: Minimal test to print the Julian Day for July 15, 1965
// ABOUTME: Used to debug calendar conversion issues
#include "cal_gregorian.h"
#include <iostream>

int main() {
  std::cout << "Starting JD debug..." << std::endl;
  struct TestDate {
    int year, month, day;
    const char *label;
    double expected_jd_noon;
  };
  TestDate tests[] = {
    {1965, 7, 15, "1965-07-15", 2439006.5},
    {2000, 1, 1, "2000-01-01", 2451545.0},
    {1970, 1, 1, "1970-01-01", 2440588.0},
    {1582, 10, 15, "1582-10-15 (Gregorian reform)", 2299161.0},
    {1, 1, 1, "0001-01-01", 1721426.0}
  };
  for (const auto &t : tests) {
    double jd_proleptic = gregorian_to_jd_proleptic(t.year, t.month, t.day);
    double jd_astro = gregorian_to_jd_astronomical(t.year, t.month, t.day);
    std::cout << t.label << ":\n  JD (proleptic, midnight): " << jd_proleptic << "\n  JD (astronomical, noon): " << jd_astro
              << "\n  Expected JD (noon): " << t.expected_jd_noon << "\n";
  }
  return 0;
}
