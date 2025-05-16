# g++ -std=c++17 test/test_cal_ethiopian.cpp src/cal_ethiopian.cpp -o ethiopian_test ./ethiopian_test
CXX := g++
#CXXFLAGS := -std=c++17 -Wall -Iinclude -Itest
CXXFLAGS := -std=c++17 -Wall -Wno-unused-variable -Iinclude -Itest 
CXXFLAGS += -I.pio/libdeps/m5paper/doctest/doctest 
CXXFLAGS += -I.pio/libdeps/m5paper/M5EPD/src
CXXFLAGS += -I$(HOME)/.platformio/packages/framework-arduinoespressif32/libraries/Preferences/src
# CXXFLAGS += -I$(HOME)/.platformio/packages/framework-arduinoespressif32/cores/esp32
# CXXFLAGS += -I$(HOME)/.platformio/packages/framework-arduinoespressif32/tools/sdk/esp32/include
# CXXFLAGS += -I$(HOME)/.platformio/packages/framework-arduinoespressif32/tools/sdk/esp32/include/freertos/include
# CXXFLAGS += -I$(HOME)/.platformio/packages/framework-arduinoespressif32/tools/sdk/esp32/include/esp_common/include
# CXXFLAGS += -I$(HOME)/.platformio/packages/framework-arduinoespressif32/tools/sdk/esp32/include/freertos
# CXXFLAGS += -I$(HOME)/.platformio/packages/framework-arduinoespressif32/tools/sdk/esp32/include/esp_common
# CXXFLAGS += -I$(HOME)/.platformio/packages/framework-arduinoespressif32/tools/sdk/esp32/include/freertos/include/esp_additions/freertos
# CXXFLAGS += -I$(HOME)/.platformio/packages/framework-arduinoespressif32/tools/sdk/esp32/include/esp_additions
# CXXFLAGS += -I$(HOME)/.platformio/packages/framework-arduinoespressif32/tools/sdk/esp32/include/esp_additions/freertos
# CXXFLAGS += -I$(HOME)/.platformio/packages/framework-arduinoespressif32-libs/esp32s3/opi_opi/include
# CXXFLAGS += -I$(HOME)/.platformio/packages/framework-arduinoespressif32/tools/sdk/esp32/include/freertos/port/xtensa/include
# CXXFLAGS += -I$(HOME)/.platformio/packages/framework-arduinoespressif32/tools/sdk/esp32/include/xtensa/include
# CXXFLAGS += -I$(HOME)/.platformio/packages/framework-arduinoespressif32/tools/sdk/esp32/include/xtensa

SRC := $(wildcard src/*.cpp)
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

