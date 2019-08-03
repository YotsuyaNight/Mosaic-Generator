cmake_minimum_required(VERSION 3.1.0)
project(mosaicgenerator)
set(CMAKE_CXX_STANDARD 17)

set(PROJECT_SRC
    pixelmap_test.cpp
)

add_executable(mg_tests main.cpp catch.hpp ${PROJECT_SRC})
target_link_libraries(mg_tests libmg)

set_target_properties(mg_tests
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)