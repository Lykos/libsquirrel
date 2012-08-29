#ifndef AESTEST_H
#define AESTEST_H

#include <QObject>

class AESTest : public QObject
{
  Q_OBJECT

private Q_SLOTS:
  void test_enc_dec();

  void test_exception();

};

#endif // AESTEST_H
