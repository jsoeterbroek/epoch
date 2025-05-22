/* converted from */
/*
       JavaScript functions for the Fourmilab Calendar Converter

                  by John Walker  --  September, MIM
              http://www.fourmilab.ch/documents/calendar/

                This program is in the public domain. 
*/

/* 
Different reconstructions of the Old English calendar pick slightly different “month‐start” dates. 
The version here implemented has Thrimilci beginning on April 24 (so May 22 → day 29), whereas 
Mine Wyrtruman’s calendar apparently begins Thrimilci on April 28 (or thereabouts), which makes 
May 22 only the 25th.

Scholars don’t all agree on the precise day each month began—some tie month-starts to fixed equinox 
dates, others to ecclesiastical reckonings—so you’ll see these 3–4-day offsets in different 
reconstructions. Neither is “wrong”.
 */
#include "calendar.h"
#include <cmath>
#include <array>
#include "astro.h"
#include <string>
#include <cstring>
#include <iostream>

//
// Anglosaxon (Julian)
//
const char *anglosaxon_weekday_name(int day) {
  static const char *names[] = {"Monandag", "Tiwesdag", "Wodnesdag", "Dunresdag", "Frigedag", "Saeternesdag", "Sunnandag"};
  return names[(day + 6) % 7];  // Wrap 1 (Mon) to 7 (Sun) → 0–6
}

const char *anglosaxon_month_name(int month) {
  static const char *names[] = {"Aefterra Geola", "Solmonath",  "Hrethmonath", "Eosturmonath",  "Thrimilchi", "Aerra Litha",
                                "Aeftera Litha",  "Weodmonath", "Helegmonath", "Winterfilleth", "Blodmonath", "Aerra Geola"};
  //	Þrilīþa "Third (Mid)summer" (leap month)
  return names[month - 1];
}

const char *anglosaxon_month_desc(int month) {
  static const char *desc[] = {"After Yule",       "Month of cakes",  "Month of Wildness", "Month of Dawn", "Month of Three Milkings",
                               "Before Midsummer", "After Midsummer", "Weed month",        "Holy Month",    "Winter full moon",
                               "Blood Month",      "Before Yule"};
  return desc[month - 1];
}

/* 
Holidays
Ēosturdæġ	    Sun Apr 13, 2025 CE	  15th of Ēosturmōnaþ
Midsumor	    Sat Jun 21, 2025 CE	  25th of Ærra Liða
Winterfylleþ	Wed Nov 5, 2025 CE	  15th of Wintermōnaþ
Ġēola	        Sun Dec 21, 2025 CE	  1st of Ærra Ġēola
Blōstmfrēols 	Sun Apr 27, 2025 CE	  29th of Ēosturmōnaþ
Mōdraniht     Sun Dec 21, 2025 CE	  1st of Ærra Ġēola
 */
std::string anglosaxon_holiday_name(double jd) {
  auto date = jd_to_anglosaxon(jd);
  int year = date[0];
  int month = date[1];
  const char *month_str = anglosaxon_month_name(month);
  int day = date[2];
  std::cout << "DEBUG: Anglosaxon Holiday date: " << date[2] << " - " << month_str << " - " << date[0] << std::endl;

  // Ēosturdæġ	    Sun Apr 13, 2025 CE	  15th of Ēosturmōnaþ
  if ((strcmp(month_str, "Eosturmonath") == 0) && day == 15) {
    return "Eosturdag";
  }
  // Midsumor	      Sat Jun 21, 2025 CE	  25th of Ærra Liða
  if ((strcmp(month_str, "Aerra Litha") == 0) && day == 25) {
    return "Midsumor";
  }
  // Winterfylleþ	  Wed Nov 5, 2025 CE	  15th of Wintermōnaþ
  // Ġēola	        Sun Dec 21, 2025 CE	  1st of Ærra Ġēola
  // Blōstmfrēols 	Sun Apr 27, 2025 CE	  29th of Ēosturmōnaþ
  // Mōdraniht      Sun Dec 21, 2025 CE	  1st of Ærra Ġēola
  // Add more holidays as needed
  return "";
}

bool is_anglosaxon_holiday(double jd, const std::string &name) {
  return anglosaxon_holiday_name(jd) == name;
}

int anglosaxon_jd_to_weekday(double jd) {
  return static_cast<int>(std::fmod(std::floor(jd + 1.5), 7.0));
}

// Returns [year, month, day] in Anglosaxon calendar
std::array<int, 3> jd_to_anglosaxon(double jd) {
  auto g = jd_to_gregorian(jd);
  int year = g[0];
  int month = g[1];
  int day = g[2];

  // Anglosaxon months start at fixed Gregorian dates
  static const int month_starts[12][2] = {
    {12, 25},  // Aefterra Geola (After Yule) - Dec 25
    {1, 25},   // Solmonath - Jan 25
    {2, 24},   // Hrethmonath - Feb 24
    {3, 25},   // Eosturmonath - Mar 25
    {4, 24},   // Thrimilchi - Apr 24
    {5, 24},   // Aerra Litha - May 24
    {6, 23},   // Aeftera Litha - Jun 23
    {7, 23},   // Weodmonath - Jul 23
    {8, 22},   // Helegmonath - Aug 22
    {9, 21},   // Winterfilleth - Sep 21
    {10, 21},  // Blodmonath - Oct 21
    {11, 20}   // Aerra Geola - Nov 20
  };

  int amonth = 0, aday = 0, ayear = year;
  for (int i = 11; i >= 0; --i) {
    int m = month_starts[i][0];
    int d = month_starts[i][1];
    if ((month > m) || (month == m && day >= d)) {
      amonth = i + 1;
      // Calculate days since start of this Anglosaxon month
      int days_in_prev_month = 0;
      if (month == m) {
        aday = day - d + 1;
      } else {
        // Days left in start month
        int days_in_month = 31;
        if (m == 2) {
          days_in_month = 28 + ((ayear % 4 == 0 && (ayear % 100 != 0 || ayear % 400 == 0)) ? 1 : 0);
        } else if (m == 4 || m == 6 || m == 9 || m == 11) {
          days_in_month = 30;
        }
        aday = days_in_month - d + 1 + day;
      }
      break;
    }
  }
  if (amonth == 0) {
    // Before Dec 25: still in previous year's Aerra Geola
    amonth = 1;
    ayear -= 1;
    int days_in_dec = 31;
    aday = days_in_dec - 25 + 1 + day;
  }
  return {ayear, amonth, aday};
}

std::string format_anglosaxon_date(double jd) {
  auto date = jd_to_anglosaxon(jd);
  int month = date[1];
  const char *month_str = anglosaxon_month_name(month);
  char buffer[20];
  snprintf(buffer, sizeof(buffer), "%i %s %i", date[2], month_str, date[0]);
  return std::string(buffer);
}

std::string format_anglosaxon_date_weekday(double jd) {
  int weekday = calendar::iso_day_of_week(jd);  // ISO: Mon=1, Sun=7
  const char *weekday_name = anglosaxon_weekday_name(anglosaxon_jd_to_weekday(jd));
  char buffer[20];
  snprintf(buffer, sizeof(buffer), "%s", weekday_name);
  return std::string(buffer);
}

std::string format_anglosaxon_date_day(double jd) {
  auto date = jd_to_anglosaxon(jd);
  char buffer[20];
  snprintf(buffer, sizeof(buffer), "%i", date[2]);
  return std::string(buffer);
}

std::string format_anglosaxon_date_month(double jd) {
  auto date = jd_to_anglosaxon(jd);
  const char *month_str = anglosaxon_month_name(date[1]);
  char buffer[20];
  snprintf(buffer, sizeof(buffer), "%s", month_str);
  return std::string(buffer);
}

std::string format_anglosaxon_date_month_description(double jd) {
  auto date = jd_to_anglosaxon(jd);
  const char *month_desc_str = anglosaxon_month_desc(date[1]);
  char buffer[40];
  snprintf(buffer, sizeof(buffer), "%s", month_desc_str);
  return std::string(buffer);
}

std::string format_anglosaxon_date_year(double jd) {
  auto date = jd_to_anglosaxon(jd);
  char buffer[20];
  snprintf(buffer, sizeof(buffer), "%i AD", date[0]);
  return std::string(buffer);
}
