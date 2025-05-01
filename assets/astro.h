
#ifndef ASTRO_H
#define ASTRO_H

#include <cmath>
#include <array>

namespace astro {

// Constants
constexpr double J2000 = 2451545.0;
constexpr double JulianCentury = 36525.0;
constexpr double JulianMillennium = JulianCentury * 10;
constexpr double AstronomicalUnit = 149597870.0;
constexpr double TropicalYear = 365.24219878;

// Function declarations
double astor(double a);
double dtr(double d);
double rtd(double r);
double fixangle(double a);
double fixangr(double a);
double dsin(double d);
double dcos(double d);
double mod(double a, double b);
double amod(double a, double b);
std::array<int, 3> jhms(double j);
int jwday(double j);
double obliqeq(double jd);
std::array<double, 2> nutation(double jd);
std::array<double, 2> ecliptoeq(double jd, double Lambda, double Beta);
double deltat(double year);

} // namespace astro

#endif // ASTRO_H
