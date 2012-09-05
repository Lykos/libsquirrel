#ifndef ELGAMALSIGNER_H
#define ELGAMALSIGNER_H

#ifdef __cplusplus

#include "Crypto/elgamal_signer.h"
#include <string>
#include <rice/Data_Type.hpp>

extern Rice::Data_Type<Crypto::Elgamal::Signer> rb_cElgamalSigner;

extern "C" {
#endif

void Init_ElgamalSigner();

#ifdef __cplusplus
}
#endif

#endif // ELGAMALSIGNER_H
