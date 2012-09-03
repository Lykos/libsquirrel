#ifndef ELGAMALENCRYPTER_H
#define ELGAMALENCRYPTER_H

#ifdef __cplusplus

#include "Crypto/cbc_encrypter.h"
#include "Crypto/elgamal_encrypter.h"
#include <rice/Data_Type.hpp>

class ElgamalEncrypter {
public:

  ElgamalEncrypter(const std::string& public_key, const std::string& initial_state);

  ~ElgamalEncrypter();

  std::string encrypt(const std::string& plain);

private:
  Crypto::CBC::Encrypter<Crypto::Elgamal::Encrypter>* m_encrypter;
};

extern Rice::Data_Type<ElgamalEncrypter> rb_cElgamalEncrypter;

extern "C" {
#endif

void Init_ElgamalEncrypter();

#ifdef __cplusplus
}
#endif

#endif // ELGAMALENCRYPTER_H
