project(mosaicgenerator_lib)

set(SOURCES
    iconrepository.cpp
    pixelmap.cpp
    mosaic.cpp
    generator.cpp
    controller.cpp
)

add_library(mgcore ${SOURCES})
target_link_libraries(mgcore Qt5::Widgets)

target_include_directories(mgcore PUBLIC .)
