#include <cstdlib>
#include <QtTest>
#include "rsatest.h"
#include "elgamaltest.h"
#include "aestest.h"
#include "cbctest.h"
#include "sha256test.h"
#include "dhtest.h"

int main(int argc, char** argv) {
  AESTest aes_test;
  QTest::qExec(&aes_test, argc, argv);
  CBCTest cbc_test;
  QTest::qExec(&cbc_test, argc, argv);
  SHA256Test sha256_test;
  QTest::qExec(&sha256_test, argc, argv);
  RSATest rsa_test;
  QTest::qExec(&rsa_test, argc, argv);
  ElgamalTest elgamal_test;
  QTest::qExec(&elgamal_test, argc, argv);
  DHTest dh_test;
  QTest::qExec(&dh_test, argc, argv);
  return EXIT_SUCCESS;
}
