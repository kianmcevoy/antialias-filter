cmake_minimum_required(VERSION 3.10)
project(ioFilter)
add_executable(ioFilter src/test.cpp src/ioFilter.cpp src/biquad.cpp)
include_directories(include lib) 
set_target_properties(ioFilter PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/)