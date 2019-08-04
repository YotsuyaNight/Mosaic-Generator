#include "catch.hpp"
#include "mosaic.h"

namespace MosaicGenerator {

TEST_CASE("Mosaic::Mosaic") {

    Mosaic m(4, 4, 4, 4);
    for (int x = 0; x < 4; x++) {
        for (int y = 0; y < 4; y++) {
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    REQUIRE(m.getTile(x, y)[i][j] == 0);
                }
            }
        }
    }

}

TEST_CASE("Mosaic::getTile") {

    Mosaic m(4, 4, 4, 4);
    for (int x = 0; x < 4; x++) {
        for (int y = 0; y < 4; y++) {
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    m.getTile(x, y)[i][j] = x * y + i * j;
                }
            }
        }
    }
    for (int x = 0; x < 4; x++) {
        for (int y = 0; y < 4; y++) {
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    REQUIRE(m.getTile(x, y)[i][j] == x * y + i * j);
                }
            }
        }
    }

}

}
