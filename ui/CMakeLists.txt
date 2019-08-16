project(mosaicgenerator_ui)

set(SOURCES
    mainwindow.cpp
    mosaicwindow.cpp
    mainwindow.ui
    mosaicwindow.ui
)

add_library(mgui ${SOURCES})
target_link_libraries(mgui mgcore Qt5::Widgets)

target_include_directories(mgui PUBLIC . ${CMAKE_CURRENT_BINARY_DIR}/mgui_autogen/include)
