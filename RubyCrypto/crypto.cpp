#include "crypto.h"
#include "cryptoexception.h"
#include "cbcencrypter.h"
#include "cbcdecrypter.h"
#include "sha2hasher.h"

using namespace Rice;

Rice::Module rb_mCrypto;

extern "C" void Init_Crypto()
{
  rb_mCrypto = define_module("Crypto");
  Init_CryptoException();
  Init_CBCEncrypter();
  Init_CBCDecrypter();
  Init_SHA2Hasher();
}
