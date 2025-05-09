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
// Converts JD to Babylonian calendar: [year, month, day]
std::array<int, 3> jd_to_babylonian(double jd);
// Format Babylonian date without weekday, year (e.g., "Addaru 14")
std::string format_babylonian_date(double jd);
// Returns weekday name for a given JD in Babylonian 7-day cycle
std::string format_babylonian_date_weekday(double jd);
// Format Babylonian year
std::string format_babylonian_date_year(double jd);

#endif