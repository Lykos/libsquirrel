#ifndef CRYPTO_ELGAMAL_TYPES_H
#define CRYPTO_ELGAMAL_TYPES_H

#include "types.h"
#include "dh_types.h"
#include "keypair.h"

namespace Crypto {

  namespace Elgamal {

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

    typedef DH::group_t group_t;

    typedef KeyPair<public_key_t, private_key_t> key_pair_t;

  } // namespace Elgamal

} // namespace Crypto

#endif // CRYPTO_ELGAMAL_TYPES_H
