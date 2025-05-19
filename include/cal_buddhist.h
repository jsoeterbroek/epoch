#pragma once
#include <array>
#include <string>

// Buddhist (Thai Solar) calendar for Epoch Calendar Project
// Conversion functions: JD <-> Buddhist (Thai Solar) calendar
// Epoch: Buddhist Era = Gregorian Year + 543

// Convert Julian Day to Buddhist (Thai Solar) date [year, month, day]
std::array<int, 3> jd_to_buddhist(double jd);

// Convert Buddhist (Thai Solar) date to Julian Day
double buddhist_to_jd(int year, int month, int day);

// Get Buddhist (Thai Solar) month name (1-based)
std::string buddhist_month_name(int month);

// Format a full Buddhist (Thai Solar) date as a string (e.g., "2568-5-18 (May)")
std::string format_buddhist_date(const std::array<int, 3> &date);

std::string format_buddhist_date_day(double jd);
std::string format_buddhist_date_weekday(double jd);

// Format month name for given JD
std::string format_buddhist_date_month(double jd);

// Format year as Buddhist year with "BE" suffix (e.g., "2568 BE")
std::string format_buddhist_date_year(double jd);
