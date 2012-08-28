#ifndef DHTEST_H
#define DHTEST_H

#include <QObject>

class DHTest : public QObject
{
  Q_OBJECT

private Q_SLOTS:
  void test_constants();

};

#endif // DHTEST_H
