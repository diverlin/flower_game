#include "gridtest.h"
#include <grid.h>
#include <pixmaplayer.h>
#include <index2d.h>

#include <QTest>

void GridTest::testGrid1D2DIndexConversion()
{
    const int rows = 5;
    const int columns = 10;
    core::Grid grid(rows, columns);
    QCOMPARE(int(grid.size()), rows*columns);

    size_t index1d = grid.getIndex1D(2,9);
    core::Index2D index2d = grid.getIndex2D(index1d);
    QCOMPARE(index1d, 29);
    QCOMPARE(index2d.i(), 2);
    QCOMPARE(index2d.j(), 9);
}

void GridTest::testGridAddRemoveLayer()
{
    const int rows = 5;
    const int columns = 10;
    core::Grid grid(rows, columns);
    QCOMPARE(int(grid.size()), rows*columns);

    for (int i=0; i<rows; ++i) {
        for (int j=0; j<rows; ++j) {
            QVERIFY(grid.isIndexFree(grid.getIndex1D(core::Index2D(i, j))));
        }
    }

    // add
    grid.addLayer(grid.getIndex1D(2,3),core::PixmapLayer::FLOWER_LAYER);
    QVERIFY(!grid.isIndexFree(grid.getIndex1D(core::Index2D(2,3))));

    grid.addLayer(grid.getIndex1D(4,4),core::PixmapLayer::ROCK_LAYER);
    QVERIFY(!grid.isIndexFree(grid.getIndex1D(core::Index2D(4,4))));

    // remove
    grid.removeLayer(grid.getIndex1D(2,3),core::PixmapLayer::FLOWER_LAYER);
    QVERIFY(grid.isIndexFree(grid.getIndex1D(core::Index2D(2,3))));

    grid.removeLayer(grid.getIndex1D(4,4),core::PixmapLayer::ROCK_LAYER);
    QVERIFY(grid.isIndexFree(grid.getIndex1D(core::Index2D(4,4))));
}

void GridTest::testGridFreeRandomIndex()
{
    const int rows = 4;
    const int columns = 4;
    core::Grid grid(rows, columns);

    int counter = 0;
    for (int i=0; i<20; ++i) {
        int index1d = grid.getFreeRandomIndex();
        grid.addLayer(index1d, core::PixmapLayer::FLOWER_LAYER);
        if (counter<16) {
            QVERIFY(index1d >= 0);
        } else {
            QVERIFY(index1d == -1);
        }
        counter++;
    }
}

void GridTest::testGridMultilayer()
{
    const int rows = 8;
    const int columns = 4;
    core::Grid grid(rows, columns);

    std::vector<core::PixmapLayer> allLayers = {
        core::PixmapLayer::GROUND_LAYER,
        core::PixmapLayer::GRASS_LAYER,
        core::PixmapLayer::ROCK_LAYER,
        core::PixmapLayer::WOOD_LAYER,
        core::PixmapLayer::FLOWER_LAYER,
        core::PixmapLayer::SNAKE_LAYER,
        core::PixmapLayer::TREE_LAYER,
        core::PixmapLayer::OVERLAY_LAYER,
        core::PixmapLayer::HUD_LAYER
    };

    std::size_t index1d = 1;

    for (core::PixmapLayer& layer: allLayers) {
        grid.addLayer(index1d, layer);
        QVERIFY(grid.hasLayer(index1d, layer));
    }

    QVERIFY(!grid.isIndexFree(index1d));
    QVERIFY(!grid.isIndexPassable(index1d));

    // remove obsticles one by one
    QVERIFY(grid.removeLayer(index1d, core::PixmapLayer::ROCK_LAYER));
    QVERIFY(!grid.hasLayer(index1d, core::PixmapLayer::ROCK_LAYER));
    QVERIFY(!grid.isIndexFree(index1d));
    QVERIFY(!grid.isIndexPassable(index1d));

    QVERIFY(grid.removeLayer(index1d, core::PixmapLayer::WOOD_LAYER));
    QVERIFY(!grid.hasLayer(index1d, core::PixmapLayer::WOOD_LAYER));
    QVERIFY(!grid.isIndexFree(index1d));
    QVERIFY(!grid.isIndexPassable(index1d));

    QVERIFY(grid.removeLayer(index1d, core::PixmapLayer::SNAKE_LAYER));
    QVERIFY(!grid.hasLayer(index1d, core::PixmapLayer::SNAKE_LAYER));
    QVERIFY(!grid.isIndexFree(index1d));
    QVERIFY(!grid.isIndexPassable(index1d));

    QVERIFY(grid.removeLayer(index1d, core::PixmapLayer::TREE_LAYER));
    QVERIFY(!grid.hasLayer(index1d, core::PixmapLayer::TREE_LAYER));
    QVERIFY(!grid.isIndexFree(index1d));
    QVERIFY(grid.isIndexPassable(index1d)); // index becomes passable here
    // end removing obsticles

    // remove decors one by one
    QVERIFY(grid.removeLayer(index1d, core::PixmapLayer::OVERLAY_LAYER));
    QVERIFY(!grid.hasLayer(index1d, core::PixmapLayer::OVERLAY_LAYER));
    QVERIFY(!grid.isIndexFree(index1d));
    QVERIFY(grid.isIndexPassable(index1d));

    QVERIFY(grid.removeLayer(index1d, core::PixmapLayer::HUD_LAYER));
    QVERIFY(!grid.hasLayer(index1d, core::PixmapLayer::HUD_LAYER));
    QVERIFY(!grid.isIndexFree(index1d));
    QVERIFY(grid.isIndexPassable(index1d));

    QVERIFY(grid.removeLayer(index1d, core::PixmapLayer::FLOWER_LAYER));
    QVERIFY(!grid.hasLayer(index1d, core::PixmapLayer::FLOWER_LAYER));
    QVERIFY(!grid.isIndexFree(index1d));
    QVERIFY(grid.isIndexPassable(index1d));

    QVERIFY(grid.removeLayer(index1d, core::PixmapLayer::GRASS_LAYER));
    QVERIFY(!grid.hasLayer(index1d, core::PixmapLayer::GRASS_LAYER));
    QVERIFY(grid.isIndexFree(index1d)); // index becomes free
    QVERIFY(grid.isIndexPassable(index1d));

    QVERIFY(grid.removeLayer(index1d, core::PixmapLayer::GROUND_LAYER));
    QVERIFY(!grid.hasLayer(index1d, core::PixmapLayer::GROUND_LAYER));
    QVERIFY(grid.isIndexFree(index1d));
    QVERIFY(grid.isIndexPassable(index1d));
}

