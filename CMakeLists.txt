# For a general introduction to CMake, see:
# https://cmake.org/cmake/help/latest/guide/tutorial/

cmake_minimum_required(VERSION 3.14)
project(programmiersprachen-aufgabenblatt_5)

# Use the C++20 standard; fail if the compiler does not support it
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# On Clang/GCC/Intel compilers, use libc++ as the standard library implementation
# (needed for consistent behavior across platforms, especially on macOS with Xcode)
if(("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang") OR ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU") OR (("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel") AND (UNIX OR APPLE) ))
  set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++")
endif()

# Make headers in external/ available via #include
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external)

# Doctest - a single-header unit testing framework (https://github.com/doctest/doctest)
set(DOCTEST_DIRECTORY doctest)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/${DOCTEST_DIRECTORY})

# Activate CMake's test runner (ctest)
enable_testing()

add_subdirectory(source)
