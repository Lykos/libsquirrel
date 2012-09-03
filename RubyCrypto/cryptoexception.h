#ifndef CRYPTOEXCEPTION_H
#define CRYPTOEXCEPTION_H

#ifdef __cplusplus

#include "Crypto/preconditionviolation.h"
#include <rice/Exception.hpp>
#include <rice/Class.hpp>

extern Rice::Class rb_eCryptoException;

void handle(const Crypto::PreconditionViolation& e);

extern "C" {
#endif

void Init_CryptoException();

#ifdef __cplusplus
}
#endif

#endif // CRYPTOEXCEPTION_H
