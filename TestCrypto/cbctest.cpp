#include "cbctest.h"
#include "Crypto/aes_encrypter.h"
#include "Crypto/aes_decrypter.h"
#include "Crypto/cbc_encrypter.h"
#include "Crypto/cbc_decrypter.h"
#include <iostream>
#include <QtTest/QTest>
#include <boost/random/uniform_int_distribution.hpp>
#include <boost/random/mersenne_twister.hpp>

using namespace Crypto;
using namespace std;

static void printit(const uchar* bla, ulong length)
{
  static const char hex_chars[17] = "0123456789ABCDEF";
  for (ulong i = 0; i < length; ++i) {
    std::cout << hex_chars[bla[i] >> 4] << hex_chars[bla[i] & 0xF];
  }
  std::cout << std::endl;
}

void CBCTest::test_enc_dec()
{
  string key (16, 0);
  string initial1 (16, 0);
  string initial2 (16, 0);
  mt19937_64 rng;
  uniform_int_distribution<uchar> dist;
  for (uint i = 0; i < 16; ++i) {
    key[i] = dist(rng);
    initial1[i] = initial2[i] = dist(rng);
  }
  ulong plain_length = 1024;
  string plain (plain_length, 0);
  for (uint i = 0; i < plain_length; ++i) {
    plain[i] = dist(rng);
  }
  AES::Encrypter aes_enc (key);
  AES::Decrypter aes_dec (key);
  CBC::Encrypter<AES::Encrypter> enc (aes_enc, initial1);
  CBC::Decrypter<AES::Decrypter> dec (aes_dec, initial2);
  string cipher = enc.encrypt(plain);
  string replain = dec.decrypt(cipher);
  QCOMPARE(replain, plain);
}
