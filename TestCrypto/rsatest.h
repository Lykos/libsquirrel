#ifndef TESTRSA_H
#define TESTRSA_H

#include <QObject>
#include "rsa_types.h"

class RSATest : public QObject
{
  Q_OBJECT

private:
  Crypto::RSA::cipher_text_t m_cipher_text;

  Crypto::RSA::plain_text_t m_plain_text;

  Crypto::RSA::public_key_t m_public_key;

  Crypto::RSA::private_key_t m_private_key;

private Q_SLOTS:
  void init();

  void test_key_generation();

  void test_encrypter();

  void test_decrypter_pq();

  void test_decrypter_invalid_pq();

  void test_decrypter_no_pq();

};

#endif // TESTRSA_H
