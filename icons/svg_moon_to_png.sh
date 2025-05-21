#!/bin/bash
# Scalar vector icons to Adafruit GFX format script for esp32-weather-epd.
# Copyright (C) 2022-2025  Luke Marzen
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

mkdir -p icons
mkdir -p png

SVG_FILES="./svg/wi-moon*.svg"
PNG_PATH="./png/${1}x${1}"
PNG_FILES="${PNG_PATH}/*.png"

echo "Cleaning old files..."
if [ -e "$PNG_PATH" ];then rm -rf "$PNG_PATH" ; fi
# if [ -e "$HEADER_PATH" ];then rm -rf "$HEADER_PATH" ; fi
# if [ -e "$HEADER" ];then rm "$HEADER" ; fi

# arguments 1($1) determines the resolution of the output images
# IMAGES MUST HAVE A TOTAL NUMBER OF PIXELS THAT IS DIVISIBLE BY 8
# For sqaure images:
# x = original dimension of icon
# y = desired dimension of icon
# z = density
# In this case we are scaling by 0.25 for better image quality
# ImageMagick default density is 96
# z = 96 * y / (0.25 * x)

if [ ! -e "$PNG_PATH" ]; then
  mkdir $PNG_PATH
  for f in $SVG_FILES
  do
    echo "Converting .svg to .png for $f..."
    out="$PNG_PATH/$(basename $f .svg).png"
    inkscape -w ${1} -h ${1} $f -o $out --export-background="#ffffff"
  done
fi


echo "Done."
