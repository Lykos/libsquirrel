#include "elgamal_converter.h"
#include "readnumber_macro.h"
#include "preconditionviolation.h"

using namespace std;

namespace Crypto {

  namespace Elgamal {

    public_key_t Converter::read_public_key(const std::string& raw_public_key)
    {
      INIT_READ(raw_public_key);
      READ_NUMBER(PublicKeyModulusLengthLength, PublicKeyModulusLength, modulus, raw_public_key);
      READ_NUMBER(PublicKeyGeneratorLengthLength, PublicKeyGeneratorLength, generator, raw_public_key);
      READ_NUMBER(PublicKeyGenPowerLengthLength, PublicKeyGenPowerLength, gen_power, raw_public_key);
      return {modulus, generator, gen_power};
    }

    std::string Converter::write_public_key(const public_key_t& public_key)
    {
      return DH::Converter::write_number(public_key.modulus)
          + DH::Converter::write_number(public_key.generator)
          + DH::Converter::write_number(public_key.gen_power);
    }

    private_key_t Converter::read_private_key(const std::string& raw_private_key)
    {
      INIT_READ(raw_private_key);
      READ_NUMBER(PrivateKeyModulusLengthLength, PrivateKeyModulusLength, modulus, raw_private_key);
      READ_NUMBER(PrivateKeyGeneratorLengthLength, PrivateKeyGeneratorLength, generator, raw_private_key);
      READ_NUMBER(PrivateKeyExponentLengthLength, PrivateKeyExponentLength, exponent, raw_private_key);
      return {modulus, generator, exponent};
    }

    std::string Converter::write_private_key(const private_key_t& private_key)
    {
      return DH::Converter::write_number(private_key.modulus)
          + DH::Converter::write_number(private_key.generator)
          + DH::Converter::write_number(private_key.exponent);
    }

  } // namespace Elgamal
} // namespace Crypto
