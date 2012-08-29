#ifndef ELGAMALTEST_H
#define ELGAMALTEST_H

#include <QObject>
#include "Crypto/elgamal_types.h"

class ElgamalTest : public QObject
{
  Q_OBJECT

private Q_SLOTS:
  void initTestCase();

  void test_key_generation();

  void test_enc_dec();

  void test_enc_dec_char();

  void test_sign();

  void test_sign_char();

private:
  DataStructures::LongInt m_modulus, m_generator, m_gen_power, m_exponent;
  Crypto::Elgamal::public_key_t m_public_key;
  Crypto::Elgamal::private_key_t m_private_key;
  std::mt19937_64 m_random_generator;

};

#endif // ELGAMALTEST_H
