#include <QString>
#include <QtTest>

class PerformanceCryptoTest : public QObject
{
  Q_OBJECT
  
public:
  PerformanceCryptoTest();
  
private Q_SLOTS:
  void testCase1();
};

PerformanceCryptoTest::PerformanceCryptoTest()
{
}

void PerformanceCryptoTest::testCase1()
{
  QBENCHMARK {
    int a = 2;
  }
}

QTEST_APPLESS_MAIN(PerformanceCryptoTest)

#include "tst_performancecryptotest.moc"
