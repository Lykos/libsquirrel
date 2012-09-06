#ifndef ARITHMETICHELPERTEST_H
#define ARITHMETICHELPERTEST_H

#include <QObject>

class ArithmeticHelperTest : public QObject
{
  Q_OBJECT

private Q_SLOTS:

  void test_next_pow2();

  void test_prev_pow2();
  
};

#endif // ARITHMETICHELPERTEST_H
