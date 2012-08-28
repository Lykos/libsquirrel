#ifndef CRYPTO_ELGAMAL_CONVERTER_H
#define CRYPTO_ELGAMAL_CONVERTER_H

#include "dh_converter.h"
#include "elgamal_types.h"

namespace Crypto {

  namespace Elgamal {
    
    class Converter : public Crypto::DH::Converter
    {
    public:
      public_key_t read_public_key(const elgamal_byte_t* raw_key, number_size_t length);

      number_size_t write_public_key(const public_key_t& public_key, elgamal_byte_t* raw_key);

      number_size_t public_key_length(const public_key_t& public_key) const;

      private_key_t read_private_key(const elgamal_byte_t* raw_key, number_size_t length);

      number_size_t write_private_key(const private_key_t& private_key, elgamal_byte_t* raw_key);

      number_size_t private_key_length(const private_key_t& private_key) const;

    };
    
  } // namespace Elgamal

} // namespace Crypto

#endif // CRYPTO_ELGAMAL_CONVERTER_H
