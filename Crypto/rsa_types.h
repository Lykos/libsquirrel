#ifndef RSATYPES_H
#define RSATYPES_H

#include "longint.h"

namespace Crypto {

  namespace RSA {

    typedef DataStructures::LongInt number_t;

    typedef DataStructures::index_type exponent_t;

    typedef number_t plain_text_t;

    typedef number_t cipher_text_t;

    typedef struct {
      number_t modulus;
      exponent_t exponent;
    } public_key_t;

    typedef struct {
      number_t modulus;
      exponent_t exponent;
      number_t p;
      number_t q;
      bool p_q_available;
    } private_key_t;

    typedef std::pair<public_key_t, private_key_t> key_pair_t;

  }

}

#endif // RSATYPES_H
