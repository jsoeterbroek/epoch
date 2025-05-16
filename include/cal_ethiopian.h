#ifndef CAL_ETHIOPIAN_H
#define CAL_ETHIOPIAN_H

#include <array>
#include <string>

std::array<int, 3> jd_to_ethiopian(double jd);
double ethiopian_to_jd(int year, int month, int day);

std::string format_ethiopian_date_day(double jd);
std::string format_ethiopian_date_month(double jd);
std::string format_ethiopian_date_year(double jd);
std::string format_ethiopian_date_weekday(double jd);

#endif
