#include "calendar.h"
#include <cmath>
#include <array>
#include "astro.h"
#include <string>

//
// Hindu
//

// Approximate mean synodic month (days)
constexpr double SYNODIC_MONTH = 29.53059;

// Month names
static const char *HINDU_MONTHS[12] = {"Chaitra", "Vaisakha", "Jyeshtha",     "Ashadha", "Shravana", "Bhadrapada",
                                       "Ashwin",  "Kartika",  "Margashirsha", "Pausha",  "Magha",    "Phalguna"};

// Tithi names (optional display enhancement)
static const char *TITHI_NAMES[30] = {"Pratipada", "Dvitiya",  "Tritiya",   "Chaturthi",  "Panchami",    "Shashthi",    "Saptami", "Ashtami",
                                      "Navami",    "Dashami",  "Ekadashi",  "Dvadashi",   "Trayodashi",  "Chaturdashi", "Purnima", "Pratipada",
                                      "Dvitiya",   "Tritiya",  "Chaturthi", "Panchami",   "Shashthi",    "Saptami",     "Ashtami", "Navami",
                                      "Dashami",   "Ekadashi", "Dvadashi",  "Trayodashi", "Chaturdashi", "Amavasya"};

// Weekday names (Vāra)
static const char *HINDU_WEEKDAYS[7] = {"Ravi-vāra", "Soma-vāra", "Mangala-vāra", "Budha-vāra", "Guru-vāra", "Shukra-vāra", "Shani-vāra"};

// Return mean new moon near JD 2451550.1 (2000-01-06)
double mean_new_moon_before(double jd) {
  double k = std::floor((jd - 2451550.1) / SYNODIC_MONTH);
  return 2451550.1 + k * SYNODIC_MONTH;
}

// Angle between moon and sun in degrees (simplified mean elongation)
double lunar_phase_angle(double jd) {
  double moon = astro::mod(13.1763966 * (jd - 2451550.1), 360.0);
  double sun = astro::mod(0.9856474 * (jd - 2451550.1), 360.0);
  return astro::mod(moon - sun, 360.0);
}

// Return [year, month_index, tithi]
std::array<int, 3> jd_to_hindu_lunar(double jd) {
  double new_moon = mean_new_moon_before(jd);
  double age = jd - new_moon;
  int tithi = static_cast<int>(std::floor((lunar_phase_angle(jd) / 12.0))) + 1;

  int month_index = static_cast<int>(std::floor((new_moon - 2451550.1) / SYNODIC_MONTH)) % 12;
  if (month_index < 0) {
    month_index += 12;
  }

  // Estimate lunar year from Gregorian year
  int greg_year = jd_to_gregorian(jd)[0];
  int lunar_year = greg_year + 57;  // Adjust based on calendar epoch (e.g. Vikrama Samvat)

  return {lunar_year, month_index, tithi};
}

std::string format_hindu_date_year(double jd) {
  auto date = jd_to_hindu_lunar(jd);
  return "Vikrama Samvat " + std::to_string(date[0]);
}

std::string format_hindu_date_month(double jd) {
  auto date = jd_to_hindu_lunar(jd);
  const char *month = HINDU_MONTHS[date[1]];
  const char *paksha = (date[2] <= 15) ? "Shukla Paksha" : "Krishna Paksha";
  return std::string(month) + ", " + paksha;
}

std::string format_hindu_date_day(double jd) {
  auto date = jd_to_hindu_lunar(jd);
  int tithi_index = (date[2] - 1) % 30;
  return "Tithi " + std::to_string(date[2]) + " (" + TITHI_NAMES[tithi_index] + ")";
}

std::string format_hindu_date_weekday(double jd) {
  int wday = static_cast<int>(astro::mod(std::floor(jd + 1.5), 7.0));
  return HINDU_WEEKDAYS[wday];
}
