cmake_minimum_required(VERSION 3.1.0)
project(mosaicgenerator_lib)

find_package(Qt5 COMPONENTS Widgets)

set(PROJECT_SRC

    main/mainwindow.cpp
    main/iconrepository.cpp
    main/pixelmap.cpp
 
    main/mainwindow.ui

)

add_library(libmg STATIC ${PROJECT_SRC})
target_link_libraries(libmg Qt5::Widgets)

target_include_directories(libmg PUBLIC main)
target_include_directories(libmg PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/libmg_autogen/include)