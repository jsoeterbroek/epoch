/* converted from */
/*
       JavaScript functions for the Fourmilab Calendar Converter

                  by John Walker  --  September, MIM
              http://www.fourmilab.ch/documents/calendar/

                This program is in the public domain.
*/

/*  https://en.wikipedia.org/wiki/Islamic_calendar */

#include "calendar.h"
#include <cmath>
#include <array>
#include "astro.h"
#include <string>

//
// Islamic
//
const char *islamic_months[12] = {"al-Muḥarram", "Safar",  "Rabi al-Awwal", "Rabi ath-Thani", "Jumada al-Ula", "Jumada ath-Thaniyah",
                                  "Rajab",       "Shaban", "Ramadan",       "Shawwal",        "Dhu al-Qidah",  "Dhu al-Ḥijjah"};

const char *islamic_months_ar[12] = {"ٱلْمُحَرَّم", "صَفَر",   "رَبِيع ٱلْأَوَّل", "رَبِيع ٱلثَّانِي", "جُمَادَىٰ ٱلْأُولَىٰ", "جُمَادَىٰ ٱلثَّانِيَة",
                                     "رَجَب",    "شَعْبَان", "رَمَضَان",      "شَوَّال",        "ذُو ٱلْقَعْدَة",    "ذُو ٱلْحِجَّة"};

const char *islamic_weekday_names[7] = {"al-Ahad", "al-Ithnayn", "ath-Thulatha", "al-Arbia", "al-Khamis", "al-Jumah", "as-Sabt"};

const char *islamic_weekday_names_ar[7] = {"ٱلْأَحَد", "الاِثْنَيْن", "ٱلثُّلَاثَاء", "ٱلْأَرْبِعَاء", "ٱلْخَمِيس", "ٱلْجُمْعَة", "ٱلسَّبْت"};

/*
Traditionally, the Islamic day begins at sunset and ends at the next sunset. Each Islamic 
day thus begins at nightfall and ends at the end of daylight.

The days in the seven-day week are, with the exception of the last two days, named after 
their ordinal place in the week.

On the sixth day of the week, the "gathering day" (Yawm al-Jumʿah), Muslims assemble for 
the Friday-prayer at a local mosque at noon. The "gathering day" is often regarded as the 
weekly day off. This is frequently made official, with many Muslim countries adopting 
Friday and Saturday (e.g., Egypt, Saudi Arabia) or Thursday and Friday as official weekends, 
during which offices are closed; other countries (e.g., Iran) choose to make Friday alone 
a day of rest. A few others (e.g., Turkey, Pakistan, Morocco, Nigeria, Malaysia) have adopted 
the Saturday-Sunday weekend while making Friday a working day with a long midday break to 
allow time off for worship.
No. 	Name 	    Arabic 	  English equivalent
1 	al-ʾAḥad    	ٱلْأَحَد 	  Saturday night and Sunday daytime
2 	al-Ithnayn  	الاِثْنَيْن    Sunday night and Monday daytime
3 	ath-Thulāthāʾ 	ٱلثُّلَاثَاء 	Monday night and Tuesday daytime
4 	al-ʾArbiʿāʾ 	ٱلْأَرْبِعَاء 	Tuesday night and Wednesday daytime
5 	al-Khamīs   	ٱلْخَمِيس 	  Wednesday night and Thursday daytime
6 	al-Jumʿah   	ٱلْجُمْعَة 	   Thursday night and Friday daytime
7 	as-Sabt     	ٱلسَّبْت 	  Friday night and Saturday daytime 
*/
int islamic_day_of_week(double jd) {
  // Compute weekday: 0 = Sunday, ..., 6 = Saturday
  int iso_day = static_cast<int>(std::floor(jd + 1.5)) % 7;
  if (iso_day < 0) {
    iso_day += 7;
  }
  // Convert ISO (0 = Sunday) to Islamic (1 = Sunday ... 7 = Saturday)
  return iso_day + 1;
}

std::array<int, 3> jd_to_islamic(double jd) {
  jd = std::floor(jd) + 0.5;
  int year = static_cast<int>(std::floor((30 * (jd - ISLAMIC_EPOCH) + 10646) / 10631.0));
  int month = static_cast<int>(std::min(12.0, std::ceil((jd - islamic_to_jd(year, 1, 1) + 1) / 29.5)));
  int day = static_cast<int>(jd - islamic_to_jd(year, month, 1) + 1);

  return {year, month, day};
}

double islamic_to_jd(int year, int month, int day) {
  return (day + std::ceil(29.5 * (month - 1)) + (year - 1) * 354 + std::floor((3 + (11 * year)) / 30.0) + ISLAMIC_EPOCH - 1);
}

int islamic_is_leap_year(int year) {
  return (
    year % 30 == 2 || year % 30 == 5 || year % 30 == 7 || year % 30 == 10 || year % 30 == 13 || year % 30 == 16 || year % 30 == 18 || year % 30 == 21
    || year % 30 == 24 || year % 30 == 26 || year % 30 == 29
  );
}

std::string format_islamic_date(double jd) {
  auto islamic = jd_to_islamic(jd);
  int year = islamic[0], month = islamic[1], day = islamic[2];

  const char *month_name = islamic_months[month - 1];

  char buffer[40];
  snprintf(buffer, sizeof(buffer), "%s %d, %d AH", month_name, day, year);
  return std::string(buffer);
}

// TODO: bidi, proper display arabic
std::string format_islamic_date_local(double jd, bool use_arabic = true) {
  auto islamic = jd_to_islamic(jd);
  int year = islamic[0], month = islamic[1], day = islamic[2];
  const char *month_name = use_arabic ? islamic_months_ar[month - 1] : islamic_months[month - 1];
  char buffer[80];
  snprintf(buffer, sizeof(buffer), "%s %d, %d AH", month_name, day, year);
  return std::string(buffer);
}

// TODO: bidi, proper display arabic
std::string format_islamic_date_weekday_local(double jd, bool use_arabic = false) {
  int weekday = islamic_day_of_week(jd);
  const char *weekday_name = use_arabic ? islamic_weekday_names_ar[weekday - 1] : islamic_weekday_names[weekday - 1];
  char buffer[50];
  snprintf(buffer, sizeof(buffer), "%s", weekday_name);
  return std::string(buffer);
}

std::string format_islamic_date_day_local(double jd, bool use_arabic = false) {
  auto islamic = jd_to_islamic(jd);
  int day = islamic[2];
  char buffer[40];
  snprintf(buffer, sizeof(buffer), "%d", day);
  return std::string(buffer);
}

std::string format_islamic_date_month_local(double jd, bool use_arabic = false) {
  auto islamic = jd_to_islamic(jd);
  int month = islamic[1];
  const char *month_name = islamic_months[month - 1];
  char buffer[40];
  snprintf(buffer, sizeof(buffer), "%s", month_name);
  return std::string(buffer);
}

std::string format_islamic_date_year_local(double jd, bool use_arabic = false) {
  auto islamic = jd_to_islamic(jd);
  int year = islamic[0];
  char buffer[40];
  snprintf(buffer, sizeof(buffer), "%d AH", year);
  return std::string(buffer);
}
