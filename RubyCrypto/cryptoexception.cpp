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
  char const* error_message;
  switch (e.get_type()) {
  case ElgamalKeyLength:
    error_message = "Invalid Elgamal key length.";
    break;
  case AESKeyLength:
    error_message = "Invalid AES key length";
    break;
  case DHKeyLength:
    error_message = "Invalid DH key length";
    break;
  case GroupModulusLengthLength:
    error_message = "The group string is too short to store the length of the modulus.";
    break;
  case GroupModulusLength:
    error_message = "The group string is too short to store the modulus.";
    break;
  case GroupGeneratorLengthLength:
    error_message = "The group string is too short to store the length of the generator.";
    break;
  case GroupGeneratorLength:
    error_message = "The group string is too short to store the generator.";
    break;
  case NumberLengthLength:
    error_message = "The string is too short to store the length of the number.";
    break;
  case NumberLength:
    error_message = "The string is too short to store the number.";
    break;
  case PublicKeyModulusLengthLength:
    error_message = "The public key string is too short to store the length of the modulus.";
    break;
  case PublicKeyModulusLength:
    error_message = "The public key string is too short to store the modulus.";
    break;
  case PublicKeyGeneratorLengthLength:
    error_message = "The public key string is too short to store the length of the generator.";
    break;
  case PublicKeyGeneratorLength:
    error_message = "The public key string is too short to store the generator.";
    break;
  case PublicKeyGenPowerLengthLength:
    error_message = "The public key string is too short to store the length of the generator power.";
    break;
  case PublicKeyGenPowerLength:
    error_message = "The public key string is too short to store the generator power.";
    break;
  case PrivateKeyModulusLengthLength:
    error_message = "The private key string is too short to store the length of the modulus.";
    break;
  case PrivateKeyModulusLength:
    error_message = "The private key string is too short to store the modulus.";
    break;
  case PrivateKeyGeneratorLengthLength:
    error_message = "The private key string is too short to store the length of the generator.";
    break;
  case PrivateKeyGeneratorLength:
    error_message = "The private key string is too short to store the generator.";
    break;
  case PrivateKeyExponentLengthLength:
    error_message = "The private key string is too short to store the length of the exponent.";
    break;
  case PrivateKeyExponentLength:
    error_message = "The private key string is too short to store the exponent.";
    break;
  case NumberFits:
    error_message = "The number doesn't fit into the given segment.";
    break;
  case DigestLength:
    error_message = "Invalid digest length.";
    break;
  case NoGroupChosen:
    error_message = "No group has been chosen for the Diffie Hellman key exchange.";
    break;
  case NoOwnPartChosen:
    error_message = "No own part has been chosen for the Diffie Hellman key exchange.";
    break;
  case NoOtherPartSet:
    error_message = "No other part has been set for the Diffie Hellman key exchange.";
    break;
  case KeyNotReady:
    error_message = "The key of the Diffie Hellman key exchange is not ready.";
    break;
  case StateLength:
    error_message = "The length of the given initial state is too short.";
    break;
  case MessagePadding:
    error_message = "The padding of the message has an invalid format";
    break;
  case MessageLength:
    error_message = "The cipher has a length which is not divisible by the block size.";
    break;
  case PlainBlockLength:
    error_message = "The decrypted plain text is too big for a block.";
    break;
  default:
    throw Exception(rb_eCryptoException, "Unknown exception thrown in extension. Internal error code is %d", int(e.get_type()));
  }
  throw Exception(rb_eCryptoException, error_message);
}
