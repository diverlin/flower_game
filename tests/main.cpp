#include <QCoreApplication>
#include <QTest>

#include "gridtest.h"
#include "fixedqueuetest.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    int testResult = 0;

    testResult |= QTest::qExec(new GridTest, argc, argv);
    testResult |= QTest::qExec(new FixedQueueTest, argc, argv);

    return testResult;
}
