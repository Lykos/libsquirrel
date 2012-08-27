#ifndef CBCTEST_H
#define CBCTEST_H

#include <QObject>

class CBCTest : public QObject
{
  Q_OBJECT

private Q_SLOTS:
  void test_enc_dec();

};

#endif // CBCTEST_H
