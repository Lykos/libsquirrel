#ifndef CRYPTO_DH_CONVERTER_H
#define CRYPTO_DH_CONVERTER_H

#include "Crypto/dh_types.h"
#include "Crypto/longintconverter.h"

namespace Crypto {

  namespace DH {
    
    class Converter
    {
    public:
      typedef LongIntConverter::number_size_t number_size_t;

      static const number_size_t length_length;

      group_t read_group(const dh_byte_t* raw_group, number_size_t length) const;

      number_size_t write_group(const group_t& group, dh_byte_t* raw_group) const;

      number_size_t group_length(const group_t& group) const;

      number_t read_number(const dh_byte_t* raw_number, number_size_t length) const;

      number_size_t write_number(const number_t& number, dh_byte_t* raw_number) const;

      number_size_t number_length(const number_t& number) const;

    protected:
      LongIntConverter m_converter;

      number_size_t read_length(const dh_byte_t* raw_length) const;

      void write_length(number_size_t length, dh_byte_t* raw_length) const;
    };
    
  } // namespace DH

} // namespace Crypto

#endif // CRYPTO_DH_CONVERTER_H
