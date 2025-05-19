CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wno-unused-variable \
            -Iinclude -Itest -I.pio/libdeps/m5paper/doctest/doctest

# Source and test file detection
SRC := $(wildcard src/cal*.cpp) src/astro.cpp src/roman.cpp
TESTS := $(wildcard test/test_*.cpp)
OBJS := $(patsubst test/%.cpp, build/%, $(TESTS))

# Set default goal
.DEFAULT_GOAL := run

.PHONY: all clean run build \
				french egyptian zoroastrian islamic saka germanic anglosaxon \
        ethiopian hebrew babylonian darian calendar icelandic chinese coptic

# Build everything
all: | build $(OBJS)

# Ensure build directory exists
build:
	@mkdir -p build

# Pattern rule to compile each test into build/
build/%: test/%.cpp $(SRC)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Run all tests
run: all
	@for test in $(OBJS); do \
		echo "Running $$test"; \
		./$$test || exit 1; \
	done

# Manual test targets for individual calendars
french: build/test_cal_french
	./$<

egyptian: build/test_cal_egyptian
	./$<

zoroastrian: build/test_cal_zoroastrian
	./$<

islamic: build/test_cal_islamic
	./$<

saka: build/test_cal_saka
	./$<

anglosaxon: build/test_cal_anglosaxon
	./$<

germanic: build/test_cal_germanic
	./$<

ethiopian: build/test_cal_ethiopian
	./$<

hebrew: build/test_cal_hebrew
	./$<

babylonian: build/test_cal_babylonian
	./$<

darian: build/test_cal_darian
	./$<

calendar: build/test_calendar
	./$<

icelandic: build/test_cal_icelandic
	./$<

chinese: build/test_cal_chinese_zodiac
	./$<

coptic: build/test_cal_coptic
	./$<

# Clean build artifacts
clean:
	rm -rf build

