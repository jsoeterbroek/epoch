CXX := g++
CXXFLAGS := -std=c++17 -Wall -Iinclude -Itest

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

