#ifndef CRYPTO_DH_CONVERTER_H
#define CRYPTO_DH_CONVERTER_H

#include "Crypto/types.h"
#include "Crypto/dh_types.h"
#include "Crypto/longintconverter.h"

namespace Crypto {

  namespace DH {
    
    class Converter
    {
    public:
      static const number_size_t length_length;

      group_t read_group(const byte_t* raw_group, number_size_t length) const;

      number_size_t write_group(const group_t& group, byte_t* raw_group) const;

      number_size_t group_length(const group_t& group) const;

      number_t read_number(const byte_t* raw_number, number_size_t length) const;

      number_size_t write_number(const number_t& number, byte_t* raw_number) const;

      number_size_t number_length(const number_t& number) const;

    protected:
      LongIntConverter m_converter;

      number_size_t read_length(const byte_t* raw_length) const;

      void write_length(number_size_t length, byte_t* raw_length) const;
    };
    
  } // namespace DH

} // namespace Crypto

#endif // CRYPTO_DH_CONVERTER_H
