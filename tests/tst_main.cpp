#include <QTest>
#include <QObject>

class TestMain : public QObject
{
    Q_OBJECT
private slots:
    void initTestCase()
    {
        // Called before the first test function is executed
    }

    void cleanupTestCase()
    {
        // Called after the last test function is executed
    }

    void testDummy()
    {
        QVERIFY(true);
    }
};

QTEST_MAIN(TestMain)
#include "tst_main.moc"
