#include "elgamaltest.h"
#include "Crypto/elgamal_keygenerator.h"
#include "Crypto/elgamal_encrypter.h"
#include "Crypto/elgamal_decrypter.h"
#include "Crypto/elgamal_signer.h"
#include "Crypto/elgamal_verifier.h"
#include "Crypto/dh_constants.h"
#include "Crypto/primetester.h"
#include "DataStructures/uniformlongintdistribution.h"
#include <boost/random/mersenne_twister.hpp>
#include <QtTest/QtTest>
#include <iostream>

using namespace Crypto;
using namespace Elgamal;
using namespace DataStructures;

static void printit(const uchar* bla, ulong length)
{
  static const char hex_chars[17] = "0123456789ABCDEF";
  for (ulong i = 0; i < length; ++i) {
    std::cout << hex_chars[bla[i] >> 4] << hex_chars[bla[i] & 0xF];
  }
  std::cout << std::endl;
}

void ElgamalTest::test_key_generation()
{
  uint key_bits = 1024;
  KeyGenerator key_generator;
  std::mt19937_64 rng;
  key_pair_t key_pair = key_generator.generate(rng, key_bits);
  public_key_t  public_key = key_pair.public_key;
  private_key_t private_key = key_pair.private_key;

  // Check sanity
  QCOMPARE(public_key.modulus, private_key.modulus);
  QCOMPARE(public_key.generator, private_key.generator);
  number_t modulus = public_key.modulus;
  number_t generator = public_key.generator;
  exponent_t exponent = private_key.exponent;
  number_t gen_power = public_key.gen_power;
  QCOMPARE(generator.pow_mod(exponent, modulus), gen_power);

  Encrypter encrypter (public_key);
  Decrypter decrypter (private_key);
  QCOMPARE(encrypter.cipher_block_size(), decrypter.cipher_block_size());
  QCOMPARE(encrypter.plain_block_size(), decrypter.plain_block_size());

  // Check if key is usable for enc/dec.
  std::uniform_int_distribution<unsigned char> dist;
  unsigned char *plain = new unsigned char[encrypter.plain_block_size()];
  unsigned char *cipher = new unsigned char[decrypter.cipher_block_size()];
  unsigned char *replain = new unsigned char[encrypter.plain_block_size()];
  for (uint i = 0; i < encrypter.plain_block_size(); ++i) {
    plain[i] = dist(rng);
  }
  encrypter.encrypt(plain, cipher);
  decrypter.decrypt(cipher, replain);
  for (uint i = 0; i < encrypter.plain_block_size(); ++i) {
    QCOMPARE(plain[i], replain[i]);
  }
  delete[] plain;
  delete[] cipher;
  delete[] replain;

  // Check if key is usable for signatures.
  Signer signer (private_key);
  Verifier verifier (public_key);
  ulong signature_length = signer.signature_length();
  unsigned char *message = new unsigned char[5000 + signature_length];
  for (uint i = 0; i < 5000; ++i) {
    message[i] = dist(rng);
  }
  signer.sign(message, 5000);
  QVERIFY(verifier.verify(message, 5000 + signature_length));
  message[233] = ~message[233];
  QVERIFY(!verifier.verify(message, 5000 + signature_length));
  delete[] message;
}
