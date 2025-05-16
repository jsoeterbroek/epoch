# g++ -std=c++17 test/test_cal_ethiopian.cpp src/cal_ethiopian.cpp -o ethiopian_test ./ethiopian_test
CXX := g++
#CXXFLAGS := -std=c++17 -Wall -Iinclude -Itest
CXXFLAGS := -std=c++17 -Wall -Wno-unused-variable -Iinclude -Itest
CXXFLAGS += -I.pio/libdeps/m5paper/doctest/doctest
CXXFLAGS += -I.pio/libdeps/m5paper/M5EPD/src
CXXFLAGS += -I$(HOME)/.platformio/packages/framework-arduinoespressif32/libraries/Preferences/src

SRC := $(wildcard src/cal*.cpp)
SRC += src/astro.cpp
TESTS := $(wildcard test/test_*.cpp)
OBJS := $(patsubst test/%.cpp, build/%, $(TESTS))

.PHONY: all clean run

all: $(OBJS)

build/%: test/%.cpp $(SRC)
	@mkdir -p build
	$(CXX) $(CXXFLAGS) $^ -o $@

run: all
	@for test in $(OBJS); do \
		echo "Running $$test"; \
		./$$test || exit 1; \
	done

clean:
	rm -rf build

