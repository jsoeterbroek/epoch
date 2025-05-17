#include "roman.h"

std::string to_roman(int number) {
  if (number <= 0 || number > 3999) {
    return "(Invalid)";
  }

  struct Roman {
    int value;
    const char *numeral;
  };

  static const Roman numerals[] = {{1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"}, {100, "C"}, {90, "XC"}, {50, "L"},
                                   {40, "XL"},  {10, "X"},   {9, "IX"},  {5, "V"},    {4, "IV"},  {1, "I"}};

  std::string result;
  for (const auto &r : numerals) {
    while (number >= r.value) {
      result += r.numeral;
      number -= r.value;
    }
  }
  return result;
}
