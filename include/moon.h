#ifndef MOON_H
#define MOON_H

#include <array>
#include <string>
#include "astro.h"
#include <math.h>

// FIXME: rewrite to use https://github.com/oliverkwebb/moonphase/tree/main

// Function declarations
extern double moonphase(double ud);
int get_phase(time_t timestamp = 0);   // 0 means use current time
int get_phase(const char *phase_arg);  // String version for backward compatibility
std::string moon_phase_name();
std::string format_moon_phase();

#endif  // MOON_H
