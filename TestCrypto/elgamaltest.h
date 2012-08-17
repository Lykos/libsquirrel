#ifndef ELGAMALTEST_H
#define ELGAMALTEST_H

#include <QObject>
#include "elgamal_types.h"

class ElgamalTest : public QObject
{
  Q_OBJECT

private:
  Crypto::Elgamal::cipher_text_t m_cipher_text;

  Crypto::Elgamal::plain_text_t m_plain_text;

  Crypto::Elgamal::public_key_t m_public_key;

  Crypto::Elgamal::personalized_public_key_t m_personalized_public_key;

  Crypto::Elgamal::private_key_t m_private_key;

private Q_SLOTS:
  void init();

  void test_key_generation();

  void test_encrypter();

  void test_decrypter();

  void test_personalizer();

};

#endif // ELGAMALTEST_H
