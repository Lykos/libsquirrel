#ifndef CRYPTO_H
#define CRYPTO_H

#ifdef __cplusplus

#include <rice/Module.hpp>

extern Rice::Module rb_mCrypto;

extern "C" {
#endif

void Init_Crypto();

#ifdef __cplusplus
}
#endif

#endif // CRYPTO_H
