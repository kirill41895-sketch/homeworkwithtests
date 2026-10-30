cmake_minimum_required(VERSION 3.24)
project(ThermostatLab LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(CTest)

include(FetchContent)
FetchContent_Declare(googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG 52eb8108c5bdec04579160ae17225d66034bd723
)
FetchContent_MakeAvailable(googletest)

add_library(thermostat_core
    src/Entities.cpp
    src/Room.cpp
    src/Services.cpp
    src/Repositories.cpp
)
target_include_directories(thermostat_core PUBLIC include)

add_executable(thermostat_sim src/main.cpp)
target_link_libraries(thermostat_sim PRIVATE thermostat_core)

add_executable(thermostat_tests tests/test_main.cpp)
target_link_libraries(thermostat_tests PRIVATE thermostat_core GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(thermostat_tests DISCOVERY_MODE PRE_TEST)