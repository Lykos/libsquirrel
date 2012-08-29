#include "rsatest.h"
#include "Crypto/rsa_keygenerator.h"
#include "Crypto/rsa_encrypter.h"
#include "Crypto/rsa_decrypter.h"
#include "DataStructures/uniformlongintdistribution.h"
#include <boost/random/mersenne_twister.hpp>
#include <QtTest/QtTest>
#include <iostream>

using namespace Crypto::RSA;
using namespace DataStructures;

void RSATest::init()
{
  m_public_key.modulus = 3053;
  m_public_key.exponent = 1919;
  m_private_key.modulus = 3053;
  m_private_key.exponent = 239;
  m_private_key.p = 71;
  m_private_key.q = 43;
  m_private_key.p_q_available = true;
  m_plain_text = 1735;
  m_cipher_text = 368;
}

static const DataStructures::LongInt ONE = 1;

void RSATest::test_key_generation()
{
  std::mt19937_64 rng;
  KeyGenerator key_generator;
  key_pair_t key_pair = key_generator.generate(rng, 20);
  public_key_t  public_key = key_pair.public_key;
  private_key_t private_key = key_pair.private_key;
  QVERIFY(private_key.p_q_available);
  QCOMPARE(private_key.p * private_key.q, private_key.modulus);
  QCOMPARE(private_key.modulus, public_key.modulus);
  LongInt exponent_product = (private_key.exponent * public_key.exponent) % ((private_key.p - ONE) * (private_key.q - ONE));
  QCOMPARE(exponent_product, LongInt(1));
  Encrypter encrypter (public_key);
  Decrypter decrypter (private_key);
  UniformLongIntDistribution dist (0, public_key.modulus - ONE);
  plain_text_t plain_text = dist(rng);
  cipher_text_t cipher_text = encrypter.encrypt(plain_text);
  QCOMPARE(decrypter.decrypt(cipher_text), plain_text);
}

void RSATest::test_encrypter()
{
  Encrypter encrypter (m_public_key);
  QCOMPARE(encrypter.encrypt(m_plain_text), m_cipher_text);
}

void RSATest::test_decrypter_pq()
{
  Decrypter decrypter (m_private_key);
  QCOMPARE(decrypter.decrypt(m_cipher_text), m_plain_text);
}

void RSATest::test_decrypter_no_pq()
{
  m_private_key.p_q_available = false;
  Decrypter decrypter (m_private_key);
  QCOMPARE(decrypter.decrypt(m_cipher_text), m_plain_text);
}

void RSATest::test_decrypter_invalid_pq()
{
  m_private_key.p_q_available = false;
  m_private_key.p = 0;
  Decrypter decrypter (m_private_key);
  QCOMPARE(decrypter.decrypt(m_cipher_text), m_plain_text);
}

