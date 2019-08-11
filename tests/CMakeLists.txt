cmake_minimum_required(VERSION 3.1.0)
project(mosaicgenerator_tests)

set(SOURCES
    pixelmap_test.cpp
    mosaic_test.cpp
    generator_test.cpp
)

add_executable(unittests main.cpp catch.hpp ${SOURCES})
target_link_libraries(unittests mgcore)