// Globals.h
#ifndef GLOBALS_H
#define GLOBALS_H
#include <Arduino.h>

#define EPOCH_VERSION_MAJOR 0
#define EPOCH_VERSION_MINOR 0
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

#endif