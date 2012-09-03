#ifndef CRYPTO_DH_TYPES_H
#define CRYPTO_DH_TYPES_H

#include "Crypto/types.h"

namespace Crypto {

  namespace DH {

    typedef struct {
      number_t modulus;
      number_t generator;
    } group_t;

    typedef struct {
      number_t gen_power;
      exponent_t exponent;
    } partial_key_pair_t;

  } // namespace DH

} // namespace Crypto

#endif // CRYPTO_DH_TYPES_H
