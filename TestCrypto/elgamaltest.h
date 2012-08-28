#ifndef ELGAMALTEST_H
#define ELGAMALTEST_H

#include <QObject>

class ElgamalTest : public QObject
{
  Q_OBJECT

private Q_SLOTS:
  void test_key_generation();

};

#endif // ELGAMALTEST_H
