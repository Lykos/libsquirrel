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
#include <iomanip>

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

static const uint key_bits = 512;

void ElgamalTest::initTestCase()
{
  m_modulus = DH::diffie_hellman_modulus_512;
  m_generator = DH::diffie_hellman_generator_512;
  m_gen_power = LongInt("0x9BC63C0647405350B82E33E795F9D03981E95D3587902E94B91E798DC12C11939F45A1F3FCF760FCC4C367BBF81ACFC422678A61BAD3F6C0BC88BFD5887B6D");
  m_exponent = LongInt("0x502EE589D30277A596A9ADBFADAB77A7869A6EBB124938768803BE95099DC9804EF4A9A7CA034E1D0146C76507F1A2B3E9734EA54370BA34C7FAE9802762FAC8");
  QCOMPARE(m_generator.pow_mod(m_exponent, m_modulus), m_gen_power);
  m_public_key = {m_modulus, m_generator, m_gen_power};
  m_private_key = {m_modulus, m_generator, m_exponent};
}

void ElgamalTest::test_key_generation()
{
  uint key_bits = 512;
  KeyGenerator key_generator;
  key_pair_t key_pair = key_generator.generate(m_random_generator, key_bits);
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
  QVERIFY(encrypter.plain_block_size() <= decrypter.plain_block_size());

  // Check if key is usable for enc/dec.
  LongInt plain = LongInt("0x2323432982978429823239823");
  Encrypter::cipher_t cipher = encrypter.encrypt(plain);
  LongInt replain = decrypter.decrypt(cipher.cipher, cipher.gen_power);
  QCOMPARE(replain, plain);
}

void ElgamalTest::test_enc_dec()
{
  Encrypter encrypter (m_public_key);
  Decrypter decrypter (m_private_key);
  UniformLongIntDistribution dist (0, m_modulus);
  LongInt plain = dist(m_random_generator);
  Encrypter::cipher_t cipher = encrypter.encrypt(plain);
  LongInt replain = decrypter.decrypt(cipher.cipher, cipher.gen_power);
  QCOMPARE(replain, plain);
}

void ElgamalTest::test_enc_dec_char()
{
  Encrypter encrypter (m_public_key);
  Decrypter decrypter (m_private_key);
  boost::random::uniform_int_distribution<unsigned char> dist;
  unsigned char *plain = new unsigned char[encrypter.plain_block_size()];
  unsigned char *cipher = new unsigned char[decrypter.cipher_block_size()];
  unsigned char *replain = new unsigned char[encrypter.plain_block_size()];
  for (uint i = 0; i < encrypter.plain_block_size(); ++i) {
    plain[i] = dist(m_random_generator);
  }
  encrypter.encrypt(plain, cipher);
  decrypter.decrypt(cipher, replain);
  for (uint i = 0; i < encrypter.plain_block_size(); ++i) {
    QCOMPARE(plain[i], replain[i]);
  }
  delete[] plain;
  delete[] cipher;
  delete[] replain;
}

void ElgamalTest::test_sign()
{
  Signer signer (m_private_key);
  Verifier verifier (m_public_key);
  UniformLongIntDistribution dist (0, m_modulus);
  LongInt message = dist(m_random_generator);
  Signer::signature_t signature = signer.sign(message);
  QVERIFY(verifier.verify(message, signature.r, signature.s));
  signature.r = (signature.r * 5) % m_modulus;
  QVERIFY(!verifier.verify(message, signature.r, signature.s));
}

void ElgamalTest::test_sign_char()
{
  Signer signer (m_private_key);
  Verifier verifier (m_public_key);
  boost::random::uniform_int_distribution<unsigned char> dist;
  ulong signature_length = signer.signature_length();
  unsigned char *message = new unsigned char[5000 + signature_length];
  for (uint i = 0; i < 5000; ++i) {
    message[i] = dist(m_random_generator);
  }
  signer.sign(message, 5000);
  QVERIFY(verifier.verify(message, 5000 + signature_length));
  message[233] = ~message[233];
  QVERIFY(!verifier.verify(message, 5000 + signature_length));
  delete[] message;
}
