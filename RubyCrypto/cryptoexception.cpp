#include "cryptoexception.h"
#include "crypto.h"
#include "Crypto/conditiontype.h"
#include <rice/Exception.hpp>

using namespace Rice;
using namespace Crypto;

Rice::Class rb_eCryptoException;

extern "C" void Init_CryptoException()
{
  rb_eCryptoException = define_class_under(rb_mCrypto, "CryptoException", rb_eStandardError);
}

void handle(const Crypto::PreconditionViolation& e)
{
  throw Exception(rb_eCryptoException, e.what());
}
