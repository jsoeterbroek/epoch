
#include "calendar.h"
#include <cmath>
#include <array>
#include "astro.h"
#include <string>


//
// Chinese Zodiac
//
//  🐉 Chinese Zodiac Calendar Overview
// Based on a 60-year sexagenary cycle

// Each year combines:
// 10 Heavenly Stems (Jia, Yi, Bing, Ding, etc.)
// 12 Earthly Branches (correspond to animals: Rat, Ox, Tiger, ...)
// Repeats every 60 years
// The cycle starts from 1984 as Jia-Zi in the modern epoch (or 2637 BCE in the traditional Huangdi calendar).
//


static const std::array<const char*, 12> ZODIAC_ANIMALS = {
    "Rat", "Ox", "Tiger", "Rabbit", "Dragon", "Snake",
    "Horse", "Goat", "Monkey", "Rooster", "Dog", "Pig"
};

static const std::array<const char*, 10> HEAVENLY_STEMS = {
    "Jia", "Yi", "Bing", "Ding", "Wu", "Ji", "Geng", "Xin", "Ren", "Gui"
};

static const std::array<const char*, 12> EARTHLY_BRANCHES = {
    "Zi", "Chou", "Yin", "Mao", "Chen", "Si",
    "Wu", "Wei", "Shen", "You", "Xu", "Hai"
};

// Convert JD → Gregorian year
static int jd_to_gregorian_year(double jd) {
    return jd_to_gregorian(jd)[0]; // year from [year, month, day]
}

// Zodiac animal (Earthly branch)
std::string chinese_zodiac_animal(double jd) {
    int year = jd_to_gregorian_year(jd);
    return ZODIAC_ANIMALS[(year - 4) % 12];
}

// Heavenly stem + Earthly branch
std::string chinese_zodiac_stem_branch(double jd) {
    int year = jd_to_gregorian_year(jd);
    int stem_index = (year - 4) % 10;
    int branch_index = (year - 4) % 12;

    return std::string(HEAVENLY_STEMS[stem_index]) + "-" + EARTHLY_BRANCHES[branch_index];
}

std::string chinese_day_stem_branch(double jd) {
    constexpr double JIA_ZI_JD = 2445701.5; // 1984-01-01 = Jia-Zi day

    static const std::array<const char*, 10> STEMS = {
        "Jia", "Yi", "Bing", "Ding", "Wu", "Ji", "Geng", "Xin", "Ren", "Gui"
    };
    static const std::array<const char*, 12> BRANCHES = {
        "Zi", "Chou", "Yin", "Mao", "Chen", "Si",
        "Wu", "Wei", "Shen", "You", "Xu", "Hai"
    };

    int offset = static_cast<int>(std::floor(jd - JIA_ZI_JD));
    int stem_index = (offset % 10 + 10) % 10;
    int branch_index = (offset % 12 + 12) % 12;

    return std::string(STEMS[stem_index]) + "-" + BRANCHES[branch_index];
}

std::string chinese_lunar_month_name(double jd) {
    constexpr double NEW_MOON_EPOCH = 2460009.5; // Jan 22, 2023
    constexpr double SYNODIC_MONTH = 29.53059;

    int months_since = static_cast<int>(std::round((jd - NEW_MOON_EPOCH) / SYNODIC_MONTH));
    int lunar_month_number = (months_since % 12 + 12) % 12;

    static const std::array<const char*, 12> LUNAR_MONTHS = {
        "Zhengyue", "Eryue", "Sanyue", "Siyue", "Wuyue", "Liuyue",
        "Qiyue", "Bayue", "Jiuyue", "Shiyue", "Shiyiyue", "Shieryue"
    };

    return LUNAR_MONTHS[lunar_month_number];
}

// Modular formatters
std::string format_chinese_zodiac_date_weekday(double jd) {
    // Chinese calendar is traditionally lunar, with no standard weekday system,
    // so we return the zodiac animal for weekday context.
    return chinese_zodiac_animal(jd);
}

std::string format_chinese_zodiac_date_day(double jd) {
    // Placeholder: traditional Chinese day naming is complex (Jia-Zi day cycle)
    // Here we simply return "Day N" within Gregorian month
    int day = jd_to_gregorian(jd)[2];
    return "Day " + std::to_string(day);
}

std::string format_chinese_zodiac_date_month(double jd) {
    static const std::array<const char*, 12> CHINESE_SOLAR_MONTHS = {
        "Zhengyue", "Eryue", "Sanyue", "Siyue", "Wuyue", "Liuyue",
        "Qiyue", "Bayue", "Jiuyue", "Shiyue", "Shiyiyue", "Shieryue"
    };
    int month = jd_to_gregorian(jd)[1];
    return CHINESE_SOLAR_MONTHS[(month - 1) % 12];
}

std::string format_chinese_zodiac_date_year(double jd) {
    int year = jd_to_gregorian_year(jd);
    std::string stem_branch = chinese_zodiac_stem_branch(jd);
    return stem_branch + " (" + std::to_string(year) + ")";
}

std::string format_chinese_zodiac_full_date(double jd) {
    std::string year_str   = format_chinese_zodiac_date_year(jd);      // Yi-Si (2025)
    std::string month_str  = chinese_lunar_month_name(jd);             // e.g. "Wuyue"
    std::string day_str    = chinese_day_stem_branch(jd);              // e.g. "Jia-Zi"
    std::string weekday    = format_chinese_zodiac_date_weekday(jd);   // e.g. "Snake"

    return year_str + ", " + month_str + ", " + day_str + ", " + weekday;
}
