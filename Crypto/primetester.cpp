#include "primetester.h"

namespace Crypto {

  DataStructures::LongInt PrimeTester::random_prime(const DataStructures::LongInt& max) const
  {
    DataStructures::LongInt result = 1;
    while (!is_prime(result)) {
      result = rand_number(max);
    }
    return result;
  }

  bool PrimeTester::is_prime(const DataStructures::LongInt& number) const
  {
    if (number <= 1 && number >= -1) {
      return false;
    } else {
      return false;
    }
  }

}
