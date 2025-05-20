#include "calendar.h"
#include <cmath>
#include <array>
#include "astro.h"
#include <string>
#include <iostream>

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
static const char *HINDU_WEEKDAYS[7] = {"Ravi-vara", "Soma-vara", "Mangala-vara", "Budha-vara", "Guru-vara", "Shukra-vara", "Shani-vara"};

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

// Simple festival lookup for a few major festivals (add more as needed)
// FIXME: This does not work well in test cases
std::string hindu_festival_name(double jd) {
  auto date = jd_to_hindu_lunar(jd);
  int year = date[0];
  int month = date[1];
  int tithi = date[2];
  //std::cout << "Hindu Festival date: " << date[0] << "-" << date[1] << "-" << date[2] << std::endl;

  // Apara Ekadashi: Vaisakha, Krishna Paksha, Ekadashi (tithi 26)
  if (month == 1 && tithi == 26) {  // Vaisakha, Krishna Ekadashi
    return "Apara Ekadashi";
  }
  // Holi: Allow a wider window due to lunar calculation imprecision.
  // Accept Phalguna (month 11) tithi 12–18 and Chaitra (month 0) tithi 1–4.
  if ((month == 11 && (tithi >= 12 && tithi <= 18)) || (month == 0 && (tithi >= 1 && tithi <= 4))) {
    return "Holi";
  }
  // Diwali: Ashwin, Amavasya (tithi 30)
  if (month == 6 && tithi == 30) {
    return "Diwali";
  }
  // Add more festivals as needed
  return "";
}

bool is_hindu_festival(double jd, const std::string &name) {
  return hindu_festival_name(jd) == name;
}

std::string format_hindu_date_year(double jd) {
  auto date = jd_to_hindu_lunar(jd);
  return std::to_string(date[0]);
}

std::string format_hindu_date_month(double jd) {
  auto date = jd_to_hindu_lunar(jd);
  const char *month = HINDU_MONTHS[date[1]];
  return std::string(month);
}

std::string format_hindu_date_month_paksha(double jd) {
  auto date = jd_to_hindu_lunar(jd);
  const char *month = HINDU_MONTHS[date[1]];
  const char *paksha = (date[2] <= 15) ? "Shukla Paksha" : "Krishna Paksha";
  return std::string(month) + ", " + paksha;
}

std::string format_hindu_date_day(double jd) {
  auto date = jd_to_hindu_lunar(jd);
  int tithi_index = (date[2] - 1) % 30;
  //return "Tithi " + std::to_string(date[2]) + " (" + TITHI_NAMES[tithi_index] + ")";
  return std::to_string(date[2]) + " (" + TITHI_NAMES[tithi_index] + ")";
}

std::string format_hindu_date_weekday(double jd) {
  int wday = static_cast<int>(astro::mod(std::floor(jd + 1.5), 7.0));
  return HINDU_WEEKDAYS[wday];
}
