#ifndef DATASTRUCTURES_LONGINTCONVERTER_H
#define DATASTRUCTURES_LONGINTCONVERTER_H

#include "longint.h"
#include <string>

namespace DataStructures {
  
  class LongIntConverter
  {
  public:
    typedef LongInt::size_type size_type;

    static size_type byte_size(const LongInt& number);

    static LongIntConverter::size_type part_size(size_type bytes);

    // Uses big endian format and no sign
    LongInt binread(const std::string& text) const;

    // Uses big endian format and no sign
    std::string binwrite(const LongInt& number) const;

    // Uses big endian format and no sign, pad zeroes at beginning to achieve size.
    std::string binwrite(const LongInt& number, size_type size) const;

    // Is used to represent the number in 1 complement big endian format, T should be a primitive integral type.
    template <typename T>
    struct packed_longint {
      bool positive;
      size_type size;
      T* parts;
    };

    template <typename T>
    LongInt unpack(const packed_longint<T>& packed) const;

    template <typename T>
    packed_longint<T> pack(const LongInt& packed) const;

  private:
    typedef LongInt::part_type part_type;

  };

} // namespace DataStructures

#endif // DATASTRUCTURES_LONGINTCONVERTER_H
