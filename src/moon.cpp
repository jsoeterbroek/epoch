#include "cal_gregorian.h"
#include <cmath>
#include <array>
#include "astro.h"
#include <string>
#include "display_utils.h"
#include <cstdint>
#include "moon.h"

#include <ArduinoJson.h>
#include <StreamUtils.h>
#include <SD.h>
#include <SPI.h>

JsonDocument filter;
JsonObject filter_0 = filter.add<JsonObject>();
JsonDocument jdoc;

struct MoonPhase {
  char datetime;
  float phase;
};

MoonPhase moonphase;

// Compute the phase angle of the moon (0=new, 180=full)
double moon_phase_angle(double jd) {
  // Use Fourmilab's mean elongation approximation
  constexpr double SYNODIC_MONTH = 29.53059;
  constexpr double NEW_MOON_ANCHOR = 2451550.1;  // 2000-01-06 new moon
  double days_since = jd - NEW_MOON_ANCHOR;
  double phase = std::fmod(days_since, SYNODIC_MONTH);
  if (phase < 0) {
    phase += SYNODIC_MONTH;
  }
  return (phase / SYNODIC_MONTH) * 360.0;
}

void readJsonFile(const char *path, MoonPhase &moonphase) {

  filter_0["time"] = true;
  filter_0["phase"] = true;
  static uint8_t buf[5012];
  size_t len = 0;
  File jfile = SD.open(path);
  if (!jfile || jfile.isDirectory()) {
    Serial.println("ERROR: failed to open JSON file for reading");
  } else {
    ReadBufferingStream bufferedFile{jfile, 64};
    DeserializationError error = deserializeJson(jdoc, bufferedFile, DeserializationOption::Filter(filter));
    bufferedFile.flush();
    if (error) {
      Serial.print("ERROR: deserializeJson returned ");
      Serial.println(error.c_str());
    }
  }
  jfile.close();
}

// Example stub for querying the USNO API (synchronous, blocking, for illustration only)
// NOTE: This is a stub for using the USNO API for moon phase names.
// In practice, you would need to perform an HTTP GET request to the USNO API
// (https://aa.usno.navy.mil/data/api) and parse the JSON response.
// This requires an HTTP client and a JSON parser, which are not shown here.
// The functions below show the intended structure.
std::string query_usno_moon_phase(const std::string &date_iso) {
  // Example API endpoint:
  // https://aa.usno.navy.mil/api/moon/phases/date?date=2025-05-21
  // You would use an HTTP client to GET this URL and parse the JSON response.
  // For now, return an empty string or a placeholder.
  // In production, use a library like ArduinoHttpClient or similar for ESP32.
  return "";  // Not implemented: network code required
}

// query local JSON file for moon phase data
float query_gsfcnasa_moon_phase(const std::string &date_iso) {
  // https://svs.gsfc.nasa.gov/vis/a000000/a005400/a005415/mooninfo_2025.json
  // json file on SD filesystem
  readJsonFile("/moonphases/mooninfo_2025.json", moonphase);
  for (JsonObject item : jdoc.as<JsonArray>()) {

    const char *datetime = item["time"];  // "01 Jan 2025 12:00 UT", "02 Jan 2025 12:00 UT", "03 Jan 2025 12:00 ...
    float phase = item["phase"];          // 2.97, 7.7, 14.57, 23.28, 33.43, 44.47, 55.84, 66.92, 77.11, 85.86, ...
    //Serial.printf("time: %s phase: %f\r\n", datetime, phase);
    //Serial.printf("date_iso: %s\r\n", date_iso.c_str());  //2025-05-22
    if (strcmp(datetime, date_iso.c_str()) == 0) {
      Serial.printf("Found match: %s %f\r\n", datetime, phase);
      moonphase.phase = item["phase"];
      break;
    }
  }
  return moonphase.phase;
}

std::string moon_phase_name_detailed(double jd) {
  // Convert JD to Gregorian date (YYYY-MM-DD)
  auto g = jd_to_gregorian(jd);
  char date_iso[16];
  snprintf(date_iso, sizeof(date_iso), "%02d-%02d-%04d", g[2], g[1], g[0]);
  float phase = query_gsfcnasa_moon_phase(date_iso);

  Serial.printf("moon_phase_name_detailed: %s %f\r\n", date_iso, phase);

  // Length of the synodic (lunar) month
  const double lunar_month = 29.53;
  const double quarter = lunar_month / 4.0;  // ≈7.3825
  const double step = quarter / 6.0;         // ≈1.2304

  // Normalize phase into [0, lunar_month)
  while (phase < 0) {
    phase += lunar_month;
  }
  while (phase >= lunar_month) {
    phase -= lunar_month;
  }

  if (phase < step) {
    return "New Moon";
  } else if (phase < quarter) {
    return (phase < step * 2)   ? "Waxing Crescent-1"
           : (phase < step * 3) ? "Waxing Crescent-2"
           : (phase < step * 4) ? "Waxing Crescent-3"
           : (phase < step * 5) ? "Waxing Crescent-4"
           : (phase < step * 6) ? "Waxing Crescent-5"
                                : "Waxing Crescent-6";
  } else if (phase < quarter + step) {
    return "First Quarter";
  } else if (phase < 2 * quarter) {
    return (phase < quarter + step * 2)   ? "Waxing Gibbous-1"
           : (phase < quarter + step * 3) ? "Waxing Gibbous-2"
           : (phase < quarter + step * 4) ? "Waxing Gibbous-3"
           : (phase < quarter + step * 5) ? "Waxing Gibbous-4"
           : (phase < quarter + step * 6) ? "Waxing Gibbous-5"
                                          : "Waxing Gibbous-6";
  } else if (phase < 2 * quarter + step) {
    return "Full Moon";
  } else if (phase < 3 * quarter) {
    return (phase < 2 * quarter + step * 2)   ? "Waning Gibbous-1"
           : (phase < 2 * quarter + step * 3) ? "Waning Gibbous-2"
           : (phase < 2 * quarter + step * 4) ? "Waning Gibbous-3"
           : (phase < 2 * quarter + step * 5) ? "Waning Gibbous-4"
           : (phase < 2 * quarter + step * 6) ? "Waning Gibbous-5"
                                              : "Waning Gibbous-6";
  } else if (phase < 3 * quarter + step) {
    return "Last Quarter";
  } else if (phase < lunar_month) {
    return (phase < 3 * quarter + step * 2)   ? "Waning Crescent-1"
           : (phase < 3 * quarter + step * 3) ? "Waning Crescent-2"
           : (phase < 3 * quarter + step * 4) ? "Waning Crescent-3"
           : (phase < 3 * quarter + step * 5) ? "Waning Crescent-4"
           : (phase < 3 * quarter + step * 6) ? "Waning Crescent-5"
                                              : "Waning Crescent-6";
  } else {
    return "New Moon";
  }
}

std::string format_moon_phase(double jd) {
  return moon_phase_name_detailed(jd);
}
