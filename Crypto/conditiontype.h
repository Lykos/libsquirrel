#ifndef CRYPTO_CONDITIONTYPE_H
#define CRYPTO_CONDITIONTYPE_H

#ifdef __cplusplus
namespace Crypto {
#endif

  typedef enum {
    KeyLength = 1,
    GroupModulusLengthLength = 2,
    GroupModulusLength = 3,
    GroupGeneratorLengthLength = 4,
    GroupGeneratorLength = 5,
    NumberLengthLength = 6,
    NumberLength = 7,
    PublicKeyModulusLengthLength = 8,
    PublicKeyModulusLength = 9,
    PublicKeyGeneratorLengthLength = 10,
    PublicKeyGeneratorLength = 11,
    PublicKeyGenPowerLengthLength = 12,
    PublicKeyGenPowerLength = 13,
    PrivateKeyModulusLengthLength = 14,
    PrivateKeyModulusLength = 15,
    PrivateKeyGeneratorLengthLength = 16,
    PrivateKeyGeneratorLength = 17,
    PrivateKeyGenPowerLengthLength = 18,
    PrivateKeyGenPowerLength = 19,
    NumberFits = 20,
    DigestLength = 21,
    NoGroupChosen = 22,
    NoOwnPartChosen = 23,
    NoOtherPartSet = 24,
    KeyNotReady = 25,
    StateLength = 26,
    CipherAlignment = 27,
    NumberAlignment = 28,
    GroupModulusAlignment = 29,
    GroupGeneratorAlignment = 30,
    PublicKeyModulusAlignment = 31,
    PublicKeyGeneratorAlignment = 32,
    PublicKeyGenPowerAlignment = 33,
    PrivateKeyModulusAlignment = 34,
    PrivateKeyGeneratorAlignment = 35,
    PrivateKeyExponentAlignment = 36
  } ConditionType;

#ifdef __cplusplus
}
#endif

#endif // CRYPTO_CONDITIONTYPE_H
