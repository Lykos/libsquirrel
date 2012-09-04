#ifndef ELGAMALVERIFIER_H
#define ELGAMALVERIFIER_H

#ifdef __cplusplus

#include "Crypto/elgamal_verifier.h"
#include <rice/Data_Type.hpp>

class ElgamalVerifier {
public:

  ElgamalVerifier(const std::string& public_key);

  ~ElgamalVerifier();

  bool verify(const std::string& message);

  std::string& remove_signature(std::string& message);

  Crypto::number_size_t signature_length();

private:
  Crypto::Elgamal::Verifier* m_verifier;
};

extern Rice::Data_Type<ElgamalVerifier> rb_cElgamalVerifier;

extern "C" {
#endif

void Init_ElgamalVerifier();

#ifdef __cplusplus
}
#endif

#endif // ELGAMALVERIFIER_H
