#include "calendar.h"
#include <cmath>
#include <array>
#include "astro.h"
#include <string>

//
// Anglosaxon (Julian)
//
const char *anglosaxon_weekday_name(int day) {
  static const char *names[] = {"Monandag", "Tiwesdag", "Wodnesdag", "Dunresdag", "Frigedag", "Saeternesdag", "Sunnandag"};
  return names[(day + 6) % 7];  // Wrap 1 (Mon) to 7 (Sun) → 0–6
}

const char *anglosaxon_month_name(int month) {
  static const char *names[] = {"Aefterra Geola", "Sol-monath",  "Hreth-monath", "Easter-monath", "Thrimilce-monath", "Aerra Litha",
                                "Aeftera Litha",  "Weod-monath", "Halig-monath", "Winterfylleth", "Blot-monath",      "Aerra Geola"};
  //	Þrilīþa "Third (Mid)summer" (leap month)
  return names[month - 1];
}

const char *anglosaxon_month_desc(int month) {
  static const char *desc[] = {"After Yule",       "Mud month",       "Month of Wildness", "Month of Dawn", "Month of Three Milkings",
                               "Before Midsummer", "After Midsummer", "Weed month",        "Holy Month",    "Winter full moon",
                               "Blood Month",      "Before Yule"};
  return desc[month - 1];
}

int anglosaxon_jd_to_weekday(double jd) {
  return static_cast<int>(std::fmod(std::floor(jd + 1.5), 7.0));
}

std::string format_anglosaxon_date(double jd) {
  auto date = jd_to_julian(jd);
  int month = date[1];
  const char *month_str = anglosaxon_month_name(month);
  char buffer[20];
  snprintf(buffer, sizeof(buffer), "%i %s %i", date[2], month_str, date[0]);
  return std::string(buffer);
}

std::string format_anglosaxon_date_weekday(double jd) {
  auto date = jd_to_julian(jd);
  int weekday = calendar::iso_day_of_week(jd);  // ISO: Mon=1, Sun=7
  const char *weekday_name = anglosaxon_weekday_name(anglosaxon_jd_to_weekday(jd));
  char buffer[20];
  snprintf(buffer, sizeof(buffer), "%s", weekday_name);
  return std::string(buffer);
}

std::string format_anglosaxon_date_day(double jd) {
  auto date = jd_to_julian(jd);
  char buffer[20];
  snprintf(buffer, sizeof(buffer), "%i", date[2]);
  return std::string(buffer);
}

std::string format_anglosaxon_date_month(double jd) {
  auto date = jd_to_julian(jd);
  const char *month_str = anglosaxon_month_name(date[1]);
  char buffer[20];
  snprintf(buffer, sizeof(buffer), "%s", month_str);
  return std::string(buffer);
}

std::string format_anglosaxon_date_month_description(double jd) {
  auto date = jd_to_julian(jd);
  const char *month_desc_str = anglosaxon_month_desc(date[1]);
  char buffer[40];
  snprintf(buffer, sizeof(buffer), "%s", month_desc_str);
  return std::string(buffer);
}

std::string format_anglosaxon_date_year(double jd) {
  auto date = jd_to_julian(jd);
  char buffer[20];
  snprintf(buffer, sizeof(buffer), "%i AD", date[0]);
  return std::string(buffer);
}
