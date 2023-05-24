#include "gridtest.h"
#include <grid.h>
#include <tilelayer.h>

#include <QTest>

void GridTest::testGrid1D2DIndexConversion()
{
    Grid grid(5, 5);
    QCOMPARE(int(grid.size()), 25);

    size_t index1d = grid.getIndex1D(2,3);
    Index2D index2d = grid.getIndex2D(index1d);
    QCOMPARE(index2d, Index2D(2,3));
}

void GridTest::testGridAddRemoveLayer()
{
    const int rows = 5;
    const int columns = 5;
    Grid grid(rows, columns);
    QCOMPARE(int(grid.size()), rows*columns);

    for (int i=0; i<rows; ++i) {
        for (int j=0; j<rows; ++j) {
            QVERIFY(grid.isIndexFree(Index2D(i, j)));
        }
    }

    // add
    grid.addLayer(2,3,TileLayer::FLOWER_LAYER);
    QVERIFY(!grid.isIndexFree(Index2D(2,3)));

    grid.addLayer(4,4,TileLayer::ROCK_LAYER);
    QVERIFY(!grid.isIndexFree(Index2D(4,4)));

    // remove
    grid.removeLayer(2,3,TileLayer::FLOWER_LAYER);
    QVERIFY(grid.isIndexFree(Index2D(2,3)));

    grid.removeLayer(4,4,TileLayer::ROCK_LAYER);
    QVERIFY(grid.isIndexFree(Index2D(4,4)));
}
