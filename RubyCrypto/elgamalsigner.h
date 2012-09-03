#ifndef ELGAMALSIGNER_H
#define ELGAMALSIGNER_H

#ifdef __cplusplus

#include "Crypto/elgamal_signer.h"
#include <rice/Data_Type.hpp>

class ElgamalSigner {
public:

  ElgamalSigner(const std::string& private_key);

  ~ElgamalSigner();

  void sign(std::string& message);

private:
  Crypto::Elgamal::Signer* m_signer;
};

extern Rice::Data_Type<ElgamalSigner> rb_cElgamalSigner;

extern "C" {
#endif

void Init_ElgamalSigner();

#ifdef __cplusplus
}
#endif

#endif // ELGAMALSIGNER_H
