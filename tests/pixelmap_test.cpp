#include "catch.hpp"
#include "pixelmap.h"

#include "pixelmap.h"

namespace MosaicGenerator {

TEST_CASE("PixelMap::operator[]") {

    PixelMap p(2, 2);
    p[0][0] = 1;
    p[1][1] = 2;
    REQUIRE(p[0][0] == 1);
    REQUIRE(p[1][1] == 2);
    p[0][0] = p[1][1];
    p[1][1] = p[0][0];
    REQUIRE(p[0][0] == 2);
    REQUIRE(p[1][1] == 2);

}

}
