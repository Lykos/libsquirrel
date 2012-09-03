#ifndef CRYPTO_DH_CONVERTER_H
#define CRYPTO_DH_CONVERTER_H

#include "types.h"
#include "dh_types.h"
#include "longintconverter.h"

namespace Crypto {

  namespace DH {
    
    class Converter
    {
    public:
      static const number_size_t length_length;

      group_t read_group(const std::string& raw_group) const;

      std::string write_group(const group_t& group) const;

      number_t read_number(const std::string& raw_number) const;

      std::string write_number(const number_t& number) const;

    protected:
      LongIntConverter m_converter;

      number_size_t read_length(const std::string& raw_length) const;

      std::string write_length(number_size_t length) const;
    };
    
  } // namespace DH

} // namespace Crypto

#endif // CRYPTO_DH_CONVERTER_H
