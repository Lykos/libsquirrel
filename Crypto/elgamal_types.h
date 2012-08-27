#ifndef CRYPTO_ELGAMAL_TYPES_H
#define CRYPTO_ELGAMAL_TYPES_H

#include "keypair.h"
#include "longint.h"

namespace Crypto {

  namespace Elgamal {

    typedef DataStructures::LongInt number_t;

    typedef DataStructures::LongInt exponent_t;

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

    typedef u_int8_t elgamal_byte_t;

    typedef KeyPair<public_key_t, private_key_t> key_pair_t;

  } // namespace Elgamal

} // namespace Crypto

#endif // CRYPTO_ELGAMAL_TYPES_H
