#include "catch.hpp"
#include "generator.h"

namespace MosaicGenerator {

TEST_CASE("Generator") {

    IconRepository *ir = new IconRepository("/home/yotsuya/icons");
    QImage source("/home/yotsuya/dims.jpeg");
    Generator g(source, ir, 60, 60);
    g.setThreadCount(4);
    g.generate();
    QImage mosaic = g.mosaic()->toImage();
    mosaic.save("/home/yotsuya/mosaic.png");

    delete ir;

}

}