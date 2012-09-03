#ifndef ELGAMALDECRYPTER_H
#define ELGAMALDECRYPTER_H

#ifdef __cplusplus

#include "Crypto/cbc_decrypter.h"
#include "Crypto/elgamal_decrypter.h"
#include <rice/Data_Type.hpp>

class ElgamalDecrypter {
public:

  ElgamalDecrypter(const std::string& private_key, const std::string& initial_state);

  ~ElgamalDecrypter();

  std::string decrypt(const std::string& cipher);

private:
  Crypto::CBC::Decrypter<Crypto::Elgamal::Decrypter>* m_decrypter;
};

extern Rice::Data_Type<ElgamalDecrypter> rb_cElgamalDecrypter;

extern "C" {
#endif

void Init_ElgamalDecrypter();

#ifdef __cplusplus
}
#endif

#endif // ELGAMALDECRYPTER_H
