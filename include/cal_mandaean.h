#pragma once
#include <array>
#include <string>

// Mandaean calendar module for Epoch Calendar Project
// 12 months of 30 days, plus 5 epagomenal days ("Parwanaya")
// No leap years. Year 1 starts 18 July 79 CE (Julian)

// Convert Julian Day to Mandaean date [year, month, day]
std::array<int, 3> jd_to_mandaean(double jd);

// Convert Mandaean date to Julian Day
double mandanean_to_jd(int year, int month, int day);

// Get Mandaean month name (1-based)
std::string mandanean_month_name(int month);

// Get Mandaean day name (1-based; epagomenal days return "Parwanaya")
std::string mandanean_day_name(int month, int day);

// Format a full Mandaean date as a string (e.g., "1945-1-1 (Qaina)")
std::string format_mandaean_date(const std::array<int, 3> &date);

// Format month name for a given JD
std::string format_mandaean_date_month(double jd);

// Format day (number as string) for a given JD
std::string format_mandaean_date_day(double jd);

// Format weekday for a given JD (uses standard 7-day cycle)
std::string format_mandaean_date_weekday(double jd);

// Get festival name for given date (empty if none)
std::string mandanean_festival(int month, int day);
