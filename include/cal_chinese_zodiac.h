#ifndef CAL_CHINESE_ZODIAC_H
#define CAL_CHINESE_ZODIAC_H

#include <string>

// Core conversions
std::string chinese_zodiac_animal(double jd);
std::string chinese_zodiac_stem_branch(double jd);
std::string chinese_day_stem_branch(double jd);   // e.g. "Jia-Zi"
std::string chinese_lunar_month_name(double jd);  // e.g. "Wuyue" or "Rùn Bayue"

// Modular formatters
std::string format_chinese_zodiac_date_weekday(double jd);
std::string format_chinese_zodiac_date_day(double jd);
std::string format_chinese_zodiac_date_month(double jd);
std::string format_chinese_zodiac_date_year(double jd);
std::string format_chinese_zodiac_full_date(double jd);
std::string format_chinese_zodiac_animal(double jd);

#endif
