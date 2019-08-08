/*
* This file is part of "Mosaic Generator".
* 
* Copyright 2019 Marcin Dłubakowski <m.dlubakowski@gmail.com>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
* 
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/


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

    Mosaic m(QImage("/home/yotsuya/testing.jpg"), 3, 3);
    Mosaic t(m.rows(), m.columns(), m.tileWidth(), m.tileHeight());
    for (int x = 0; x < m.rows(); x++) {
        for (int y = 0; y < m.columns(); y++) {
            t.setTile(x, y, &m.getTile(x, y));
        }
    }
    t.toImage().save("/home/yotsuya/mb_test_image.png");

}

}
