cmake_minimum_required(VERSION 3.0)
project(ring_buffer)

set(tests_dir unit_tests)

set(CMAKE_CXX_STANDARD 14)

# google test:
enable_testing()
add_subdirectory(googletest)
add_subdirectory(${tests_dir})

# creating ringbuffer library
add_library(RingBuffer STATIC RingBuffer.cpp RingBuffer.hpp)