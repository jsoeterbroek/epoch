#include "calendar.h"
#include "astro.h"
#include <cmath>
#include <string>
#include <array>

constexpr double ICELANDIC_EPOCH = 2434923.5;  // Icelandic calendar anchor: Harpa 1, year 0 = JD 2434923.5 (Thursday, April 15, 1954)
constexpr int DAYS_IN_YEAR = 364;
constexpr int DAYS_IN_MONTH = 30;

// Weekday names
const char *icelandic_weekday_name(int day) {
  static const char *names[] = {"Manudagur", "Thrithjudagur", "Mithvikudagur", "Thorsdagur", "Fostudagur", "Laugardagur", "Sunnudagur"};
  return names[(day + 6) % 7];  // Wrap 1 (Mon) to 7 (Sun) → 0–6
}

// Month names (12 months of 30 days each)
const char *icelandic_month_name(int month) {
  static const char *names[] = {"Harpa",       "Skerpla", "Solmanuthur", "Heyannir", "Tvimanuthur", "Haustmanuthur",
                                "Gormanuthur", "Ylir",    "Morsugur",    "Thorri",   "Goa",         "Einmanuthur"};
  return names[month - 1];
}

const char *icelandic_month_desc(int month) {
  static const char *desc[] = {
    "",
    "",
    "Sun month",
    "Hay working month",
    "Second month",
    "Autumn month",
    "Slaughter month",
    "Yule month",
    "Fat sucking month",
    "Frozen snow month",
    "Goa's Month",
    "Single month"
  };
  return desc[month - 1];
}

int icelandic_jd_to_weekday(double jd) {
  return static_cast<int>(std::fmod(std::floor(jd + 1.5), 7.0));
}

std::array<int, 3> jd_to_icelandic(double jd) {
  constexpr double TROPICAL_YEAR = 365.2422;
  constexpr int DAYS_IN_YEAR = 364;
  constexpr double DRIFT_PER_YEAR = TROPICAL_YEAR - DAYS_IN_YEAR;

  int days_since_epoch = static_cast<int>(std::floor(jd - ICELANDIC_EPOCH));

  // Estimate how many full Icelandic years have passed
  int rough_years = static_cast<int>(days_since_epoch / DAYS_IN_YEAR);

  // Now simulate drift and count leap weeks
  int leap_weeks = 0;
  double accumulated_drift = 0.0;
  int year = 0;
  int total_days = 0;

  while (total_days <= days_since_epoch) {
    accumulated_drift += DRIFT_PER_YEAR;

    int year_length = DAYS_IN_YEAR;
    if (accumulated_drift >= 7.0) {
      year_length += 7;
      accumulated_drift -= 7.0;
      leap_weeks++;
    }

    total_days += year_length;
    if (total_days <= days_since_epoch) {
      year++;
    }
  }

  // How many days into the current year?
  int days_into_year = days_since_epoch - (total_days - ((accumulated_drift < 0.0001) ? 364 : 371));

  int month = days_into_year / DAYS_IN_MONTH + 1;
  int day = days_into_year % DAYS_IN_MONTH + 1;
  return {year, month, day};
}

std::string format_icelandic_date_weekday(double jd) {
  const char *weekday_name = icelandic_weekday_name(icelandic_jd_to_weekday(jd));
  char buffer[20];
  snprintf(buffer, sizeof(buffer), "%s", weekday_name);
  return std::string(buffer);
}

std::string format_icelandic_date_day(double jd) {
  auto date = jd_to_icelandic(jd);
  return std::to_string(date[2]);
}

std::string format_icelandic_date_month(double jd) {
  auto date = jd_to_julian(jd);
  const char *month_str = icelandic_month_name(date[1]);
  char buffer[20];
  snprintf(buffer, sizeof(buffer), "%s", month_str);
  return std::string(buffer);
}

std::string format_icelandic_date_month_description(double jd) {
  auto date = jd_to_julian(jd);
  const char *month_desc_str = icelandic_month_desc(date[1]);
  char buffer[40];
  snprintf(buffer, sizeof(buffer), "%s", month_desc_str);
  return std::string(buffer);
}

std::string format_icelandic_date_year(double jd) {
  auto date = jd_to_julian(jd);
  char buffer[20];
  snprintf(buffer, sizeof(buffer), "%i AD", date[0]);
  return std::string(buffer);
}
