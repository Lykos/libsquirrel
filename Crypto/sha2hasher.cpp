#include "Crypto/sha2hasher.h"
#include "Crypto/preconditionviolation.h"
#include "Crypto/types.h"
#include <string>
#include <climits>
#include <cassert>

#define shr(x, n) ((x) >> (n))
#define rotr(x, n) (((x) >> (n)) | ((x) << (word_length * CHAR_BIT - (n))))
#define Ch(x, y, z) (((x) & (y)) ^ (~(x) & (z)))
#define Maj(x, y, z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
#define S0(x) (rotr((x), 2) ^ rotr((x), 13) ^ rotr((x), 22))
#define S1(x) (rotr((x), 6) ^ rotr((x), 11) ^ rotr((x), 25))
#define s0(x) (rotr((x), 7) ^ rotr((x), 18) ^ shr((x), 3))
#define s1(x) (rotr((x), 17) ^ rotr((x), 19) ^ shr((x), 10))

using namespace std;

namespace Crypto {

  const static number_size_t n_hash_values = 8;

  typedef u_int32_t sha256_word_t;
  
  const static sha256_word_t initial_hash_values[n_hash_values] = {
    0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a, 0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
  };

  const static number_size_t n_rounds = 64;

  const static sha256_word_t round_constants[n_rounds] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
  };

  const static number_size_t chunk_length = 64;

  const static number_size_t length_length = 8;

  const static number_size_t word_length = sizeof(sha256_word_t);

  const static number_size_t chunk_words = chunk_length / word_length;

  string SHA2Hasher::hash(const string& message) const
  {
    message_size_t message_length = message.length();
    // Pad message such that the length in bytes modulo chunk_length is 0 after we put the length there.
    number_size_t zeroes = ((2 * chunk_length - length_length) - (message_length + 1) % chunk_length) % chunk_length;
    message_size_t whole_length = (length_length + message_length + 1 + zeroes);
    assert(whole_length % chunk_length == 0);
    message_size_t chunks = whole_length / chunk_length;
    string padded_message = message;
    padded_message.push_back(0x80); // A 1 with 7 zeroes
    padded_message.resize(zeroes, 0);
    // Store the length in the last bits in big endian.
    message_size_t length_position = message_length + 1 + zeroes;
    for (number_size_t i = 0; i < length_length; ++i) {
      padded_message[length_position + i] = ((message_length * CHAR_BIT) >> CHAR_BIT * (length_length - 1 - i)) & 0xFF;
    }
    sha256_word_t hash[n_hash_values];
    for (number_size_t i = 0; i < n_hash_values; ++i) {
      hash[i] = initial_hash_values[i];
    }
    for (message_size_t j = 0; j < chunks; ++j) {
      sha256_word_t words[n_rounds];
      for (message_size_t i = 0; i < chunk_words; ++i) {
        words[i] = (padded_message[j * chunk_length + word_length * i] << 3 * CHAR_BIT)
            + (padded_message[j * chunk_length + word_length * i + 1] << 2 * CHAR_BIT)
            + (padded_message[j * chunk_length + word_length * i + 2] << CHAR_BIT)
            + (padded_message[j * chunk_length + word_length * i + 3]);
      }
      for (message_size_t i = chunk_words; i < n_rounds; ++i) {
        words[i] = words[i - 16] + s0(words[i - 15]) + words[i - 7] + s1(words[i - 2]);
      }
      sha256_word_t a = hash[0];
      sha256_word_t b = hash[1];
      sha256_word_t c = hash[2];
      sha256_word_t d = hash[3];
      sha256_word_t e = hash[4];
      sha256_word_t f = hash[5];
      sha256_word_t g = hash[6];
      sha256_word_t h = hash[7];
      for (number_size_t i = 0; i < n_rounds; ++i) {
        sha256_word_t t1 = h + S1(e) + Ch(e, f, g) + round_constants[i] + words[i];
        sha256_word_t t2 = S0(a) + Maj(a, b, c);

        h = g;
        g = f;
        f = e;
        e = d + t1;
        d = c;
        c = b;
        b = a;
        a = t1 + t2;
      }
      hash[0] += a;
      hash[1] += b;
      hash[2] += c;
      hash[3] += d;
      hash[4] += e;
      hash[5] += f;
      hash[6] += g;
      hash[7] += h;
    }
    string digest;
    for (number_size_t i = 0; i < n_hash_values; ++i) {
      for (number_size_t j = 0; j < word_length; ++j) {
        digest.push_back((hash[i] >> (word_length - 1 - j) * CHAR_BIT) & 0xFF);
      }
    }
    return digest;
  }
  
} // namespace Crypto
