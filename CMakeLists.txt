cmake_minimum_required(VERSION 3.1.0)
project(mosaicgenerator)
set(CMAKE_CXX_STANDARD 17)

find_package(Qt5 COMPONENTS Widgets)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_INSTALL_RPATH .)

add_subdirectory(lib)
add_subdirectory(ui)
add_subdirectory(tests)

add_executable(mg main.cpp)
target_link_libraries(mg mgcore mgui)

install(TARGETS mg unittests DESTINATION ${CMAKE_SOURCE_DIR}/install)