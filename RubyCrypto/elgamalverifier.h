#ifndef ELGAMALVERIFIER_H
#define ELGAMALVERIFIER_H

#ifdef __cplusplus

#include "Crypto/elgamal_verifier.h"
#include <rice/Data_Type.hpp>

extern Rice::Data_Type<Crypto::Elgamal::Verifier> rb_cElgamalVerifier;

extern "C" {
#endif

void Init_ElgamalVerifier();

#ifdef __cplusplus
}
#endif

#endif // ELGAMALVERIFIER_H
