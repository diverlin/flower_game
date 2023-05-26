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
    void testGridMultilayer();
};

#endif // GRIDTEST_H
