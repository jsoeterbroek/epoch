#ifndef CAL_BABYLONIAN_H
#define CAL_BABYLONIAN_H

#include <array>
#include <string>
#include <astro.h>

//Month starts = JD mod 29.53059 (synodic month)
//Year starts near spring equinox
//Intercalary month added every 2–3 years

// Constants

// Function declarations
std::array<int, 3> jd_to_babylonian(double jd);
std::string format_babylonian_date(double jd);
std::string format_babylonian_date_weekday(double jd);
std::string format_babylonian_date_month(double jd);
std::string format_babylonian_date_year(double jd);

#endif
