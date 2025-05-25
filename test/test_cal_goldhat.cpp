#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "calendar.h"
#include "venus.h"
#include "cal_goldhat.h"
#include <iostream>

/*

  Wikipedia example for Goldhat calendar:
  To determine a 54 month cycle in the lunar system, the numerical values of the 
  green or blue Zones 3 to 21 are added, reaching a sum of 1,739 days. From this, 
  the values of the red intercalary fields 5, 16, and 17 are subtracted, The 
  result is 1739 − 142 = 1597 days, exactly 54 synodic months of 29.5305 days each.

  So, to get the number of days for 54 lunar months (as in the Wikipedia example):  
  `int days = goldhat_days_54_lunar_months(); // should be 1597`

**Explanation:**  
- Zone 5: 38 (special value, as per Wikipedia)
- Zone 16: 13 symbols × 4 rings = 52
- Zone 17: 13 symbols × 4 rings = 52

Now, the sum for zones 3–21 is 1739, and the sum of intercalary zones 5, 16, 17 is 38 + 52 + 52 = 142.  
So, 1739 − 142 = 1597, matching the expected test result.

*/
TEST_CASE("get number of days for 54 lunar months in Goldhat calendar") {
  int days = goldhat_days_54_lunar_months();  // should be 1597`
  CHECK(days == 1597);
}
