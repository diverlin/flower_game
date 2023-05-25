#ifndef GRIDTEST_H
#define GRIDTEST_H

#include <QObject>

class GridTest : public QObject {
    Q_OBJECT
public:
    GridTest()=default;
    ~GridTest()=default;

private slots:
    void testGrid1D2DIndexConversion();
    void testGridAddRemoveLayer();
    void testGridFreeRandomIndex();
};

#endif // GRIDTEST_H
