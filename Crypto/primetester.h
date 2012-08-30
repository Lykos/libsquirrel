#ifndef CRYPTO_PRIMETESTER_H
#define CRYPTO_PRIMETESTER_H

#include "DataStructures/longint.h"
#include "DataStructures/arraylist.h"
#include "Crypto/Crypto_global.h"
#include "DataStructures/uniformlongintdistribution.h"
#include "Crypto/primes.h"
#include "DataStructures/treap.h"
#include <cstring>

namespace Crypto {

  class CRYPTOSHARED_EXPORT PrimeTester
  {
  private:
    std::mt19937_64 m_random_generator; // For security reasons, this generator is only used for the primality test, not for the primes itself.

  public:
    typedef bool (*predicate_t)(const DataStructures::LongInt&);

  // The probability that a non-prime is mistaken for a prime is 2^-security
    template <typename Engine>
    DataStructures::LongInt random_prime(Engine& engine, DataStructures::LongInt min, DataStructures::LongInt max, uint security);

  // The probability that a non-prime is mistaken for a prime is 2^-security
    bool is_prime(const DataStructures::LongInt& number, uint security);

  };

static const ulong SIEVE_RANGE = 1 << 24;
static const DataStructures::LongInt LONGINT_SIEVE_RANGE = SIEVE_RANGE;

  template <typename Engine>
  DataStructures::LongInt PrimeTester::random_prime(Engine& engine, DataStructures::LongInt min, DataStructures::LongInt max, uint security)
  {
    static const DataStructures::LongInt ONE = 1;
    DataStructures::UniformLongIntDistribution point_dist (min, max);
    DataStructures::LongInt candidate;
    bool not_found = true;
    ulong sieve_length = std::min(LONGINT_SIEVE_RANGE, max + ONE - min);
    bool *sieve = new bool[sieve_length];
    while (not_found) {
      // Sample one point in the available range and construct a range of length SIEVE_RANGE (truncate near the ends)
      DataStructures::LongInt point = point_dist(engine);
      DataStructures::LongInt start = std::max(min, point - point % LONGINT_SIEVE_RANGE);
      uint length = std::min(max + ONE - start, LONGINT_SIEVE_RANGE);
      assert(length < sieve_length);
      DataStructures::LongInt number = start;
      for (ulong i = 0; i < length; ++i, ++number) {
        sieve[i] = false;
      }
      for (ulong i = 0; i < N_PRIMES; ++i) {
        ulong prime = FIRST_PRIMES[i];
        ulong j = start.add_inv_mod(prime);
        if (start <= prime) {
          j += prime;
        }
        for (; j < length; j += prime) {
          sieve[j] = true;
        }
      }
      DataStructures::Treap<ulong> prime_candidates;
      for (ulong i = 0; i < length; ++i) {
        if (!sieve[i]) {
          prime_candidates.insert(i);
        }
      }
      while (!prime_candidates.is_empty()) {
        std::uniform_int_distribution<ulong> index_dist (0, prime_candidates.size() - 1);
        ulong i = index_dist(engine);
        ulong offset = prime_candidates[i];
        candidate = start + offset;
        if (is_prime(candidate, security)) {
          not_found = false;
          break;
        } else {
          prime_candidates.remove(offset);
        }
      }
    }
    return candidate;
  }

}

#endif // CRYPTO_PRIMETESTER_H
