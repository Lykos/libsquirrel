#ifndef CRYPTO_AES_TYPES_H
#define CRYPTO_AES_TYPES_H

#define BLOCK_SIZE 128
#define AES_128_BYTES 16
#define AES_192_BYTES 24
#define AES_256_BYTES 32
#define AES_128_ROUNDS 10
#define AES_192_ROUNDS 12
#define AES_256_ROUNDS 14

namespace Crypto {

  namespace AES {

    typedef unsigned char char_t;

    typedef unsigned int word_t;

    typedef struct {
      char_t* bytes;
      unsigned int key_length;
    } key_t;

    typedef struct {
      word_t* bytes;
      unsigned int key_length;
    } ex_key_t;

    typedef char_t* cipher_t;

    typedef char_t* plain_t;

  }

}

#endif // CRYPTO_AES_TYPES_H
