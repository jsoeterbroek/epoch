#ifndef CAL_HEBREW_H
#define CAL_HEBREW_H

#include <array>
#include <string>

// Constants
constexpr double HEBREW_EPOCH = 347995.5;  // Hebrew epoch in Julian days

std::array<int, 3> jd_to_hebrew(double jd);
double hebrew_to_jd(int year, int month, int day);

bool is_hebrew_leap(int year);
int hebrew_year_days(int year);
int hebrew_year_months(int year);
int hebrew_month_days(int year, int month);
double hebrew_delay_1(int year);
double hebrew_delay_2(int year);
std::string format_hebrew_date(double jd);
std::string format_hebrew_date_day(double jd);
std::string format_hebrew_date_month(double jd);
std::string format_hebrew_date_year(double jd);
std::string format_hebrew_date_weekday(double jd);
std::string format_hebrew_full_date(double jd);

#endif
