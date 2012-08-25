#ifndef CRYPTO_AES_CONSTANTS_H
#define CRYPTO_AES_CONSTANTS_H

#define BLOCK_BYTE_SIZE 16
#define BLOCK_ROWS 4
#define BLOCK_COLS 4
#define AES_128_BYTES 16
#define AES_192_BYTES 24
#define AES_256_BYTES 32
#define AES_128_ROUNDS 10
#define AES_192_ROUNDS 12
#define AES_256_ROUNDS 14

namespace Crypto {

  namespace AES {

    extern const unsigned char Rcon[256];

    extern const unsigned char SBox[256];

    extern const unsigned char InvSBox[256];

    extern const unsigned int Log[256];

    extern const unsigned char Exp[256];

    extern const unsigned char Invertible[256];

  }

}

#endif // CRYPTO_AES_CONSTANTS_H
