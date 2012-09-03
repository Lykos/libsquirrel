#include "crypto_interface.h"
#include "Crypto/elgamal_encrypter.h"
#include "Crypto/elgamal_decrypter.h"
#include "Crypto/elgamal_verifier.h"
#include "Crypto/elgamal_signer.h"
#include "Crypto/cbc_encrypter.h"
#include "Crypto/cbc_decrypter.h"
#include "Crypto/cbc_mac.h"
#include "Crypto/aes_encrypter.h"
#include "Crypto/aes_decrypter.h"
#include "Crypto/dh_keyexchange.h"
#include "Crypto/sha2hasher.h"
#include "Crypto/preconditionviolation.h"
#include "Crypto/elgamal_keygenerator.h"
#include <cstring>
#include <boost/random/random_device.hpp>
#include <typeinfo>
#define TYPECHECK(var, typid) \
  if (var->type != typid) { \
    return TYPE_EXCEPTION; \
  }
#define CAST(src, dst, type, typid) \
  TYPECHECK(src, typid); \
  if (src->ptr == NULL) { \
    return NO_INITIALIZE_EXCEPTION; \
  } \
  type* dst = reinterpret_cast<type*>(src->ptr);
#define INIT_CHECK(var, typid) \
  TYPECHECK(var, typid) \
  if (var->ptr != NULL) { \
    return DOUBLE_INITIALIZE_EXCEPTION; \
  }
#define BEGIN_EXCEPTIONS() try {
#define END_EXCEPTIONS() \
  return NO_EXCEPTION; \
} catch (Crypto::PreconditionViolation& e) { \
  return PRECONDITION_BASE - e.get_type(); \
} catch (...) { \
  return UNKNOWN_EXCEPTION; \
}

extern "C" {

using namespace Crypto;

typedef CBC::Encrypter<Elgamal::Encrypter> CBCElgamalEncrypter;

typedef CBC::Decrypter<Elgamal::Decrypter> CBCElgamalDecrypter;

typedef CBC::Encrypter<AES::Encrypter> CBCAESEncrypter;

typedef CBC::Decrypter<AES::Decrypter> CBCAESDecrypter;

typedef CBC::MAC<AES::Encrypter> CBCAESSigner;

typedef CBC::MAC<AES::Encrypter> CBCAESVerifier;

static boost::random::random_device random_device;

// Constructors
error_code_t Crypto_init_elgamal_key_generator(Crypto_object_t* key_generator)
{
  BEGIN_EXCEPTIONS();
  INIT_CHECK(key_generator, CryptoCBCElgamalEncrypter);
  key_generator->ptr = new Elgamal::KeyGenerator();
  END_EXCEPTIONS();
}

error_code_t Crypto_init_cbc_elgamal_encrypter(Crypto_object_t* encrypter, const byte_t* raw_public_key, uint key_length, const byte_t* initial_state, number_size_t state_length)
{
  BEGIN_EXCEPTIONS();
  INIT_CHECK(encrypter, CryptoCBCElgamalEncrypter);
  encrypter->ptr = new CBCElgamalEncrypter(Elgamal::Encrypter(raw_public_key, key_length), initial_state, state_length);
  END_EXCEPTIONS();
}

error_code_t Crypto_init_cbc_elgamal_decrypter(Crypto_object_t* decrypter, const byte_t* raw_private_key, uint key_length, const byte_t* initial_state, number_size_t state_length)
{
  BEGIN_EXCEPTIONS();
  INIT_CHECK(decrypter, CryptoCBCElgamalDecrypter);
  decrypter->ptr = new CBCElgamalDecrypter(Elgamal::Decrypter(raw_private_key, key_length), initial_state, state_length);
  END_EXCEPTIONS();
}

error_code_t Crypto_init_cbc_aes_encrypter(Crypto_object_t* encrypter, const byte_t* cipher_key, uint key_length, const byte_t* initial_state, number_size_t state_length)
{
  BEGIN_EXCEPTIONS();
  INIT_CHECK(encrypter, CryptoCBCAESEncrypter);
  encrypter->ptr = new CBCAESEncrypter(AES::Encrypter(cipher_key, key_length), initial_state, state_length);
  END_EXCEPTIONS();
}

error_code_t Crypto_init_cbc_aes_decrypter(Crypto_object_t* decrypter, const byte_t* cipher_key, uint key_length, const byte_t* initial_state, number_size_t state_length)
{
  BEGIN_EXCEPTIONS();
  INIT_CHECK(decrypter, CryptoCBCAESDecrypter);
  decrypter->ptr = new CBCAESDecrypter(AES::Decrypter(cipher_key, key_length), initial_state, state_length);
  END_EXCEPTIONS();
}

error_code_t Crypto_init_elgamal_signer(Crypto_object_t* signer, const byte_t* raw_private_key, uint key_length)
{
  BEGIN_EXCEPTIONS();
  INIT_CHECK(signer, CryptoElgamalSigner);
  signer->ptr = new Elgamal::Signer(raw_private_key, key_length);
  END_EXCEPTIONS();
}

error_code_t Crypto_init_elgamal_verifier(Crypto_object_t* verifier, const byte_t* raw_public_key, uint key_length)
{
  BEGIN_EXCEPTIONS();
  INIT_CHECK(verifier, CryptoElgamalVerifier);
  verifier->ptr = new Elgamal::Verifier(raw_public_key, key_length);
  END_EXCEPTIONS();
}

error_code_t Crypto_init_cbc_aes_signer(Crypto_object_t* signer, const byte_t* mac_key, uint key_length, const byte_t* initial_state, number_size_t state_length)
{
  BEGIN_EXCEPTIONS();
  INIT_CHECK(signer, CryptoCBCAESSigner);
  signer->ptr = new CBCAESSigner(AES::Encrypter(mac_key, key_length), initial_state, state_length);
  END_EXCEPTIONS();
}

error_code_t Crypto_init_cbc_aes_verifier(Crypto_object_t* verifier, const byte_t* mac_key, uint key_length, const byte_t* initial_state, number_size_t state_length)
{
  BEGIN_EXCEPTIONS();
  INIT_CHECK(verifier, CryptoCBCAESVerifier);
  verifier->ptr = new CBCAESVerifier(AES::Encrypter(mac_key, key_length), initial_state, state_length);
  END_EXCEPTIONS();
}

error_code_t Crypto_init_dh_key_exchange(Crypto_object_t* key_exchange)
{
  BEGIN_EXCEPTIONS();
  INIT_CHECK(key_exchange, CryptoDHKeyExchange);
  key_exchange->ptr = new DH::KeyExchange();
  END_EXCEPTIONS();
}

// Destructors
error_code_t Crypto_deinit_cbc_elgamal_encrypter(Crypto_object_t* encrypter)
{
  BEGIN_EXCEPTIONS();
  CAST(encrypter, enc, CBCElgamalEncrypter, CryptoCBCElgamalEncrypter);
  delete enc;
  encrypter->ptr = NULL;
  END_EXCEPTIONS();
}

error_code_t Crypto_deinit_cbc_elgamal_decrypter(Crypto_object_t* decrypter)
{
  BEGIN_EXCEPTIONS();
  CAST(decrypter, dec, CBCElgamalDecrypter, CryptoCBCElgamalDecrypter);
  delete dec;
  decrypter->ptr = NULL;
  END_EXCEPTIONS();
}

error_code_t Crypto_deinit_cbc_aes_encrypter(Crypto_object_t* encrypter)
{
  BEGIN_EXCEPTIONS();
  CAST(encrypter, enc, CBCAESEncrypter, CryptoCBCAESEncrypter);
  delete enc;
  encrypter->ptr = NULL;
  END_EXCEPTIONS();
}

error_code_t Crypto_deinit_cbc_aes_decrypter(Crypto_object_t* decrypter)
{
  BEGIN_EXCEPTIONS();
  CAST(decrypter, dec, CBCAESDecrypter, CryptoCBCAESEncrypter);
  delete dec;
  decrypter->ptr = NULL;
  END_EXCEPTIONS();
}

error_code_t Crypto_deinit_elgamal_signer(Crypto_object_t* signer)
{
  BEGIN_EXCEPTIONS();
  CAST(signer, sig, Elgamal::Signer, CryptoElgamalSigner);
  delete sig;
  signer->ptr = NULL;
  END_EXCEPTIONS();
}

error_code_t Crypto_deinit_elgamal_verifier(Crypto_object_t* verifier)
{
  BEGIN_EXCEPTIONS();
  CAST(verifier, ver, CBCElgamalEncrypter, CryptoElgamalVerifier);
  delete ver;
  verifier->ptr = NULL;
  END_EXCEPTIONS();
}

error_code_t Crypto_deinit_cbc_aes_signer(Crypto_object_t* signer)
{
  BEGIN_EXCEPTIONS();
  CAST(signer, sig, CBCAESSigner, CryptoCBCAESSigner);
  delete sig;
  signer->ptr = NULL;
  END_EXCEPTIONS();
}

error_code_t Crypto_deinit_cbc_aes_verifier(Crypto_object_t* verifier)
{
  BEGIN_EXCEPTIONS();
  CAST(verifier, ver, CBCAESVerifier, CryptoCBCAESVerifier);
  delete ver;
  verifier->ptr = NULL;
  END_EXCEPTIONS();
}

error_code_t Crypto_deinit_dh_key_exchange(Crypto_object_t* key_exchange)
{
  BEGIN_EXCEPTIONS();
  CAST(key_exchange, ke, CBCElgamalEncrypter, CryptoDHKeyExchange);
  delete ke;
  key_exchange->ptr = NULL;
  END_EXCEPTIONS();
}

// Queries
returned_message_size_t Crypto_cbc_elgamal_cipher_length(Crypto_object_t* encrypter, message_size_t plain_length)
{
  BEGIN_EXCEPTIONS();
  CAST(encrypter, enc, CBCElgamalEncrypter, CryptoCBCElgamalEncrypter);
  return enc->cipher_length(plain_length);
  END_EXCEPTIONS();
}

returned_message_size_t Crypto_cbc_elgamal_max_plain_length(Crypto_object_t* decrypter, message_size_t cipher_length)
{
  BEGIN_EXCEPTIONS();
  CAST(decrypter, dec, CBCElgamalDecrypter, CryptoCBCElgamalDecrypter);
  return dec->max_plain_length(cipher_length);
  END_EXCEPTIONS();
}

returned_message_size_t Crypto_cbc_aes_cipher_length(Crypto_object_t* encrypter, message_size_t plain_length)
{
  BEGIN_EXCEPTIONS();
  CAST(encrypter, enc, CBCAESEncrypter, CryptoCBCAESEncrypter);
  return enc->cipher_length(plain_length);
  END_EXCEPTIONS();
}

returned_message_size_t Crypto_cbc_aes_max_plain_length(Crypto_object_t* decrypter, message_size_t cipher_length)
{
  BEGIN_EXCEPTIONS();
  CAST(decrypter, dec, CBCAESDecrypter, CryptoCBCAESDecrypter);
  return dec->max_plain_length(cipher_length);
  END_EXCEPTIONS();
}

returned_message_size_t Crypto_elgamal_signature_length_signer(Crypto_object_t* signer)
{
  BEGIN_EXCEPTIONS();
  CAST(signer, sig, Elgamal::Signer, CryptoElgamalSigner);
  return sig->signature_length();
  END_EXCEPTIONS();
}

returned_message_size_t Crypto_elgamal_signature_length_verifier(Crypto_object_t* verifier)
{
  BEGIN_EXCEPTIONS();
  CAST(verifier, ver, Elgamal::Verifier, CryptoElgamalVerifier);
  return ver->signature_length();
  END_EXCEPTIONS();
}

returned_message_size_t Crypto_cbc_aes_signature_length_signer(Crypto_object_t* signer)
{
  BEGIN_EXCEPTIONS();
  CAST(signer, sig, CBCAESSigner, CryptoCBCAESSigner);
  return sig->signature_length();
  END_EXCEPTIONS();
}

returned_message_size_t Crypto_cbc_aes_signature_length_verifier(Crypto_object_t* verifier)
{
  BEGIN_EXCEPTIONS();
  CAST(verifier, ver, CBCAESVerifier, CryptoCBCAESVerifier);
  return ver->signature_length();
  END_EXCEPTIONS();
}

returned_message_size_t Crypto_dh_key_exchange_group_length(Crypto_object_t* key_exchange)
{
  BEGIN_EXCEPTIONS();
  CAST(key_exchange, ke, DH::KeyExchange, CryptoDHKeyExchange);
  if (!ke->group_chosen()) {
    return PRECONDITION_BASE + ConditionType::NoGroupChosen;
  }
  return ke->group_length();
  END_EXCEPTIONS();
}

returned_message_size_t Crypto_dh_key_exchange_gen_power_length(Crypto_object_t* key_exchange)
{
  BEGIN_EXCEPTIONS();
  CAST(key_exchange, ke, DH::KeyExchange, CryptoDHKeyExchange);
  if (!ke->group_chosen()) {
    return PRECONDITION_BASE + ConditionType::NoGroupChosen;
  }
  if (!ke->own_part_chosen()) {
    ke->choose_own_part(random_device);
  }
  return ke->own_part_length();
  END_EXCEPTIONS();
}

returned_message_size_t Crypto_dh_key_exchange_key_length(Crypto_object_t* key_exchange)
{
  BEGIN_EXCEPTIONS();
  CAST(key_exchange, ke, DH::KeyExchange, CryptoDHKeyExchange);
  if (!ke->group_chosen()) {
    return PRECONDITION_BASE + ConditionType::NoGroupChosen;
  } else if (!ke->own_part_chosen()) {
    return PRECONDITION_BASE + ConditionType::NoOwnPartChosen;
  } else if (!ke->other_part_set()) {
    return PRECONDITION_BASE + ConditionType::NoOtherPartSet;
  } else if (!ke->key_ready()) {
    return PRECONDITION_BASE + ConditionType::KeyNotReady;
  }
  return ke->key_length();
  END_EXCEPTIONS();
}

returned_bool_t Crypto_dh_key_exchange_group_chosen(Crypto_object_t* key_exchange)
{
  BEGIN_EXCEPTIONS();
  CAST(key_exchange, ke, DH::KeyExchange, CryptoDHKeyExchange);
  return ke->group_chosen();
  END_EXCEPTIONS();
}

returned_bool_t Crypto_dh_key_exchange_own_part_chosen(Crypto_object_t* key_exchange)
{
  BEGIN_EXCEPTIONS();
  CAST(key_exchange, ke, DH::KeyExchange, CryptoDHKeyExchange);
  return ke->own_part_chosen();
  END_EXCEPTIONS();
}

returned_bool_t Crypto_dh_key_exchange_other_part_set(Crypto_object_t* key_exchange)
{
  BEGIN_EXCEPTIONS();
  CAST(key_exchange, ke, DH::KeyExchange, CryptoDHKeyExchange);
  return ke->other_part_set();
  END_EXCEPTIONS();
}

returned_bool_t Crypto_dh_key_exchange_key_ready(Crypto_object_t* key_exchange)
{
  BEGIN_EXCEPTIONS();
  CAST(key_exchange, ke, DH::KeyExchange, CryptoDHKeyExchange);
  return ke->key_ready();
  END_EXCEPTIONS();
}

// Operations
error_code_t Crypto_generate_aes_keys(const byte_t* secret, message_size_t secret_length, byte_t* cipher_key, byte_t* mac_key)
{
  BEGIN_EXCEPTIONS();
  // TODO This has to be exchanged since it might be insecure for some hash functions. (Probably not for SHA-2, though)
  byte_t digest[256];
  SHA2Hasher hasher (256);
  hasher.hash(secret, secret_length, digest + 0);
  memcpy(cipher_key, digest + 0, 128);
  memcpy(mac_key, digest + 128, 128);
  END_EXCEPTIONS();
}

returned_message_size_t Crypto_cbc_elgamal_encrypt(Crypto_object_t* encrypter, const byte_t* plain, message_size_t length, byte_t* cipher)
{
  BEGIN_EXCEPTIONS();
  CAST(encrypter, enc, CBCElgamalEncrypter, CryptoCBCElgamalEncrypter);
  return enc->encrypt(plain, length, cipher);
  END_EXCEPTIONS();
}

returned_message_size_t Crypto_cbc_elgamal_decrypt(Crypto_object_t* decrypter, const byte_t* cipher, message_size_t length, byte_t* plain)
{
  BEGIN_EXCEPTIONS();
  CAST(decrypter, dec, CBCElgamalDecrypter, CryptoCBCElgamalDecrypter);
  return dec->decrypt(cipher, length, plain);
  END_EXCEPTIONS();
}

returned_message_size_t Crypto_cbc_aes_encrypt(Crypto_object_t* encrypter, const byte_t* plain, message_size_t length, byte_t* cipher)
{
  BEGIN_EXCEPTIONS();
  CAST(encrypter, enc, CBCAESEncrypter, CryptoCBCAESEncrypter);
  return enc->encrypt(plain, length, cipher);
  END_EXCEPTIONS();
}

returned_message_size_t Crypto_cbc_aes_decrypt(Crypto_object_t* decrypter, const byte_t* cipher, message_size_t length, byte_t* plain)
{
  BEGIN_EXCEPTIONS();
  CAST(decrypter, dec, CBCAESDecrypter, CryptoCBCAESDecrypter);
  return dec->decrypt(cipher, length, plain);
  END_EXCEPTIONS();
}

returned_message_size_t Crypto_elgamal_sign(Crypto_object_t* signer, byte_t* message, message_size_t length)
{
  BEGIN_EXCEPTIONS();
  CAST(signer, sig, Elgamal::Signer, CryptoElgamalSigner);
  return sig->sign(message, length);
  END_EXCEPTIONS();
}

returned_bool_t Crypto_elgamal_verify(Crypto_object_t* verifier, const byte_t* message, message_size_t length)
{
  BEGIN_EXCEPTIONS();
  CAST(verifier, ver, Elgamal::Verifier, CryptoElgamalVerifier);
  return ver->verify(message, length);
  END_EXCEPTIONS();
}

returned_message_size_t Crypto_cbc_aes_sign(Crypto_object_t* signer, byte_t* message, message_size_t length)
{
  BEGIN_EXCEPTIONS();
  CAST(signer, sig, CBCAESSigner, CryptoCBCAESSigner);
  return sig->sign(message, length);
  END_EXCEPTIONS();
}

returned_bool_t Crypto_cbc_aes_verify(Crypto_object_t* verifier, const byte_t* message, message_size_t length)
{
  BEGIN_EXCEPTIONS();
  CAST(verifier, ver, CBCAESVerifier, CryptoCBCAESVerifier);
  return ver->verify(message, length);
  END_EXCEPTIONS();
}

error_code_t Crypto_dh_key_exchange_choose_group(Crypto_object_t* key_exchange, number_size_t bits)
{
  BEGIN_EXCEPTIONS();
  CAST(key_exchange, ke, DH::KeyExchange, CryptoDHKeyExchange);
  ke->choose_group(bits);
  END_EXCEPTIONS();
}

returned_message_size_t Crypto_dh_key_exchange_group(Crypto_object_t* key_exchange, byte_t* raw_group)
{
  BEGIN_EXCEPTIONS();
  CAST(key_exchange, ke, DH::KeyExchange, CryptoDHKeyExchange);
  return ke->write_group(raw_group);
  END_EXCEPTIONS();
}

returned_message_size_t Crypto_dh_key_exchange_gen_power(Crypto_object_t* key_exchange, byte_t* raw_gen_power)
{
  BEGIN_EXCEPTIONS();
  CAST(key_exchange, ke, DH::KeyExchange, CryptoDHKeyExchange);
  return ke->write_own_part(raw_gen_power);
  END_EXCEPTIONS();
}

returned_message_size_t Crypto_dh_key_exchange_key(Crypto_object_t* key_exchange, byte_t* raw_key)
{
  BEGIN_EXCEPTIONS();
  CAST(key_exchange, ke, DH::KeyExchange, CryptoDHKeyExchange);
  return ke->write_key(raw_key);
  END_EXCEPTIONS();
}

error_code_t Crypto_dh_key_exchange_set_other_gen_power(Crypto_object_t* key_exchange, byte_t* raw_gen_power, message_size_t length)
{
  BEGIN_EXCEPTIONS();
  CAST(key_exchange, ke, DH::KeyExchange, CryptoDHKeyExchange);
  ke->read_other_part(raw_gen_power, length);
  END_EXCEPTIONS();
}

error_code_t Crypto_dh_key_exchange_set_group(Crypto_object_t* key_exchange, byte_t* raw_group, message_size_t length)
{
  BEGIN_EXCEPTIONS();
  CAST(key_exchange, ke, DH::KeyExchange, CryptoDHKeyExchange);
  ke->read_group(raw_group, length);
  END_EXCEPTIONS();
}

}
