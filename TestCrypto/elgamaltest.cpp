#include "elgamaltest.h"
#include "elgamal_keygenerator.h"
#include "elgamal_encrypter.h"
#include "elgamal_decrypter.h"
#include <QtTest/QtTest>
#include <iostream>

using namespace Crypto::Elgamal;
/*
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
}*/
