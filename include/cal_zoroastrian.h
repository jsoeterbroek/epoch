#pragma once
#include <array>
#include <string>

// Zoroastrian (Fasli) calendar module for Epoch Calendar Project
// Conversion functions: JD <-> Zoroastrian (Fasli) calendar
// Epoch: JD 1948320.5 (632-03-19 Julian)

// Convert Julian Day to Zoroastrian (Fasli) calendar date [year, month, day]
std::array<int, 3> jd_to_zoroastrian(double jd);

// Convert Zoroastrian (Fasli) calendar date to Julian Day
double zoroastrian_to_jd(int year, int month, int day);

// Get Zoroastrian month name (Fasli, 1-based)
std::string zoroastrian_month_name(int month);

// Get Zoroastrian day name (Fasli, 1-based)
std::string zoroastrian_day_name(int day);

// Format a full Zoroastrian (Fasli) date as a string (e.g., "1394-2-29 (Ardibehesht)")
std::string format_zoroastrian_date(const std::array<int, 3> &date);

std::string format_zoroastrian_date_weekday(double jd);
std::string format_zoroastrian_date_month(double jd);
std::string format_zoroastrian_date_year(double jd);
