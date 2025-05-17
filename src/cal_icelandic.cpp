#include "calendar.h"
#include "astro.h"
#include <cmath>
#include <string>
#include <array>
#include <map>

constexpr double ICELANDIC_EPOCH = 2434923.5;  // Icelandic calendar anchor: Harpa 1, year 0 = JD 2434923.5 (Thursday, April 15, 1954)
constexpr int DAYS_IN_YEAR = 364;
constexpr int DAYS_IN_MONTH = 30;

/* 
// https://time-meddler.co.uk/the-old-icelandic-calendar/
Month / *Year 	|2023-24† |2024-25 	|2025-26 	|2026-27  |2027-28 	|2028-29 	|2029-30†
Harpa 	        |20 Apr 	|25 Apr 	|24 Apr 	|23 Apr   |22 Apr 	|20 Apr 	|19 Apr
Skerpla 	      |20 May 	|25 May 	|24 May 	|23 May 	|22 May 	|20 May 	|19 May
Solmanuthr 	    |19 Jun 	|24 Jun   |23 Jun 	|22 Jun 	|21 Jun 	|19 Jun 	|18 Jun
Sumarauki       |19 Jul 	|24 Jul 	|23 Jul 	|22 Jul 	|21 Jul 	|19 Jul 	|18 Jul
Heyannir        |30 Jul 	|28 Jul 	|27 Jul 	|26 Jul 	|25 Jul 	|23 Jul 	|29 Jul
Tvimanuthur     |29 Aug 	|27 Aug 	|26 Aug 	|25 Aug 	|24 Aug 	|22 Aug 	|28 Aug
Haustmanuthur   |28 Sep 	|26 Sep 	|25 Sep 	|24 Sep 	|23 Sep 	|21 Sep 	|27 Sep
Gormanuthur     |28 Oct 	|26 Oct 	|25 Oct 	|24 Oct 	|23 Oct 	|21 Oct 	|27 Oct
Ylir            |27 Nov 	|25 Nov 	|24 Nov 	|23 Nov 	|22 Nov 	|20 Nov 	|26 Nov
Morsugr         |27 Dec 	|25 Dec 	|24 Dec 	|23 Dec 	|22 Dec 	|20 Dec 	|26 Dec
Thorri          |26 Jan 	|24 Jan 	|23 Jan 	|22 Jan 	|21 Jan 	|19 Jan 	|25 Jan
Goa             |25 Feb 	|23 Feb 	|22 Feb 	|21 Feb 	|20 Feb 	|18 Feb 	|24 Feb
Einmanuthur     |26 Mar 	|25 Mar 	|24 Mar 	|23 Mar 	|21 Mar 	|20 Mar 	|26 Mar  
*/

static const std::map<int, std::array<double, 13>> icelandic_month_starts = {
  {2023, {2460054.5, 2460084.5, 2460114.5, 2460144.5, 2460155.5, 2460186.5, 2460216.5, 2460246.5, 2460276.5, 2460306.5, 2460336.5, 2460366.5, 2460396.5}},
  {2024, {2460419.5, 2460449.5, 2460479.5, 2460509.5, 2460517.5, 2460548.5, 2460578.5, 2460608.5, 2460638.5, 2460668.5, 2460698.5, 2460728.5, 2460758.5}},
  {2025, {2460786.5, 2460816.5, 2460846.5, 2460876.5, 2460886.5, 2460917.5, 2460947.5, 2460977.5, 2461007.5, 2461037.5, 2461067.5, 2461097.5, 2461127.5}},
  {2026, {2461152.5, 2461182.5, 2461212.5, 2461242.5, 2461251.5, 2461282.5, 2461312.5, 2461342.5, 2461372.5, 2461402.5, 2461432.5, 2461462.5, 2461492.5}},
  {2027, {2461519.5, 2461549.5, 2461579.5, 2461609.5, 2461619.5, 2461650.5, 2461680.5, 2461710.5, 2461740.5, 2461770.5, 2461800.5, 2461830.5, 2461860.5}},
  {2028, {2461887.5, 2461917.5, 2461947.5, 2461977.5, 2461985.5, 2462016.5, 2462046.5, 2462076.5, 2462106.5, 2462136.5, 2462166.5, 2462196.5, 2462226.5}},
  {2029, {2462253.5, 2462283.5, 2462313.5, 2462343.5, 2462353.5, 2462384.5, 2462414.5, 2462444.5, 2462474.5, 2462504.5, 2462534.5, 2462564.5, 2462594.5}},
  {2030, {2462621.5, 2462651.5, 2462681.5, 2462711.5, 2462721.5, 2462752.5, 2462782.5, 2462812.5, 2462842.5, 2462872.5, 2462902.5, 2462932.5, 2462962.5}}
};

int get_icelandic_month_index(double jd) {
  auto gdate = jd_to_gregorian(jd);
  int year = gdate[0];

  auto it = icelandic_month_starts.find(year);
  if (it == icelandic_month_starts.end()) {
    return -1;
  }

  const auto &starts = it->second;

  for (int i = 12; i >= 0; --i) {
    if (jd >= starts[i]) {
      // Check if we are before next month's start
      if (i < 12 && jd >= starts[i + 1]) {
        return i + 1;
      }
      return i;
    }
  }

  return -1;
}

// Weekday names
const char *icelandic_weekday_name(int day) {
  static const char *names[] = {"Manudagur", "Thrithjudagur", "Mithvikudagur", "Thorsdagur", "Fostudagur", "Laugardagur", "Sunnudagur"};
  return names[(day + 6) % 7];  // Wrap 1 (Mon) to 7 (Sun) → 0–6
}

// Month names (12 months of 30 days each)
static const char *ICELANDIC_MONTHS[13] = {"Harpa",       "Skerpla", "Solmanuthur", "Heyannir", "Tvimanuthur", "Haustmanuthur",
                                           "Gormanuthur", "Ylir",    "Morsugur",    "Thorri",   "Goa",         "Einmanuthur"};

static const char *ICELANDIC_MONTH_DESCRIPTIONS[13] = {
  "First summer month",
  "Second summer month",
  "Sun month - height of light and growth",
  "Leap week (Sumarauki)",
  "Hay month - main hay harvest time",
  "Second month of haying - final summer preparations",
  "Autumn month - gathering and storing begins",
  "Slaughter month - culling livestock before winter",
  "Yule month - beginning of the dark season",
  "Fat-sucking month - harsh winter begins",
  "Thorri - deep winter, Thorri feasts held",
  "Goa - thaw begins, honoring goddess Goa",
  "Lone month - last winter month before Harpa"
};

int icelandic_jd_to_weekday(double jd) {
  return static_cast<int>(std::fmod(std::floor(jd + 1.5), 7.0));
}

std::array<int, 3> jd_to_icelandic(double jd) {
  auto gdate = jd_to_gregorian(jd);
  int year = gdate[0];

  auto it = icelandic_month_starts.find(year);
  if (it == icelandic_month_starts.end()) {
    return {-1, -1, -1};  // fallback for unsupported years
  }

  const auto &starts = it->second;

  for (int i = 12; i >= 0; --i) {
    if (jd >= starts[i]) {
      int day = static_cast<int>(jd - starts[i]) + 1;
      if (day > 30) {
        return {-1, -1, -1};  // safeguard
      }
      return {year, i + 1, day};  // month is 1-based
    }
  }
  return {-1, -1, -1};  // before Harpa
}

std::string format_icelandic_date_weekday(double jd) {
  const char *weekday_name = icelandic_weekday_name(icelandic_jd_to_weekday(jd));
  char buffer[20];
  snprintf(buffer, sizeof(buffer), "%s", weekday_name);
  return std::string(buffer);
}

std::string format_icelandic_date_day(double jd) {
  int index = get_icelandic_month_index(jd);
  if (index == -1) {
    return "Unknown";
  }

  auto gdate = jd_to_gregorian(jd);
  int year = gdate[0];
  const auto &starts = icelandic_month_starts.at(year);

  int day = static_cast<int>(jd - starts[index]) + 1;

  if (day < 1 || day > 30) {
    return "Unknown";  // safety check
  }
  return std::to_string(day);
}
std::string format_icelandic_date_month(double jd) {
  int index = get_icelandic_month_index(jd);
  if (index == -1) {
    return "Unknown month";
  }
  return ICELANDIC_MONTHS[index];
}

std::string format_icelandic_date_month_description(double jd) {
  std::string name = format_icelandic_date_month(jd);
  for (int i = 0; i < 13; ++i) {
    if (name == ICELANDIC_MONTHS[i]) {
      return ICELANDIC_MONTH_DESCRIPTIONS[i];
    }
  }
  return "Unknown or pre-calendar date";
}

// There is no special numbering of the years used in the Icelandic calendar, so the year may be omitted or the current Gregorian year used.
std::string format_icelandic_date_year(double jd) {
  auto date = jd_to_gregorian(jd);
  char buffer[20];
  snprintf(buffer, sizeof(buffer), "%i AD", date[0]);
  return std::string(buffer);
}
