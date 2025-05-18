#include "cal_zoroastrian.h"
#include <cmath>
#include <array>
#include <string>

/* 
Note: The Zoroastrian Fasli calendar in this code strictly follows a 365-day solar year with no leap years, 
leading to cumulative drift compared to the Gregorian calendar. Test expectations reflect the resulting 
historical offset. 

Wikipedia https://en.wikipedia.org/wiki/Zoroastrian_calendar:
Webster's online dictionary and various unreferenced sources state that the Fasli calendar follows the 
Gregorian, and it is shown strictly following the Gregorian calendar in the period AD 2009–2031 in the tables 
published by R. E. Kadva[1]. The Gregorian calendar itself, however, will not keep 21 March as the date of the 
northern vernal equinox forever – it has a deviation of one day every 5025 years.
[1]: "Compendium of Fasli Zoroastrian Monthly Calendars 1379 A.Y. (2009-2010 C.E.) through
1400 A.Y. (2030-2031 C.E.)" https://zoroastrian.ru/files/eng/zoroastrian-calendars-1379-ay-1400-ay-fasli.pdf
*/

// Zoroastrian (Fasli) epoch: 632-03-19 Julian (JD 1948320.5)
constexpr double ZOROASTRIAN_EPOCH = 1948320.5;

const char *zoroastrian_months[13] = {"Farvardin", "Ardibehesht", "Khordad", "Tir",    "Amordad", "Shahrivar", "Mehr",
                                      "Aban",      "Adar",        "Dey",     "Bahman", "Esfand",  "Gatha"};

// Replace your day-name array in cal_zoroastrian.cpp
const char *zoroastrian_days[30] = {"Hormazd",  "Bahman", "Ardibehesht", "Shahrevar", "Spandarmad", "Hordad", "Amurdad", "Day Bad", "Adar",       "Aban",
                                    "Khorshed", "Mah",    "Tir",         "Gosh",      "Day Mihr",   "Mihr",   "Srosh",   "Rashn",   "Farvardin",  "Varahram",
                                    "Ram",      "Govad",  "Day Din",     "Din",       "Ard",        "Ashtad", "Asman",   "Zamyad",  "Mahraspand", "Aniran"};

std::array<int, 3> jd_to_zoroastrian(double jd) {
  // Days since Zoroastrian epoch (both floored to handle noon start)
  int days = static_cast<int>(std::floor(jd) - std::floor(ZOROASTRIAN_EPOCH));
  int year = days / 365 + 1;
  int day_of_year = (days % 365) + 1;
  int month, day;
  if (day_of_year > 360) {
    // Epagomenal days: month 13 (Gatha)
    month = 13;
    day = day_of_year - 360;
  } else {
    month = (day_of_year - 1) / 30 + 1;
    day = ((day_of_year - 1) % 30) + 1;
  }
  return {year, month, day};
}

double zoroastrian_to_jd(int year, int month, int day) {
  // Each year = 365 days, months 1–12 = 30 days, 13th month = 5 epagomenal days
  int y = year - 1;
  int m = month - 1;
  int d = day - 1;
  int days = y * 365;
  if (month == 13) {
    days += 360 + d;  // 12 * 30 + epagomenal day
  } else {
    days += m * 30 + d;
  }
  // Return JD at start of day
  return std::floor(ZOROASTRIAN_EPOCH) + days;
}

std::string zoroastrian_month_name(int month) {
  if (month >= 1 && month <= 13) {
    return zoroastrian_months[month - 1];
  }
  return "";
}

std::string zoroastrian_day_name(int day) {
  // Day names repeat every month; for Gatha days use their ordinal
  if (day >= 1 && day <= 30) {
    return zoroastrian_days[day - 1];
  }
  // Gatha days: 1–5 (could give custom names if desired)
  if (day >= 1 && day <= 5) {
    return "Gatha";
  }
  return "";
}

std::string format_zoroastrian_date(const std::array<int, 3> &date) {
  int year = date[0], month = date[1], day = date[2];
  std::string s = std::to_string(year) + "-" + std::to_string(month) + "-" + std::to_string(day) + " (";
  s += zoroastrian_month_name(month) + " ";
  s += zoroastrian_day_name(day) + ")";
  return s;
}

std::string format_zoroastrian_date_weekday(double jd) {
  auto date = jd_to_zoroastrian(jd);
  // For days 1–30, return the Zoroastrian day name; for Gatha days, you can return "Gatha" or ordinal
  if (date[1] == 13) {  // Gatha days (month 13)
    return "Gatha";
  }
  return zoroastrian_day_name(date[2]);
}

std::string format_zoroastrian_date_month(double jd) {
  auto date = jd_to_zoroastrian(jd);
  return zoroastrian_month_name(date[1]);
}

std::string format_zoroastrian_date_year(double jd) {
  auto date = jd_to_zoroastrian(jd);
  int year = date[0];
  return std::to_string(year) + " YZ";
}
