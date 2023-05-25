#include "fixedqueuetest.h"
#include <fixedqueue.h>

#include <QTest>

QString intQueueToString(const core::FixedQueue<int>& q)
{
    QString buff;
    for (int el: q) {
        buff += QString::number(el);
    }
    return buff;
}

void FixedQueueTest::testBase()
{
    core::FixedQueue<int> q(5);
    q.push(1);
    q.push(2);
    q.push(3);

    QCOMPARE(q.size(), 3);

    q.push(4);
    q.push(5);

    QCOMPARE(q.size(), 5);

    q.push(6);

    QCOMPARE(q.size(), 5);

    QCOMPARE(intQueueToString(q), "65432");

    q.push(7);
    QCOMPARE(q.size(), 5);

    QCOMPARE(intQueueToString(q), "76543");

    q.setMaxLength(2);
    QCOMPARE(intQueueToString(q), "76");
}
