#ifndef MOON_H
#define MOON_H

#include <array>
#include <string>
#include "astro.h"

// Function declarations
std::string moon_phase_name_detailed(double jd);
std::string format_moon_phase(double jd);

#endif  // MOON_H
