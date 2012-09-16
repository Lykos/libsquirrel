#include "dhtest.h"
#include "Crypto/dh_constants.h"
#include "Crypto/primetester.h"
#include "LongArithmetic/longint.h"
#include <QtTest/QTest>

using namespace Crypto;
using namespace DH;
using namespace LongArithmetic;

void DHTest::test_constants()
{
  PrimeTester tester;
  LongInt moduli[10] = {diffie_hellman_modulus_512,
                        diffie_hellman_modulus_1024,
                        diffie_hellman_modulus_2048_1,
                        diffie_hellman_modulus_2048_2,
                        diffie_hellman_modulus_2048_3,
                        diffie_hellman_modulus_2560,
                        diffie_hellman_modulus_3072,
                        diffie_hellman_modulus_3584,
                        diffie_hellman_modulus_4096,
                        diffie_hellman_modulus_8192};
  LongInt generators[10] = {diffie_hellman_generator_512,
                            diffie_hellman_generator_1024,
                            diffie_hellman_generator_2048_1,
                            diffie_hellman_generator_2048_2,
                            diffie_hellman_generator_2048_3,
                            diffie_hellman_generator_2560,
                            diffie_hellman_generator_3072,
                            diffie_hellman_generator_3584,
                            diffie_hellman_generator_4096,
                            diffie_hellman_generator_8192};
  for (uint i = 0; i < 10; ++i) {
    QVERIFY2(tester.is_prime(moduli[i], 1), "Prime number is not a prime.");
    LongInt p = moduli[i] >> 1;
    QVERIFY2(tester.is_prime(p, 1), "Prime number is not a Sophie Germain prime.");
    LongInt minus_one = moduli[i] - 1;
    QVERIFY2(minus_one == generators[i].pow_mod(p, moduli[i]), "Generator is not a generator.");
  }
}
