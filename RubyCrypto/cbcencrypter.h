#ifndef CBCENCRYPTER_H
#define CBCENCRYPTER_H

#ifdef __cplusplus

#include "Crypto/cbc_encrypter.h"
#include "Crypto/elgamal_encrypter.h"
#include "Crypto/aes_encrypter.h"
#include <rice/Data_Type.hpp>

template <typename BlockCipher>
class CBCEncrypter {
public:

  CBCEncrypter(const std::string& public_key, const std::string& initial_state);

  ~CBCEncrypter();

  std::string encrypt(const std::string& plain);

private:
  Crypto::CBC::Encrypter<BlockCipher>* m_encrypter;
};

typedef CBCEncrypter<Crypto::Elgamal::Encrypter> ElgamalEncrypter;

typedef CBCEncrypter<Crypto::AES::Encrypter> AESEncrypter;

extern Rice::Data_Type<ElgamalEncrypter> rb_cElgamalEncrypter;

extern Rice::Data_Type<AESEncrypter> rb_cAESEncrypter;

extern "C" {
#endif

void Init_CBCEncrypter();

#ifdef __cplusplus
}
#endif

#endif // CBCENCRYPTER_H
