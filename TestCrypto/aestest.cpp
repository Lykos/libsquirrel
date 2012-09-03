#include "aestest.h"
#include "Crypto/aes_encrypter.h"
#include "Crypto/aes_decrypter.h"
#include "Crypto/conditiontype.h"
#include "Crypto/preconditionviolation.h"
#include <iostream>
#include <QtTest/QTest>
#include <string>

using namespace std;
using namespace Crypto;
using namespace AES;

void AESTest::test_enc_dec()
{
  string plain = "Halli hallo.";
  string key ({char(0x12), char(0x23), char(0x53), char(0x43), char(0x32), char(0x34), char(0x34), char(0x43),
              char(0x43), char(0x45), char(0xFF), char(0xFE), char(0xAB), char(0xAD), char(0xCC), char(0xAA)});
  Encrypter enc (key);
  string cipher = enc.encrypt(plain);
  Decrypter dec (key);
  string replain = dec.decrypt(cipher);
  QCOMPARE(replain, plain);
}

void AESTest::test_exception()
{
  string key = "as";
  try {
    Encrypter enc (key);
    QFAIL("No exception after invalid key length.");
  } catch (PreconditionViolation &e) {
    QCOMPARE(e.get_type(), ConditionType::KeyLength);
  }
}
