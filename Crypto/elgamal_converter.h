#ifndef CRYPTO_ELGAMAL_CONVERTER_H
#define CRYPTO_ELGAMAL_CONVERTER_H

#include "elgamal_types.h"
#include "longintconverter.h"

namespace Crypto {

  namespace Elgamal {
    
    class Converter
    {
    public:
      typedef u_int32_t number_size_t;

      public_key_t read_public_key(const elgamal_byte_t* raw_key, number_size_t length);

      number_size_t write_public_key(const public_key_t& public_key, elgamal_byte_t* raw_key);

      number_size_t public_key_length(const public_key_t& public_key) const;

      private_key_t read_private_key(const elgamal_byte_t* raw_key, number_size_t length);

      number_size_t write_private_key(const private_key_t& private_key, elgamal_byte_t* raw_key);

      number_size_t private_key_length(const private_key_t& private_key) const;

      group_t read_group(const elgamal_byte_t* raw_group, number_size_t length);

      number_size_t write_group(const group_t& group, elgamal_byte_t* raw_group);

      number_size_t group_length(const group_t& group) const;

      number_t read_number(const elgamal_byte_t* raw_number, number_size_t length);

      number_size_t write_number(const number_t& number, elgamal_byte_t* raw_number);

      number_size_t number_length(const number_t& number) const;

    private:
      LongIntConverter m_converter;

      number_size_t read_length(const elgamal_byte_t* raw_length);

      void write_length(number_size_t length, elgamal_byte_t* raw_length);
    };
    
  } // namespace Elgamal

} // namespace Crypto

#endif // CRYPTO_ELGAMAL_CONVERTER_H
