#include "elgamaltest.h"
#include "elgamal_keygenerator.h"
#include "elgamal_encrypter.h"
#include "elgamal_decrypter.h"
#include "elgamal_keypersonalizer.h"
#include <QtTest/QtTest>
#include <iostream>

using namespace Crypto::Elgamal;

void ElgamalTest::init()
{
  m_public_key.modulus = 83;
  m_public_key.generator = 55;
  m_public_key.gen_power = 32;
  m_private_key.modulus = 83;
  m_private_key.generator = 55;
  m_private_key.exponent = 21;
  m_personalized_public_key.modulus = 83;
  m_personalized_public_key.gen_power = 69;
  m_personalized_public_key.key_inv = 49;
  m_plain_text = 27;
  m_cipher_text = {78, 69};
}

void ElgamalTest::test_key_generation()
{
  KeyGenerator key_generator;
  key_pair_t key_pair = key_generator.generate(6);
  public_key_t  public_key = key_pair.public_key;
  private_key_t private_key = key_pair.private_key;
  QCOMPARE(public_key.modulus, private_key.modulus);
  QCOMPARE(public_key.generator, private_key.generator);
  number_t modulus = public_key.modulus;
  number_t generator = public_key.generator;
  exponent_t exponent = private_key.exponent;
  number_t gen_power = public_key.gen_power;
  QCOMPARE(generator.pow_mod(exponent, modulus), gen_power);
  Encrypter encrypter (public_key);
  Decrypter decrypter (private_key);
  plain_text_t plain_text = rand_number(public_key.modulus);
  cipher_text_t cipher_text = encrypter.encrypt(plain_text);
  QCOMPARE(decrypter.decrypt(cipher_text), plain_text);
}

void ElgamalTest::test_encrypter()
{
  Encrypter encrypter (m_personalized_public_key);
  cipher_text_t cipher_text = encrypter.encrypt(m_plain_text);
  QCOMPARE(cipher_text.text, m_cipher_text.text);
  QCOMPARE(cipher_text.gen_power, m_cipher_text.gen_power);
}

void ElgamalTest::test_decrypter()
{
  Decrypter decrypter (m_private_key);
  QCOMPARE(decrypter.decrypt(m_cipher_text), m_plain_text);
}

void ElgamalTest::test_personalizer()
{
  static const DataStructures::LongInt ONE (1);
  KeyPersonalizer personalizer;
  personalized_public_key_t personalized_public_key = personalizer.personalize_key(m_public_key);
  number_t modulus = personalized_public_key.modulus;
  number_t key_inv = personalized_public_key.key_inv;
  number_t key = personalized_public_key.gen_power.pow_mod(m_private_key.exponent, modulus);
  QCOMPARE(modulus, m_public_key.modulus);
  QCOMPARE((key * key_inv) % modulus, ONE);
}
