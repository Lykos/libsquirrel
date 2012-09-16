#ifndef CRYPTO_PRIMETESTER_H
#define CRYPTO_PRIMETESTER_H

#include "LongArithmetic/longint.h"
#include "DataStructures/arraylist.h"
#include "LongArithmetic/uniformlongintdistribution.h"
#include "primes.h"
#include "DataStructures/treap.h"

namespace Crypto {

  class PrimeTester
  {
  public:
  // The probability that a non-prime is mistaken for a prime is 2^-security
    template <typename Engine>
    LongArithmetic::LongInt random_prime(Engine& engine, LongArithmetic::LongInt min, LongArithmetic::LongInt max, number_size_t security);

  // The probability that a non-prime is mistaken for a prime is 2^-security
    bool is_prime(const LongArithmetic::LongInt& number, number_size_t security);

  private:
    // For security reasons, this generator is only used for the primality test, not to choose the primes itself.
    std::mt19937_64 m_random_generator;

  };

static const ulong SIEVE_RANGE = 1 << 24;
static const LongArithmetic::LongInt LONGINT_SIEVE_RANGE = SIEVE_RANGE;

  template <typename Engine>
  LongArithmetic::LongInt PrimeTester::random_prime(Engine& engine, LongArithmetic::LongInt min, LongArithmetic::LongInt max, number_size_t security)
  {
    static const LongArithmetic::LongInt ONE = 1;
    LongArithmetic::UniformLongIntDistribution point_dist (min, max);
    LongArithmetic::LongInt candidate;
    bool not_found = true;
    ulong sieve_length = std::min(LONGINT_SIEVE_RANGE, max + ONE - min);
    bool *sieve = new bool[sieve_length];
    while (not_found) {
      // Sample one point in the available range and construct a range of length SIEVE_RANGE (truncate near the ends)
      LongArithmetic::LongInt point = point_dist(engine);
      LongArithmetic::LongInt start = std::max(min, point - point % LONGINT_SIEVE_RANGE);
      number_size_t length = std::min(max + ONE - start, LONGINT_SIEVE_RANGE);
      assert(length <= sieve_length);
      LongArithmetic::LongInt number = start;
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
