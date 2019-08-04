#include "catch.hpp"
#include "pixelmap.h"

namespace MosaicGenerator {

TEST_CASE("PixelMap::PixelMap") {

    PixelMap p(2, 2);

    for (int x = 0; x < 2; x++) {
        for (int y = 0; y < 2; y++) {
            REQUIRE(p[x][y] == 0);
        }
    }

}

TEST_CASE("PixelMap::copyFrom") {

    PixelMap pm1(2, 2);
    PixelMap pm2(3, 3);    
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            pm2[x][y] = 64;
        }
    }
    pm1.copyFrom(&pm2);
    for (int x = 0; x < 2; x++) {
        for (int y = 0; y < 2; y++) {
            REQUIRE(pm1[x][y] == 64);
        }
    }

}

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
