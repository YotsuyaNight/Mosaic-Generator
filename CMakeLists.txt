cmake_minimum_required(VERSION 3.1.0)
project(mosaicgenerator)
set(CMAKE_CXX_STANDARD 17)

#QT config

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 COMPONENTS REQUIRED Widgets)

#Project config

include_directories(main)
set(PROJECT_SRC
    main/mainwindow.cpp
    main/mainwindow.ui
)

add_executable(mg main.cpp ${PROJECT_SRC})

target_link_libraries(mg Qt5::Widgets)