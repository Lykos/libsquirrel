#include "aestest.h"
#include "aes_encrypter.h"
#include "aes_decrypter.h"
#include <iostream>
#include <QtTest/QTest>

using namespace Crypto::AES;

void AESTest::test_enc_dec()
{
  char plain[16] = "Halli hallo.";
  char cipher[16];
  char replain[16];
  char key[16];
  Encrypter enc (key, 16);
  enc.encrypt(plain + 0, cipher + 0);
  Decrypter dec (key, 16);
  dec.decrypt(cipher, replain);
  for (uint i = 0; i < 16; ++i) {
    QCOMPARE(plain[i], replain[i]);
  }
}
