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

