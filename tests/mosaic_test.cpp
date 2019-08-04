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

TEST_CASE("Mosaic::Mosaic(QImage)") {

    Mosaic m(QImage("/home/yotsuya/icons/01_1.png"), 48, 48);
    Mosaic t(m.rows(), m.columns(), m.tileWidth(), m.tileHeight());
    for (int x = 0; x < m.rows(); x++) {
        for (int y = 0; y < m.columns(); y++) {
            t.setTile(x, y, &m.getTile(x, y));
        }
    }
    t.toImage().save("/home/yotsuya/mb_test_image.png");

}

}
