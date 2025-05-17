#ifndef CAL_EGYPTIAN_H
#define CAL_EGYPTIAN_H

#include <array>
#include <string>
#include <astro.h>
#include <calendar.h>

// Core conversion
std::array<int, 3> jd_to_egyptian(double jd);

// Modular formatters
std::string format_egyptian_date_day(double jd);
std::string format_egyptian_date_month(double jd);
std::string format_egyptian_date_year(double jd);
std::string format_egyptian_date_weekday(double jd);  // optional/custom
std::string egyptian_day_fortune(double jd);          // lucky/unlucky
std::string format_egyptian_regnal_year(double jd);

struct PharaohReign {
  const char *name;
  double jd_start;
  double jd_end;
};

#endif
