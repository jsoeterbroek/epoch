
#include <string>

std::string format_french_date(double jd) {
    auto date = jd_to_french(jd);
    int year = date[0];
    int month = date[1];
    int day = date[2];

    const char* month_str = french_month_name(month);
    const char* weekday_str = french_weekday_name(french_jd_to_weekday(jd));

    return std::string(weekday_str) + " " +
           std::to_string(day) + " " +
           month_str + ", Year " +
           std::to_string(year);
}

std::string format_gregorian_date(double jd) {
    auto date = calendar::jd_to_gregorian(jd);
    return "Gregorian: " + std::to_string(date[2]) + "/" +
           std::to_string(date[1]) + "/" +
           std::to_string(date[0]);
}

std::string format_julian_date(double jd) {
    auto date = calendar::jd_to_julian(jd);
    return "Julian: " + std::to_string(date[2]) + "/" +
           std::to_string(date[1]) + "/" +
           std::to_string(date[0]);
}

std::string format_islamic_date(double jd) {
    auto date = calendar::jd_to_islamic(jd);
    return "Islamic: " + std::to_string(date[2]) + "/" +
           std::to_string(date[1]) + "/" +
           std::to_string(date[0]);
}

std::string format_hebrew_date(double jd) {
    auto date = calendar::jd_to_hebrew(jd);
    return "Hebrew: " + std::to_string(date[2]) + "/" +
           std::to_string(date[1]) + "/" +
           std::to_string(date[0]);
}

std::string format_persian_date(double jd) {
    auto date = calendar::jd_to_persian(jd);
    return "Persian: " + std::to_string(date[2]) + "/" +
           std::to_string(date[1]) + "/" +
           std::to_string(date[0]);
}

