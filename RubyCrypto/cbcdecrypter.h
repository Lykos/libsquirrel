#ifndef ELGAMALDECRYPTER_H
#define ELGAMALDECRYPTER_H

#ifdef __cplusplus

#include "Crypto/cbc_decrypter.h"
#include "Crypto/elgamal_decrypter.h"
#include "Crypto/aes_decrypter.h"
#include <rice/Data_Type.hpp>

template <typename BlockCipher>
class CBCDecrypter {
public:

  CBCDecrypter(const std::string& private_key, const std::string& initial_state);

  ~CBCDecrypter();

  std::string decrypt(const std::string& cipher);

private:
  Crypto::CBC::Decrypter<BlockCipher>* m_decrypter;
};

typedef CBCDecrypter<Crypto::Elgamal::Decrypter> ElgamalDecrypter;

typedef CBCDecrypter<Crypto::AES::Decrypter> AESDecrypter;

extern Rice::Data_Type<ElgamalDecrypter> rb_cElgamalDecrypter;

extern Rice::Data_Type<AESDecrypter> rb_cAESDecrypter;

extern "C" {
#endif

void Init_CBCDecrypter();

#ifdef __cplusplus
}
#endif

#endif // ELGAMALDECRYPTER_H
