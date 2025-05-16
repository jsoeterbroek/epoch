cmake_minimum_required(VERSION 3.10)
project(epoch LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

enable_testing()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define the calendar module as a library
add_library(epoch_calendar
    src/calendar.cpp
    src/cal_hebrew.cpp
    src/cal_darian.cpp
    src/cal_babylonian.cpp
    # Add more .cpp files here if needed
)

# Include headers from 'include'
target_include_directories(epoch_calendar PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

# Add test executable from test directory
add_executable(epoch_tests
    test/test_all.cpp
)

# Link test executable to the calendar library
target_link_libraries(epoch_tests PRIVATE epoch_calendar)

# Also include headers in the test target (for direct includes)
target_include_directories(epoch_tests PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/test
)

# Register with CTest
add_test(NAME epoch COMMAND epoch_tests)

