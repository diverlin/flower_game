#include <QCoreApplication>
#include <QTest>

#include "gridtest.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    int testResult = 0;

    testResult |= QTest::qExec(new GridTest, argc, argv);

    return testResult;
}
