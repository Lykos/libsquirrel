#ifndef CRYPTO_ELGAMAL_TYPES_H
#define CRYPTO_ELGAMAL_TYPES_H

#include "longint.h"

namespace Crypto {

  namespace Elgamal {

    typedef DataStructures::LongInt number_t;

    typedef DataStructures::LongInt exponent_t;

    typedef number_t plain_text_t;

    typedef struct {
      number_t text;
      number_t gen_power;
    } cipher_text_t;

    typedef struct {
      number_t modulus;
      number_t generator;
      number_t gen_power;
    } public_key_t;

    typedef struct {
      number_t modulus;
      number_t generator;
      exponent_t exponent;
    } private_key_t;

    typedef struct {
      public_key_t public_key;
      private_key_t private_key;
    } key_pair_t;

    typedef struct {
      number_t modulus;
      number_t gen_power;
      number_t key_inv;
    } personalized_public_key_t;

  } // namespace Elgamal

} // namespace Crypto

#endif // CRYPTO_ELGAMAL_TYPES_H
