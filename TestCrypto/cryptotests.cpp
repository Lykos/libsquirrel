#include <cstdlib>
#include <QtTest>
#include "rsatest.h"
#include "elgamaltest.h"
#include "aestest.h"

int main(int argc, char** argv) {
  RSATest rsa_test;
  QTest::qExec(&rsa_test, argc, argv);
  ElgamalTest elgamal_test;
  QTest::qExec(&elgamal_test, argc, argv);
  AESTest aes_test;
  QTest::qExec(&aes_test, argc, argv);
  return EXIT_SUCCESS;
}
