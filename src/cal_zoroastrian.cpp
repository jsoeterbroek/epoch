#include "cal_zoroastrian.h"

#include <cstdio>

struct NowruzEntry {
  int year;
  double jd;
};

// Add more years as needed
constexpr NowruzEntry SHENSHAI_NOWRUZ[] = {
  {2025, 2460802.5},  // August 15, 2025
  {2026, 2461167.5},  // August 15, 2026
  {2027, 2461532.5},  // August 15, 2027
};

constexpr NowruzEntry KADMI_NOWRUZ[] = {
  {2025, 2460772.5},  // July 16, 2025
  {2026, 2461137.5},  // July 16, 2026
  {2027, 2461502.5},  // July 16, 2027
};

constexpr NowruzEntry FASLI_NOWRUZ[] = {
  {2025, 2460727.5},  // March 21, 2025
  {2026, 2461092.5},  // March 21, 2026
  {2027, 2461457.5},  // March 21, 2027
};

const char *const MAH_NAMES[12] = {"Farvardin", "Ardibehesht", "Khordad", "Tir", "Amardad", "Shahrevar",
                                   "Meher",     "Avan",        "Adar",    "Dae", "Bahman",  "Aspandarmad"};

const char *const ROJ_NAMES[30] = {"Hormazd",     "Bahman", "Ardibehesht", "Shahrevar", "Spandarmad", "Khordad", "Amardad",      "Dae-pa-Adar",
                                   "Adar",        "Aban",   "Khorshed",    "Mah",       "Tir",        "Gosh",    "Dae-pa-Meher", "Meher",
                                   "Srosh",       "Rashne", "Fravardin",   "Behram",    "Ram",        "Govad",   "Dae-pa-Din",   "Din",
                                   "Ashishvangh", "Ashtad", "Asman",       "Zamyad",    "Marespand",  "Aneran"};

double find_nowruz_jd(int &out_year, double jd, const NowruzEntry *table, int size) {
  for (int i = size - 1; i >= 0; --i) {
    if (jd >= table[i].jd) {
      out_year = table[i].year - 586;  // Adjusting to Zoroastrian year
      return table[i].jd;
    }
  }
  // fallback to earliest
  out_year = table[0].year - 586;
  return table[0].jd;
}

std::array<int, 3> jd_to_zoroastrian(double jd, ZoroastrianCalendarVariant variant) {
  int year = 0;
  double nowruz_jd = 0.0;

  switch (variant) {
    case ZoroastrianCalendarVariant::Shenshai: nowruz_jd = find_nowruz_jd(year, jd, SHENSHAI_NOWRUZ, sizeof(SHENSHAI_NOWRUZ) / sizeof(NowruzEntry)); break;
    case ZoroastrianCalendarVariant::Kadmi:    nowruz_jd = find_nowruz_jd(year, jd, KADMI_NOWRUZ, sizeof(KADMI_NOWRUZ) / sizeof(NowruzEntry)); break;
    case ZoroastrianCalendarVariant::Fasli:    nowruz_jd = find_nowruz_jd(year, jd, FASLI_NOWRUZ, sizeof(FASLI_NOWRUZ) / sizeof(NowruzEntry)); break;
  }

  int day_of_year = (int)(jd - nowruz_jd) + 1;
  int month = 1 + (day_of_year - 1) / 30;
  int day = 1 + (day_of_year - 1) % 30;
  if (month > 12) {
    month = 12;
  }
  if (day > 30) {
    day = 30;
  }
  return {year, month, day};
}

const char *format_zoroastrian_date_roj(double jd, ZoroastrianCalendarVariant variant) {
  auto date = jd_to_zoroastrian(jd, variant);
  const char *roj = ROJ_NAMES[date[2] - 1];
  static char buffer[64];
  snprintf(buffer, sizeof(buffer), "%s", roj);
  return buffer;
}

const char *format_zoroastrian_date_mah(double jd, ZoroastrianCalendarVariant variant) {
  auto date = jd_to_zoroastrian(jd, variant);
  const char *mah = MAH_NAMES[date[1] - 1];
  static char buffer[64];
  snprintf(buffer, sizeof(buffer), "%s", mah);
  return buffer;
}
