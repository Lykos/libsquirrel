#include "cbctest.h"
#include "aes_encrypter.h"
#include "aes_decrypter.h"
#include "cbc_encrypter.h"
#include "cbc_decrypter.h"
#include <iostream>
#include <QtTest/QTest>
#include <boost/random/uniform_int_distribution.hpp>
#include <boost/random/mersenne_twister.hpp>

using namespace Crypto;
using namespace std;

void printit(const uchar* bla, ulong length)
{
  static const char hex_chars[17] = "0123456789ABCDEF";
  for (ulong i = 0; i < length; ++i) {
    std::cout << hex_chars[bla[i] >> 4] << hex_chars[bla[i] & 0xF];
  }
  std::cout << std::endl;
}

void CBCTest::test_enc_dec()
{
  uchar key[16];
  uchar *initial1 = new uchar[16];
  uchar *initial2 = new uchar[16];
  mt19937_64 rng;
  uniform_int_distribution<uchar> dist;
  for (uint i = 0; i < 16; ++i) {
    key[i] = dist(rng);
    initial1[i] = initial2[i] = dist(rng);
  }
  ulong plain_length = 1024;
  uchar *plain = new uchar[plain_length];
  for (uint i = 0; i < plain_length; ++i) {
    plain[i] = dist(rng);
  }
  AES::Encrypter aes_enc (key, 16);
  AES::Decrypter aes_dec (key, 16);
  CBC::Encrypter<AES::Encrypter> enc (aes_enc, initial1);
  CBC::Decrypter<AES::Decrypter> dec (aes_dec, initial2);
  ulong cipher_length = enc.get_cipher_length(plain_length);
  uchar *cipher = new uchar[cipher_length];
  enc.encrypt(plain, plain_length, cipher);
  uchar *replain = new uchar[dec.max_plain_length(cipher_length)];
  ulong replain_length = dec.decrypt(cipher, cipher_length, replain);
  QCOMPARE(replain_length, plain_length);
  for (uint i = 0; i < plain_length; ++i) {
    QCOMPARE(plain[i], replain[i]);
  }

  delete[] plain;
  delete[] cipher;
  delete[] replain;
}
