#ifndef CRYPTO_TYPES_H
#define CRYPTO_TYPES_H

#include "DataStructures/longint.h"
#include <cstdint>

namespace Crypto {

  // Used internally for unsigned raw bytes
  typedef uint8_t byte_t;

  // Used for lengths of internal messages and related things
  typedef uint_fast32_t number_size_t;

  // Used for lengths of payload messages
  typedef uint64_t message_size_t;

  typedef DataStructures::LongInt number_t;

  typedef DataStructures::LongInt exponent_t;

}

#endif // CRYPTO_TYPES_H
