#ifndef LONGARITHMETIC_LONGINTCONVERTER_H
#define LONGARITHMETIC_LONGINTCONVERTER_H

#include "longint.h"
#include <string>
#include <gmpxx.h>

namespace LongArithmetic {
  
  class LongIntConverter
  {
  public:
    typedef LongInt::size_type size_type;

    static size_type byte_size(const LongInt& number);

    static LongIntConverter::size_type part_size(size_type bytes);

    /**
     * This interprets the input string as a byte array in big endian format and creates
     * a positive number consisting of those bytes.
     *
     * @brief binread Reads a number from a binary string in big endian format.
     * @param text
     * @return
     */
    LongInt binread(const std::string& text) const;

    /**
     * @brief binwrite Writes a number to a binary string without sign in big endian format.
     * @param number
     * @return
     */
    std::string binwrite(const LongInt& number) const;

    // Uses big endian format and no sign, pad zeroes at beginning to achieve size.
    std::string binwrite(const LongInt& number, size_type size) const;

    template <typename T>
    /**
     * Is used to represent the number in 1 complement big endian format, T should be a primitive integral type.
     * @brief The packed_longint struct represents a number in 1 complement big endian format.
     */
    struct packed_longint {
      bool positive;
      size_type size;
      T* parts;
    };

    template <typename T>
    /**
     * @brief unpack
     * @param packed
     * @return
     */
    LongInt unpack(const packed_longint<T>& packed) const;

    template <typename T>
    /**
     * @brief pack
     * @param packed
     * @return
     */
    packed_longint<T> pack(const LongInt& packed) const;

    /**
     * @brief from_mpz sonverts a gnu mpz integer into a LongInt
     * @param number
     * @return
     */
    LongInt from_mpz(const mpz_class& number) const;

    /**
     * @brief to_mpz converts a LongInt into a gnu mpz integer.
     * @param number
     * @return
     */
    mpz_class to_mpz(const LongInt& number) const;

  private:
    typedef LongInt::part_type part_type;

  };

} // namespace LongArithmetic

#endif // LONGARITHMETIC_LONGINTCONVERTER_H
