#ifndef CRYPTO_CONDITIONTYPE_H
#define CRYPTO_CONDITIONTYPE_H

namespace Crypto {

  enum ConditionType {
    ElgamalKeyLength,
    AESKeyLength,
    DHKeyLength,
    GroupModulusLengthLength,
    GroupModulusLength,
    GroupGeneratorLengthLength,
    GroupGeneratorLength,
    NumberLengthLength,
    NumberLength,
    PublicKeyModulusLengthLength,
    PublicKeyModulusLength,
    PublicKeyGeneratorLengthLength,
    PublicKeyGeneratorLength,
    PublicKeyGenPowerLengthLength,
    PublicKeyGenPowerLength,
    PrivateKeyModulusLengthLength,
    PrivateKeyModulusLength,
    PrivateKeyGeneratorLengthLength,
    PrivateKeyGeneratorLength,
    PrivateKeyExponentLengthLength,
    PrivateKeyExponentLength,
    NumberFits,
    DigestLength,
    NoGroupChosen,
    NoOwnPartChosen,
    NoOtherPartSet,
    KeyNotReady,
    StateLength,
    MessagePadding,
    MessageLength,
    PlainBlockLength,
    InvalidState,
    SignatureLength
  };

}

#endif // CRYPTO_CONDITIONTYPE_H
