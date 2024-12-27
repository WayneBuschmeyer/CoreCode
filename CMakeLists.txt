cmake_minimum_required(VERSION 3.10)
project(CoreCode)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the Core library
add_library(Core STATIC
    Core/Source/Core/Core.cpp
    Core/Source/Core/Core.h
)

# Add the executable (your main application)
add_executable(App
    App/Source/App.cpp
)

# Link the Core library to the application
target_link_libraries(App PRIVATE Core)

# Include Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/release-1.12.1.tar.gz
)
FetchContent_MakeAvailable(googletest)

# Enable testing
enable_testing()

# Add test executable
add_executable(tests
    Core/Source/Core/tests/test_dice.cpp
)

# Link tests with Core and Google Test
target_link_libraries(tests PRIVATE Core gtest_main)

# Add tests to CTest
add_test(NAME CoreTests COMMAND tests)
