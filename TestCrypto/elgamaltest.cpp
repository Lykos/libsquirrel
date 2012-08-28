#include "elgamaltest.h"
#include "elgamal_keygenerator.h"
#include "elgamal_encrypter.h"
#include "elgamal_decrypter.h"
#include "elgamal_constants.h"
#include "elgamal_signer.h"
#include "elgamal_verifier.h"
#include "primetester.h"
#include "uniformlongintdistribution.h"
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
  unsigned char *message = new unsigned char[5000];
  for (uint i = 0; i < 5000; ++i) {
    message[i] = dist(rng);
  }
  unsigned char *signature = new unsigned char[signer.signature_length()];
  signer.sign(message, 5000, signature);
  QVERIFY(verifier.verify(message, 5000, signature));
  SHA256Hasher hasher;
  uchar digest1[hasher.digest_length()];
  uchar digest2[hasher.digest_length()];
  message[233] = ~message[233];
  QVERIFY(!verifier.verify(message, 5000, signature));
  delete[] message;
  delete[] signature;
}

void ElgamalTest::test_constants()
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
