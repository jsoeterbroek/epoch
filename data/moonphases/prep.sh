#!/bin/bash
cat mooninfo_2025.json | wc -l
cp mooninfo_2025.json mooninfo_2025.org
grep '12:00 UT' mooninfo_2025.json > mooninfo_UT_2025.json

sed -E 's/\{"time":"([0-9]{2}) ([A-Za-z]{3}) ([0-9]{4}) [^"]+", "phase":([0-9.]+).*/{"time":"\1-\2-\3", "phase":\4},/' mooninfo_UT_2025.json \
| sed -E -e 's/-Jan-/-01-/g' \
         -e 's/-Feb-/-02-/g' \
         -e 's/-Mar-/-03-/g' \
         -e 's/-Apr-/-04-/g' \
         -e 's/-May-/-05-/g' \
         -e 's/-Jun-/-06-/g' \
         -e 's/-Jul-/-07-/g' \
         -e 's/-Aug-/-08-/g' \
         -e 's/-Sep-/-09-/g' \
         -e 's/-Oct-/-10-/g' \
         -e 's/-Nov-/-11-/g' \
         -e 's/-Dec-/-12-/g' > foo

mv foo mooninfo_2025.json
mv mooninfo_UT_2025.json /tmp
mv mooninfo_2025.org /tmp

cat mooninfo_2025.json | wc -l
