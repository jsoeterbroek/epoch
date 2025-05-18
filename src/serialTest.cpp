#include <serialTest.h>

int _delay = 2000;

void serialTest(void) {

  //Serial.println("+++++++++++++++++++++++++++++++++++");
  Serial.println("Serial test start");
  delay(_delay);

  // jd_to iso
  double jd = gregorian_to_jd(2025, 5, 2);  // 2th may, 2025 (= 2460797.5)
  Serial.print("Calculated JD (should be '2460797.5'): ");
  Serial.println(jd);
  Serial.println(calendar::format_iso_date(jd).c_str());

  Serial.println("-----------------------------------");
  delay(_delay);

  // Julian
  Serial.print(format_julian_date(jd).c_str());
  Serial.println(" - (Should be: 19 April 2025)");
  delay(_delay);
  Serial.println("-----------------------------------");

  // Gregorian
  Serial.print(format_gregorian_date(jd).c_str());
  Serial.println(" - (Should be: May 2, 2025)");
  delay(_delay);
  Serial.println("-----------------------------------");

  Serial.println("Serial test end");
  Serial.println("+++++++++++++++++++++++++++++++++++");
  Serial.println("");
  Serial.println("");
  delay(18000);
}
