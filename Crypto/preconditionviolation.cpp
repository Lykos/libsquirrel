#include "preconditionviolation.h"

namespace Crypto {
  
  PreconditionViolation::PreconditionViolation(ConditionType type, const char* dummy_message):
    m_type (type)
  {
    switch (type) {
    case ElgamalKeyLength:
      m_message = "Invalid Elgamal key length.";
      break;
    case AESKeyLength:
      m_message = "Invalid AES key length";
      break;
    case DHKeyLength:
      m_message = "Invalid DH key length";
      break;
    case GroupModulusLengthLength:
      m_message = "The group string is too short to store the length of the modulus.";
      break;
    case GroupModulusLength:
      m_message = "The group string is too short to store the modulus.";
      break;
    case GroupGeneratorLengthLength:
      m_message = "The group string is too short to store the length of the generator.";
      break;
    case GroupGeneratorLength:
      m_message = "The group string is too short to store the generator.";
      break;
    case NumberLengthLength:
      m_message = "The string is too short to store the length of the number.";
      break;
    case NumberLength:
      m_message = "The string is too short to store the number.";
      break;
    case NumberLengthValue:
      m_message = "Invalid length.";
      break;
    case PublicKeyModulusLengthLength:
      m_message = "The public key string is too short to store the length of the modulus.";
      break;
    case PublicKeyModulusLength:
      m_message = "The public key string is too short to store the modulus.";
      break;
    case PublicKeyGeneratorLengthLength:
      m_message = "The public key string is too short to store the length of the generator.";
      break;
    case PublicKeyGeneratorLength:
      m_message = "The public key string is too short to store the generator.";
      break;
    case PublicKeyGenPowerLengthLength:
      m_message = "The public key string is too short to store the length of the generator power.";
      break;
    case PublicKeyGenPowerLength:
      m_message = "The public key string is too short to store the generator power.";
      break;
    case PrivateKeyModulusLengthLength:
      m_message = "The private key string is too short to store the length of the modulus.";
      break;
    case PrivateKeyModulusLength:
      m_message = "The private key string is too short to store the modulus.";
      break;
    case PrivateKeyGeneratorLengthLength:
      m_message = "The private key string is too short to store the length of the generator.";
      break;
    case PrivateKeyGeneratorLength:
      m_message = "The private key string is too short to store the generator.";
      break;
    case PrivateKeyExponentLengthLength:
      m_message = "The private key string is too short to store the length of the exponent.";
      break;
    case PrivateKeyExponentLength:
      m_message = "The private key string is too short to store the exponent.";
      break;
    case NumberFits:
      m_message = "The number doesn't fit into the given segment.";
      break;
    case DigestLength:
      m_message = "Invalid digest length.";
      break;
    case NoGroupChosen:
      m_message = "No group has been chosen for the Diffie Hellman key exchange.";
      break;
    case NoOwnPartChosen:
      m_message = "No own part has been chosen for the Diffie Hellman key exchange.";
      break;
    case NoOtherPartSet:
      m_message = "No other part has been set for the Diffie Hellman key exchange.";
      break;
    case KeyNotReady:
      m_message = "The key of the Diffie Hellman key exchange is not ready.";
      break;
    case StateLength:
      m_message = "The length of the given initial state is too short.";
      break;
    case MessagePadding:
      m_message = "The padding of the message has an invalid format";
      break;
    case MessageLength:
      m_message = "The cipher has a length which is not divisible by the block size.";
      break;
    case DecryptedPlainBlockLength:
      m_message = "The decrypted plain text is too big for a block.";
      break;
    case InvalidState:
      m_message = "State is invalid because of an invalid message.";
      break;
    default:
      m_message = dummy_message;
    }
  }
  
} // namespace Crypto
