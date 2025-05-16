#ifndef COMPAT_H
#define COMPAT_H

#ifdef ARDUINO
#include <Arduino.h>
#else
#include <string>
#include <cstdio>

// Basic String class stub for desktop builds
class String {
public:
  std::string value;

  String() = default;
  String(const char *s) : value(s) {}
  String(const std::string &s) : value(s) {}
  String(int n) : value(std::to_string(n)) {}

  String &operator=(const char *s) {
    value = s;
    return *this;
  }
  String &operator=(const std::string &s) {
    value = s;
    return *this;
  }

  bool operator==(const String &other) const {
    return value == other.value;
  }
  bool operator!=(const String &other) const {
    return value != other.value;
  }

  const char *c_str() const {
    return value.c_str();
  }

  String operator+(const String &rhs) const {
    return String(value + rhs.value);
  }

  // Allow printing
  friend std::ostream &operator<<(std::ostream &os, const String &str) {
    return os << str.value;
  }
};

// Stub Serial for testing
struct {
  void print(const char *s) {
    std::printf("%s", s);
  }
  void println(const char *s) {
    std::printf("%s\n", s);
  }
  void print(int n) {
    std::printf("%d", n);
  }
  void println(int n) {
    std::printf("%d\n", n);
  }
} Serial;

#endif  // ARDUINO

#endif  // COMPAT_H
