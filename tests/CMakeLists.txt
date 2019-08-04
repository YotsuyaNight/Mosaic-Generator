cmake_minimum_required(VERSION 3.1.0)
project(mosaicgenerator)
set(CMAKE_CXX_STANDARD 17)

set(SOURCES
    pixelmap_test.cpp
    mosaic_test.cpp
    generator_test.cpp
)

add_executable(unittests main.cpp catch.hpp ${SOURCES})
target_link_libraries(unittests libmg)

set_target_properties(unittests
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)