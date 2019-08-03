cmake_minimum_required(VERSION 3.1.0)
project(mosaicgenerator_ui)

find_package(Qt5 COMPONENTS Widgets)

set(SOURCES
    mainwindow.cpp
    mainwindow.ui
)

add_library(libmgui STATIC ${SOURCES})
target_link_libraries(libmgui libmg Qt5::Widgets)

target_include_directories(libmgui PUBLIC . ${CMAKE_CURRENT_BINARY_DIR}/libmgui_autogen/include)