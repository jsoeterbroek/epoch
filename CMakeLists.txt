cmake_minimum_required(VERSION 3.10)
project(epoch LANGUAGES CXX)

enable_testing()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include your calendar source files
add_library(epoch_calendar
    calendar.cpp
    cal_hebrew.cpp
    cal_darian.cpp
    cal_babylonian.cpp
    # Add other calendar modules here
)

# Add the test executable from the 'test' directory
add_executable(epoch_tests
    test/test_all.cpp
)

# Include directories
target_include_directories(epoch_tests PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/test
)

# Link to calendar code
target_link_libraries(epoch_tests PRIVATE epoch_calendar)

# Register with ctest
add_test(NAME epoch COMMAND epoch_tests)

