#include "elgamal_keygenerator.h"

namespace Crypto {

  namespace Elgamal {

    group_t KeyGenerator::choose_group(number_size_t number_bits)
    {
      return DH::KeyGenerator::choose_group(number_bits);
    }

  }

}
