cmake_minimum_required(VERSION 3.1.0)
project(mosaicgenerator_lib)

find_package(Qt5 COMPONENTS Widgets)

set(SOURCES
    iconrepository.cpp
    pixelmap.cpp
    mosaic.cpp
    generator.cpp
)

add_library(libmg STATIC ${SOURCES})
target_link_libraries(libmg Qt5::Widgets)

target_include_directories(libmg PUBLIC .)