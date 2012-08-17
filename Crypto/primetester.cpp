#include "primetester.h"

namespace Crypto {

  static const DataStructures::LongInt FIRST_PRIMES[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 57, 61, 67, 71, 73, 79, 83, 89, 91, 93, 97};

  DataStructures::LongInt PrimeTester::random_prime(DataStructures::index_type number_bits) const
  {
    DataStructures::LongInt result = 1;
    while (!is_prime(result)) {
      result = DataStructures::rand_bits(number_bits);
    }
    return result;
  }

  bool PrimeTester::is_prime(const DataStructures::LongInt& number) const
  {
    assert(number >= 0 && number < 100);
    // TODO real primality testing
    if (number <= 1 && number >= -1) {
      return false;
    } else {
      return std::binary_search(FIRST_PRIMES + 0, FIRST_PRIMES + 27, number);
    }
  }

}
