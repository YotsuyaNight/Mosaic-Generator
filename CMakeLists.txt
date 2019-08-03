cmake_minimum_required(VERSION 3.1.0)
project(mosaicgenerator)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5Test)

add_subdirectory(src/lib)
add_subdirectory(src/tests)

add_executable(mg src/main.cpp)
target_link_libraries(mg libmg)