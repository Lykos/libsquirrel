#include "rsatest.h"
#include "rsa_keygenerator.h"
#include "rsa_encrypter.h"
#include "rsa_decrypter.h"
#include <QtTest/QtTest>
#include <iostream>

using namespace Crypto::RSA;

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

void RSATest::test_key_generation()
{
  KeyGenerator key_generator;
  key_pair_t key_pair = key_generator.generate(20);
  public_key_t  public_key = key_pair.public_key;
  private_key_t private_key = key_pair.private_key;
  QVERIFY(private_key.p_q_available);
  QCOMPARE(private_key.p * private_key.q, private_key.modulus);
  QCOMPARE(private_key.modulus, public_key.modulus);
  DataStructures::LongInt exponent_product = (private_key.exponent * public_key.exponent) % ((private_key.p - 1) * (private_key.q - 1));
  QCOMPARE(exponent_product, DataStructures::LongInt(1));
  Encrypter encrypter (public_key);
  Decrypter decrypter (private_key);
  plain_text_t plain_text = rand_number(public_key.modulus);
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
