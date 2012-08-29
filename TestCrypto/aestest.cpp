#include "aestest.h"
#include "Crypto/aes_encrypter.h"
#include "Crypto/aes_decrypter.h"
#include "Crypto/preconditionviolation.h"
#include <iostream>
#include <QtTest/QTest>

using namespace Crypto;
using namespace AES;

void AESTest::test_enc_dec()
{
  uchar plain[16] = "Halli hallo.";
  uchar cipher[16];
  uchar replain[16];
  uchar key[16];
  Encrypter enc (key, 16);
  enc.encrypt(plain + 0, cipher + 0);
  Decrypter dec (key, 16);
  dec.decrypt(cipher, replain);
  for (uint i = 0; i < 16; ++i) {
    QCOMPARE(plain[i], replain[i]);
  }
}

void AESTest::test_exception()
{
  uchar key[3] = "as";
  try {
    Encrypter enc (key, 3);
    QFAIL("No exception after invalid key length.");
  } catch (PreconditionViolation &e) {
    QCOMPARE(e.get_type(), PreconditionViolation::ConditionType::KeyLength);
  }
}
