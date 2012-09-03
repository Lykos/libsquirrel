#ifndef CRYPTO_CONDITIONTYPE_H
#define CRYPTO_CONDITIONTYPE_H

namespace Crypto {

  enum ConditionType {
    KeyLength,
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
    MessageLength
  };

}

#endif // CRYPTO_CONDITIONTYPE_H
