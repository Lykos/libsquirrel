#include "dhtest.h"
#include "dh_constants.h"
#include "primetester.h"
#include "longint.h"
#include <QtTest/QTest>

using namespace Crypto;
using namespace DH;
using namespace DataStructures;

void DHTest::test_constants()
{
  PrimeTester tester;
  LongInt moduli[9] = {diffie_hellman_modulus_1024,
                       diffie_hellman_modulus_2048_1,
                       diffie_hellman_modulus_2048_2,
                       diffie_hellman_modulus_2048_3,
                       diffie_hellman_modulus_2560,
                       diffie_hellman_modulus_3072,
                       diffie_hellman_modulus_3584,
                       diffie_hellman_modulus_4096,
                       diffie_hellman_modulus_8192};
  LongInt generators[9] = {diffie_hellman_generator_1024,
                           diffie_hellman_generator_2048_1,
                           diffie_hellman_generator_2048_2,
                           diffie_hellman_generator_2048_3,
                           diffie_hellman_generator_2560,
                           diffie_hellman_generator_3072,
                           diffie_hellman_generator_3584,
                           diffie_hellman_generator_4096,
                           diffie_hellman_generator_8192};
  for (uint i = 0; i < 8; ++i) {
    QVERIFY(tester.is_prime(moduli[i], 1));
    LongInt p = moduli[i] >> 1;
    QVERIFY(tester.is_prime(p, 1));
    LongInt minus_one = moduli[i] - 1;
    QCOMPARE(minus_one, generators[i].pow_mod(p, moduli[i]));
  }
}
