#include "cal_mandaean.h"
#include <cmath>
#include <string>
#include <array>

// JD for 18 July 79 CE (Julian) = 1 Farvardin 1 AM (Anno Mandaica)
constexpr double MANDAEAN_EPOCH = 1757106.5;

// Mandaean months (1-based)
const char *mandanean_months[13] = {
  "Qaina",          // Aries
  "Aria",           // Taurus
  "Tumma",          // Gemini
  "Sartana",        // Cancer
  "Asta",           // Leo
  "Kta",            // Virgo
  "Libra",          // Libra
  "Scorpius",       // Scorpio
  "Hitia (Kanun)",  // Sagittarius. It currently corresponds to May / June in the Gregorian calendar due to a lack of a leap year in the Mandaean calendar.
  "Haura",          // Capricorn
  "Dalia",          // Aquarius
  "Nuna",           // Pisces
  "Parwanaya"       // 5 epagomenal days
};

// Simple day names; Mandaeans generally just number the days except for festivals
const char *mandanean_epagomenal[5] = {"Parwanaya 1", "Parwanaya 2", "Parwanaya 3", "Parwanaya 4", "Parwanaya 5"};

std::array<int, 3> jd_to_mandaean(double jd) {
  int days = static_cast<int>(std::floor(jd) - std::floor(MANDAEAN_EPOCH));
  int year = days / 365 + 1;
  int day_of_year = (days % 365) + 1;
  int month, day;
  if (day_of_year > 360) {
    month = 13;  // Parwanaya
    day = day_of_year - 360;
  } else {
    month = (day_of_year - 1) / 30 + 1;
    day = ((day_of_year - 1) % 30) + 1;
  }
  return {year, month, day};
}

double mandanean_to_jd(int year, int month, int day) {
  int y = year - 1;
  int m = month - 1;
  int d = day - 1;
  int days = y * 365;
  if (month == 13) {
    days += 360 + d;  // 12*30 + epagomenal day
  } else {
    days += m * 30 + d;
  }
  return std::floor(MANDAEAN_EPOCH) + days;
}

std::string mandanean_month_name(int month) {
  if (month >= 1 && month <= 13) {
    return mandanean_months[month - 1];
  }
  return "";
}

std::string mandanean_day_name(int month, int day) {
  if (month == 13 && day >= 1 && day <= 5) {
    return mandanean_epagomenal[day - 1];
  } else {
    return "Day " + std::to_string(day);
  }
}

// Example festivals, add more as needed
std::string mandanean_festival(int month, int day) {
  if (month == 13) {
    return "Parwanaya";  // The main festival: 5-day intercalary period
  }
  // Dehwa Daymaneh. It is celebrated on the first day of Hiṭia, which is
  // the 11th month of the Mandaean calendar.
  // Annually on May 20
  if (month == 1 && day == 1) {
    return "Dehwa Daymaneh";
  }

  // Add more known festival mappings here
  if (month == 1 && day == 1) {
    return "New Year's Day (Dehwa Rabba)";
  }

  // You may extend with additional dates based on community usage
  return "";
}

// Format: "1945-1-1 (Qaina Day 1)" or "1945-13-3 (Parwanaya 3)"
std::string format_mandaean_date(const std::array<int, 3> &date) {
  int year = date[0], month = date[1], day = date[2];
  std::string s = std::to_string(year) + "-" + std::to_string(month) + "-" + std::to_string(day) + " (";
  s += mandanean_month_name(month) + " " + mandanean_day_name(month, day) + ")";
  return s;
}

std::string format_mandaean_date_month(double jd) {
  auto date = jd_to_mandaean(jd);
  return mandanean_month_name(date[1]);
}

std::string format_mandaean_date_day(double jd) {
  auto date = jd_to_mandaean(jd);
  return std::to_string(date[2]);
}

// Use standard 7-day weekday (Sunday-based); you can adjust as needed:
const char *mandanean_weekdays[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

// Standard weekday calculation from JD (same as for Gregorian):
inline int jwday(double jd) {
  return static_cast<int>(std::floor(jd + 1.5)) % 7;
}

std::string format_mandaean_date_weekday(double jd) {
  return mandanean_weekdays[jwday(jd)];
}
