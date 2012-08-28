#ifndef CRYPTO_DH_TYPES_H
#define CRYPTO_DH_TYPES_H

#include "longint.h"

namespace Crypto {

  namespace DH {

    typedef DataStructures::LongInt number_t;

    typedef DataStructures::LongInt exponent_t;

    typedef struct {
      number_t modulus;
      number_t generator;
    } group_t;

    typedef struct {
      number_t gen_power;
      exponent_t exponent;
    } partial_key_pair_t;

    typedef u_int8_t dh_byte_t;

  } // namespace DH

} // namespace Crypto

#endif // CRYPTO_DH_TYPES_H
