#include "sha256hasher.h"
#include "string.h"
#include <climits>
#include <cassert>

// This should only be used for sha256_word_t, in particular, it should be unsigned.
#define right_rotate(number, bits) (((number) >> (bits)) | ((number) << ((word_length) * byte_length - (bits))))

namespace Crypto {

  const static uint n_hash_values = 8;

  typedef u_int32_t sha256_word_t;
  
  const static sha256_word_t initial_hash_values[n_hash_values] = {
    0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a, 0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
  };

  const static uint n_rounds = 64;

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

  const static uint chunk_length = 64;

  const static uint length_length = 8;

  const static uint word_length = sizeof(sha256_word_t);

  const static uint byte_length = 8;

  const static uint chunk_words = chunk_length / word_length;

  void SHA256Hasher::hash(const sha256_byte_t* message, ulong message_length, sha256_byte_t* digest)
  {
    // Pad message such that the length in bytes modulo 64 is 0 after we put the length there.
    uint zeroes = ((2 * chunk_length - length_length) - (message_length + 1) % 64) % 64;
    uint whole_length = (length_length + message_length + 1 + zeroes);
    assert(whole_length % chunk_length == 0);
    uint chunks = whole_length / chunk_length;
    char message2[whole_length];
    memcpy(message2, message, message_length);
    message2[message_length] = 0x80; // A 1 with 7 zeroes
    memset(message2 + message_length + 1, 0, zeroes);
    // Store the length in the last bits in big endian.
    uint length_position = message_length + 1 + zeroes;
    for (uint i = 0; i < length_length; ++i) {
      message2[length_position + i] = ((message_length * byte_length) >> byte_length * (length_length - 1 - i)) & 0xFF;
    }
    sha256_word_t hash[n_hash_values];
    memcpy(hash, initial_hash_values, n_hash_values * word_length);
    for (uint j = 0; j < chunks; ++j) {
      sha256_word_t words[n_rounds];
      for (uint i = 0; i < chunk_words; ++i) {
        words[i] = (message2[word_length * i] << 3 * byte_length)
            + (message2[word_length * i + 1] << 2 * byte_length)
            + (message2[word_length * i + 2] << byte_length)
            + (message2[word_length * i + 3]);
      }
      for (uint i = chunk_words; i < n_rounds; ++i) {
        sha256_word_t s0 = right_rotate(words[i - 15], 7) ^ right_rotate(words[i - 15], 18) ^ (words[i - 15] >> 3);
        sha256_word_t s1 = right_rotate(words[i - 2], 17) ^ right_rotate(words[i - 2], 19) ^ (words[i - 2] >> 10);
        words[i] = words[i - 16] + s0 + words[i - 7] + s1;
      }
      sha256_word_t a = hash[0];
      sha256_word_t b = hash[1];
      sha256_word_t c = hash[2];
      sha256_word_t d = hash[3];
      sha256_word_t e = hash[4];
      sha256_word_t f = hash[5];
      sha256_word_t g = hash[6];
      sha256_word_t h = hash[7];
      for (uint i = 0; i < n_rounds; ++i) {
        sha256_word_t S0 = right_rotate(a, 2) ^ right_rotate(a, 13) ^ right_rotate(a, 22);
        sha256_word_t maj = (a & b) ^ (a & c) ^ (b & c);
        sha256_word_t t2 = S0 + maj;
        sha256_word_t S1 = right_rotate(e, 6) ^ right_rotate(e, 11) xor right_rotate(e, 25);
        sha256_word_t ch = (e & f) ^ ((~e) & g);
        sha256_word_t t1 = h + S1 + ch + round_constants[i] + words[i];

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
      hash[4] += a;
      hash[5] += b;
      hash[6] += c;
      hash[7] += d;
    }
    for (uint i = 0; i < n_hash_values; ++i) {
      for (uint j = 0; j < word_length; ++j) {
        digest[i * word_length + j] = (hash[i] >> (word_length - 1 - j) * byte_length) & 0xFF;
      }
    }
  }
  
} // namespace Crypto
