/* 

https://planetcalc.com/8434/
https://planetcalc.com/8448/

*/

#include "calendar.h"
#include "cal_egyptian.h"
#include <cmath>
#include <string>

//
// Ancient Egypt
//
// These dates use 365-day years, starting from Nabonassar (JD 1448638.5). The list is not complete, but gives us a working structure:
static const PharaohReign pharaohs[] = {
  // Anchor
  {"Nabonassar", 1448638.5, 1448638.5 + 14 * 365},

  // New Kingdom (18th–19th Dynasties)
  {"Thutmose III", 1193250.5, 1193250.5 + 54 * 365},   // 1479–1425 BCE
  {"Amenhotep III", 1198665.5, 1198665.5 + 38 * 365},  // 1390–1352 BCE
  {"Akhenaten", 1200050.5, 1200050.5 + 17 * 365},      // 1352–1336 BCE
  {"Tutankhamun", 1200665.5, 1200665.5 + 9 * 365},     // 1336–1327 BCE
  {"Ramses II", 1202673.5, 1202673.5 + 66 * 365},      // 1279–1213 BCE
  {"Merenptah", 1205073.5, 1205073.5 + 10 * 365},      // 1213–1203 BCE

  // Late Period and Ptolemaic
  {"Psamtik I", 1273600.5, 1273600.5 + 54 * 365},           // 664–610 BCE
  {"Cambyses II", 1283600.5, 1283600.5 + 8 * 365},          // 525–522 BCE
  {"Darius I", 1286000.5, 1286000.5 + 36 * 365},            // 522–486 BCE
  {"Alexander the Great", 1323000.5, 1323000.5 + 8 * 365},  // 332–323 BCE

  // Ptolemaic rulers (approx JD start from 305 BCE onward)
  {"Ptolemy I", 1332950.5, 1332950.5 + 38 * 365},
  {"Ptolemy II", 1334330.5, 1334330.5 + 38 * 365},
  {"Ptolemy III", 1335710.5, 1335710.5 + 25 * 365},
  {"Ptolemy IV", 1336620.5, 1336620.5 + 17 * 365},
  {"Ptolemy V", 1337245.5, 1337245.5 + 24 * 365},
  {"Ptolemy VI", 1338120.5, 1338120.5 + 24 * 365},
  {"Cleopatra VII", 1344143.5, 1344143.5 + 21 * 365}  // 51–30 BCE

  // You can extend this list with more accurate JD values or dynasties
};

// Month names (civil calendar)
static const char *EGYPTIAN_MONTHS_CIVIL[13] = {"Thoth",     "Phaophi", "Athyr", "Koiak",  "Tybi",   "Mechir",    "Phamenoth",
                                                "Pharmuthi", "Pachons", "Payni", "Epiphi", "Mesore", "Epagomenal"};
static const char *EGYPTIAN_MONTHS[13] = {"Month 1", "Month 2", "Month 3",  "Month 4",  "Month 5",  "Month 6", "Month 7",
                                          "Month 8", "Month 9", "Month 10", "Month 11", "Month 12", "Month 13"};

// Fortune day pattern (simplified mockup: 365-day rotating lucky/unlucky pattern)
static const char *EGYPTIAN_DAY_FORTUNE[7] = {"Lucky", "Unlucky", "Very Lucky", "Neutral", "Unlucky", "Lucky", "Neutral"};

// --- Core Conversion ---
std::array<int, 3> jd_to_egyptian(double jd) {

  constexpr double EGYPTIAN_EPOCH = 1448638.5;  // Nabonassar accession

  int days = static_cast<int>(std::floor(jd - EGYPTIAN_EPOCH));
  int year = days / 365 + 1;
  int day_of_year = days % 365;
  int month = day_of_year / 30 + 1;
  int day = day_of_year % 30 + 1;
  return {year, month, day};
}

double egyptian_to_jd(int year, int month, int day) {
  constexpr double EGYPTIAN_EPOCH = 1448638.5;
  return EGYPTIAN_EPOCH + 365.0 * (year - 1) + 30.0 * (month - 1) + (day - 1);
}

// --- Formatters ---
std::string format_egyptian_date_day(double jd) {
  // Determine the lunar day number (1–30) based on jd
  int lunar_day = calendar::calculate_lunar_day(jd);

  // Array of lunar day names
  static const char *lunar_day_names[30] = {"psdntyw",       "dnit",        "h3w",          "h3w-nfr",         "dhwty",           "sht",
                                            "sht-nfr",       "hmnw",        "psdntyw-nfr",  "dnit-nfr",        "h3w-nfr",         "dhwty-nfr",
                                            "sht-nfr",       "hmnw-nfr",    "sdt",          "psdntyw-hry",     "dnit-hry",        "h3w-hry",
                                            "dhwty-hry",     "sht-hry",     "hmnw-hry",     "psdntyw-hry-nfr", "dnit-hry-nfr",    "hꜣw-hry-nfr",
                                            "dhwty-hry-nfr", "sht-hry-nfr", "hmnw-hry-nfr", "sdt-nfr",         "psdntyw-hry-nfr", "dnit-hry-nfr"};

  // Array of lunar day meanings
  static const char *lunar_day_meanings[30] = {
    "Shining Ones",
    "Second Day",
    "Third Day",
    "Good Fourth Day",
    "Thoth's Day",
    "Sixth Day",
    "Good Seventh Day",
    "Eighth Day",
    "Good Shining Ones",
    "Good Second Day",
    "Good Third Day",
    "Good Thoth's Day",
    "Good Sixth Day",
    "Good Eighth Day",
    "Full Moon",
    "Shining Ones Above",
    "Second Day Above",
    "Third Day Above",
    "Thoth's Day Above",
    "Sixth Day Above",
    "Eighth Day Above",
    "Good Shining Ones Above",
    "Good Second Day Above",
    "Good Third Day Above",
    "Good Thoth's Day Above",
    "Good Sixth Day Above",
    "Good Eighth Day Above",
    "Good Full Moon",
    "Good Shining Ones Above",
    "Good Second Day Above"
  };

  if (lunar_day >= 1 && lunar_day <= 30) {
    //return std::string(lunar_day_names[lunar_day - 1]) + ", " + lunar_day_meanings[lunar_day - 1];
    return std::string(lunar_day_names[lunar_day - 1]);
  } else {
    return "Invalid lunar day";
  }
}

std::string format_egyptian_date_weekday(double jd) {
  // No 7-day week in original system; we simulate a 10-day week
  static const char *DECAN_DAYS[10] = {"Day 1", "Day 2", "Day 3", "Day 4", "Day 5", "Day 6", "Day 7", "Day 8", "Day 9", "Day 10"};
  int decan_day = static_cast<int>(std::floor(jd)) % 10;
  return DECAN_DAYS[decan_day];
}

std::string egyptian_day_fortune(double jd) {
  // Rotating 7-day pattern: mock lucky/unlucky rotation
  int index = static_cast<int>(jd) % 7;
  return EGYPTIAN_DAY_FORTUNE[index];
}

std::string format_egyptian_date_month(double jd) {
  auto date = jd_to_egyptian(jd);
  return EGYPTIAN_MONTHS[date[1] - 1];
}

std::string format_egyptian_date_year(double jd) {
  auto date = jd_to_egyptian(jd);
  return "Year " + std::to_string(date[0]);
}

std::string format_egyptian_regnal_year(double jd) {
  for (const auto &pharaoh : pharaohs) {
    if (jd >= pharaoh.jd_start && jd < pharaoh.jd_end) {
      int year = static_cast<int>((jd - pharaoh.jd_start) / 365) + 1;
      return "Year " + std::to_string(year) + " of " + pharaoh.name;
    }
  }
  return "Unknown regnal year";
}
