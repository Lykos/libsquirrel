#ifndef HEAPARITHMETICTEST_H
#define HEAPARITHMETICTEST_H

#include <QObject>

class HeapArithmeticTest : public QObject
{
  Q_OBJECT

private Q_SLOTS:

  void test_parent();

  void test_left_child();

  void test_right_child();

};

#endif // HEAPARITHMETICTEST_H
