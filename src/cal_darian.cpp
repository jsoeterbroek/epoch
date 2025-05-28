// Darian Calendar
//
//
// A Martian year in the Darian calendar has 24 months alternating between 28 and 27 sols.
//
// Non-leap years have 668 sols, leap years have 669.
// Leap years: every 10th year except every 500th year is not a leap year.
// Epoch: Darian year 0, month 1, sol 1 corresponds to MSD = 0.

// Using the Mars Sol Date (MSD) system as the intermediate.
// MSD = (JD - 2405522.0028779) / 1.0274912517
//
// 1 Mars year = 668.6 sols approx.
// The Darian calendar uses 24 months, alternating 28 and 27 sols, plus leap sols for intercalation.
// We’ll use the month and weekday names from the Darian calendar standard.
// Structure: 24 months per Martian year.
// Month Lengths: The first 5 months of each quarter have 28 sols (Martian days), and the 6th month has 27 sols, except in leap years when it has 28 sols.
// Leap Year Rule: A leap sol is added to the last month (Vrishika) in years where:

#include "calendar.h"
#include "cal_darian.h"
#include "astro.h"
#include <cmath>
#include <string>
#include <cmath>
#include <sstream>
#include <cstdio>

// Darian month lengths for the "zodiac" variant (Wikipedia)
static const int darian_month_lengths[24] = {28, 27, 28, 27, 28, 27, 28, 27, 28, 27, 28, 27, 28, 27, 28, 27, 28, 27, 28, 27, 28, 27, 28, 27};

static const char *darian_months_zodiac[24] = {"Sagittarius", "Dhanus", "Capricornus", "Makara",  "Aquarius", "Kumbha",  "Pisces",   "Mina",
                                               "Aries",       "Mesha",  "Taurus",      "Rishaba", "Gemini",   "Mithuna", "Cancer",   "Karka",
                                               "Leo",         "Simha",  "Virgo",       "Kanya",   "Libra",    "Tula",    "Scorpius", "Vrishika"};

// Leap year: every 10th year except every 500th year is not a leap year.
bool is_darian_leap_year(int year) {
  if (year % 500 == 0) {
    return false;
  }
  return (year % 10 == 0);
}

// Convert Darian date to JD
double darian_to_jd(int year, int month, int sol) {
  const double JD_EPOCH = 2405522.0028779;
  const double SOL_TO_EARTH_DAYS = 1.0274912517;
  int total_sols = 0;
  for (int y = 0; y < year; ++y) {
    total_sols += is_darian_leap_year(y) ? 669 : 668;
  }
  for (int m = 1; m < month; ++m) {
    int len = darian_month_lengths[(m - 1) % 24];
    // Month 24 (Vrishika) gets an extra sol in leap years
    if (m == 24 && is_darian_leap_year(year)) {
      len += 1;
    }
    total_sols += len;
  }
  total_sols += (sol - 1);
  double msd = static_cast<double>(total_sols);
  return msd * SOL_TO_EARTH_DAYS + JD_EPOCH;
}

// Convert JD to Darian date (zodiac variant)
void jd_to_darian(double jd, int &year, int &month, int &sol) {
  const double JD_EPOCH = 2405522.0028779;
  const double SOL_TO_EARTH_DAYS = 1.0274912517;
  int total_sols = static_cast<int>((jd - JD_EPOCH) / SOL_TO_EARTH_DAYS + 0.5);

  year = 0;
  while (true) {
    int sols_in_year = is_darian_leap_year(year) ? 669 : 668;
    if (total_sols < sols_in_year) {
      break;
    }
    total_sols -= sols_in_year;
    year++;
  }

  month = 1;
  for (int m = 1; m <= 24; ++m) {
    int len = darian_month_lengths[(m - 1) % 24];
    if (m == 24 && is_darian_leap_year(year)) {
      len += 1;
    }
    if (total_sols < len) {
      month = m;
      sol = total_sols + 1;
      return;
    }
    total_sols -= len;
  }
  // Fallback (should not happen)
  month = 24;
  sol = 1;
}

const char *darian_month_name(int month, DarianMonthStyle style) {
  if (style == DarianMonthStyle::Zodiac) {
    if (month < 1 || month > 24) {
      return "Invalid";
    }
    return darian_months_zodiac[month - 1];
  }
  // ...existing mythological names...
  static const char *mythological[24] = {"Aurora",   "Bootes", "Caelum", "Diana", "Eurus",  "Faunus",  "Gaia",  "Hercules",
                                         "Icarus",   "Juno",   "Kratos", "Luna",  "Mars",   "Neptune", "Ops",   "Phobos",
                                         "Quirinus", "Rhea",   "Saturn", "Terra", "Urania", "Vesta",   "Wotan", "Xanthus"};
  if (month < 1 || month > 24) {
    return "Invalid";
  }
  return mythological[month - 1];
}

const char *darian_weekday_name(int weekday, DarianWeekStyle style) {
  static const char *latin[7] = {"Sol Solis", "Sol Lunae", "Sol Martis", "Sol Mercurii", "Sol Jovis", "Sol Veneris", "Sol Saturni"};

  static const char *vedic[7] = {"Ravi-vara", "Soma-vara", "Mangala-vara", "Budha-vara", "Guru-vara", "Shukra-vara", "Shani-vara"};
  if (weekday < 0 || weekday > 6) {
    return "Invalid";
  }
  return (style == DarianWeekStyle::Latin) ? latin[weekday] : vedic[weekday];
}

std::string format_darian_date(int year, int month, int sol, DarianMonthStyle style) {
  const char *month_name = darian_month_name(month, style);
  char buffer[40];
  snprintf(buffer, sizeof(buffer), "%s %d, %d ME", month_name, sol, year);
  return std::string(buffer);
}

std::string format_darian_date_weekday(int year, int month, int sol, DarianWeekStyle style) {
  int total_sols = 0;
  for (int y = 0; y < year; ++y) {
    total_sols += is_darian_leap_year(y) ? 669 : 668;
  }
  for (int m = 1; m < month; ++m) {
    total_sols += (m % 2 == 1) ? 28 : 27;
  }
  total_sols += (sol - 1);
  int weekday_index = total_sols % 7;
  return std::string(darian_weekday_name(weekday_index, style));
}

std::string format_darian_date_full(int year, int month, int sol, DarianWeekStyle week_style, DarianMonthStyle month_style) {
  std::string date = format_darian_date(year, month, sol, month_style);
  std::string weekday = format_darian_date_weekday(year, month, sol, week_style);
  return date + ", " + weekday;
}

std::string format_darian_date_day(int sol) {
  char buffer[20];
  snprintf(buffer, sizeof(buffer), "Sol %d", sol);
  return std::string(buffer);
}

std::string format_darian_date_month(int month, DarianMonthStyle month_style) {
  const char *month_name = darian_month_name(month, month_style);
  return std::string(month_name);
}

std::string format_darian_date_year(int year) {
  char buffer[20];
  snprintf(buffer, sizeof(buffer), "%d ME", year);
  return std::string(buffer);
}
