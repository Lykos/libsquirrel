#include "longintconverter.h"

namespace DataStructures {
  
  LongIntConverter::LongIntConverter()
  {
  }

  /*
  LongInt::LongInt(const packed_longint_t& packed):
    m_positive (packed.sign),
    m_content (packed.num_parts / 2 + packed.num_parts % 2, 0)
  {
    size_type i = 0;
    for (; i < packed.num_parts / 2; ++i) {
      assert(i < size());
      m_content[i] = packed.parts[2 * i] + (part_type(packed.parts[2 * i + 1]) << (PART_SIZE / 2));
    }
    if (2 * i < packed.num_parts) {
      assert(i < size());
      m_content[i] = packed.parts[2 * i];
    }
    remove_zeros();
  }

  LongInt::LongInt(const u_int8_t* parts, size_type length):
    m_positive (true),
    m_content (length / sizeof(part_type) + 1, 0)
  {
    for (size_type i = 0; i < length; ++i) {
      part_type c = parts[length - 1 - i];
      m_content[i / sizeof(part_type)] |= c << CHAR_BIT * (i % sizeof(part_type));
    }
    remove_zeros();
  }


  LongInt::size_type LongInt::write(u_int8_t* dest) const throw()
  {
    size_type length = byte_size();
    part_type first_digit = m_content[size() - 1];
    size_type first_length = log2(first_digit) / CHAR_BIT + 1;
    assert(first_length + sizeof(part_type) * (size() - 1) == length);
    for (uint i = 0; i < first_length; ++i) {
      dest[i] = (first_digit >> (first_length - i - 1) * CHAR_BIT) & 0xFF;
    }
    for (size_type i = 0; i < size() - 1; ++i) {
      for (uint j = 0; j < sizeof(part_type); ++j) {
        dest[first_length + sizeof(part_type) * i + j] = (m_content[size() - i - 2] >> (sizeof(part_type) - j - 1) * CHAR_BIT) & 0xFF;
      }
    }
    return length;
  }

  LongInt::packed_longint_t LongInt::pack() const
  {
    unsigned int* result = new unsigned int[size() * 2];
    for (size_type i = 0; i < size(); ++i) {
      result[2 * i] = (unsigned int)(m_content[i]);
      result[2 * i + 1] = (unsigned int)(m_content[i] >> (PART_SIZE / 2));
    }
    return {result, size() * 2, m_positive};
  }
  */
} // namespace DataStructures
