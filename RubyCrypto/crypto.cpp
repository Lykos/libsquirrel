#include "crypto.h"
#include "cryptoexception.h"
#include "elgamalencrypter.h"
#include "elgamaldecrypter.h"
#include "sha2hasher.h"

using namespace Rice;

Rice::Module rb_mCrypto;

extern "C" void Init_Crypto()
{
  rb_mCrypto = define_module("Crypto");
  Init_CryptoException();
  Init_ElgamalEncrypter();
  Init_ElgamalDecrypter();
  Init_SHA2Hasher();
}
