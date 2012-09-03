#ifndef CRYPTO_ELGAMAL_CONVERTER_H
#define CRYPTO_ELGAMAL_CONVERTER_H

#include "Crypto/dh_converter.h"
#include "Crypto/elgamal_types.h"
#include <string>

namespace Crypto {

  namespace Elgamal {
    
    class Converter : public Crypto::DH::Converter
    {
    public:
      public_key_t read_public_key(const std::string& raw_key);

      std::string write_public_key(const public_key_t& public_key);

      private_key_t read_private_key(const std::string& raw_private_key);

      std::string write_private_key(const private_key_t& private_key);

    };
    
  } // namespace Elgamal

} // namespace Crypto

#endif // CRYPTO_ELGAMAL_CONVERTER_H
