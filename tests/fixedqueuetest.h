#ifndef FIXEDQUEUETEST_H
#define FIXEDQUEUETEST_H

#include <QObject>

class FixedQueueTest : public QObject {
    Q_OBJECT
public:
    FixedQueueTest()=default;
    ~FixedQueueTest()=default;

private slots:
    void testBase();
    void testDescreaseSize();
};

#endif // FIXEDQUEUETEST_H
