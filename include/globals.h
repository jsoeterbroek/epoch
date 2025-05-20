// Globals.h
#ifndef GLOBALS_H
#define GLOBALS_H
#include <Arduino.h>
#include "config.h"

#define EPOCH_VERSION_MAJOR 0
#define EPOCH_VERSION_MINOR 2
#define EPOCH_VERSION_PATCH 1

static inline int epoch_version_major(void) {
  return EPOCH_VERSION_MAJOR;
}
static inline int epoch_version_minor(void) {
  return EPOCH_VERSION_MINOR;
}
static inline int epoch_version_patch(void) {
  return EPOCH_VERSION_PATCH;
}
static inline String get_timezone(void) {
  return TIMEZONE_LOC;
}

#endif
