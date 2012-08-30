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
#include <cstring>
#include <boost/random/random_device.hpp>
#include <typeinfo>

extern "C" {

using namespace Crypto;

typedef CBC::Encrypter<Elgamal::Encrypter> CBCElgamalEncrypter;

typedef CBC::Decrypter<Elgamal::Decrypter> CBCElgamalDecrypter;

typedef CBC::Encrypter<AES::Encrypter> CBCAESEncrypter;

typedef CBC::Decrypter<AES::Decrypter> CBCAESDecrypter;

typedef CBC::MAC<AES::Encrypter> CBCAESSigner;

typedef CBC::MAC<AES::Encrypter> CBCAESVerifier;

static boost::random::random_device random_device;

const number_size_t Crypto_cbc_elgamal_encrypter_length = sizeof(CBCElgamalEncrypter);

const number_size_t Crypto_cbc_elgamal_decrypter_length = sizeof(CBCElgamalDecrypter);

const number_size_t Crypto_cbc_aes_encrypter_length = sizeof(CBCAESEncrypter);

const number_size_t Crypto_cbc_aes_decrypter_length = sizeof(CBCAESDecrypter);

const number_size_t Crypto_elgamal_signer_length = sizeof(Elgamal::Signer);

const number_size_t Crypto_elgamal_verifier_length = sizeof(Elgamal::Verifier);

const number_size_t Crypto_cbc_aes_signer_length = sizeof(CBCAESSigner);

const number_size_t Crypto_cbc_aes_verifier_length = sizeof(CBCAESVerifier);

const number_size_t Crypto_dh_key_exchange_length = sizeof(DH::KeyExchange);

// Constructors
error_code_t Crypto_init_cbc_elgamal_encrypter(Crypto_cbc_elgamal_encrypter_t encrypter, const byte_t* raw_public_key, uint key_length, const byte_t* initial_state, number_size_t state_length)
{
  try {
    new(encrypter) CBCElgamalEncrypter(Elgamal::Encrypter(raw_public_key, key_length), initial_state, state_length);
    return NO_EXCEPTION;
  } catch(Crypto::PreconditionViolation& e) {
    return PRECONDITION_BASE - e.get_type();
  } catch (...) {
    return UNKNOWN_EXCEPTION;
  }
}

error_code_t Crypto_init_cbc_elgamal_decrypter(Crypto_cbc_elgamal_decrypter_t decrypter, const byte_t* raw_private_key, uint key_length, const byte_t* initial_state, number_size_t state_length)
{
  try {
    new(decrypter) CBCElgamalDecrypter(Elgamal::Decrypter(raw_private_key, key_length), initial_state, state_length);
    return NO_EXCEPTION;
  } catch(Crypto::PreconditionViolation& e) {
    return PRECONDITION_BASE - e.get_type();
  } catch (...) {
    return UNKNOWN_EXCEPTION;
  }
}

error_code_t Crypto_init_cbc_aes_encrypter(Crypto_cbc_aes_encrypter_t encrypter, const byte_t* cipher_key, uint key_length, const byte_t* initial_state, number_size_t state_length)
{
  try {
    new(encrypter) CBCAESEncrypter(AES::Encrypter(cipher_key, key_length), initial_state, state_length);
    return NO_EXCEPTION;
  } catch(Crypto::PreconditionViolation& e) {
    return PRECONDITION_BASE - e.get_type();
  } catch (...) {
    return UNKNOWN_EXCEPTION;
  }
}

error_code_t Crypto_init_cbc_aes_decrypter(Crypto_cbc_aes_decrypter_t decrypter, const byte_t* cipher_key, uint key_length, const byte_t* initial_state, number_size_t state_length)
{
  try {
    new(decrypter) CBCAESDecrypter(AES::Decrypter(cipher_key, key_length), initial_state, state_length);
    return NO_EXCEPTION;
  } catch(Crypto::PreconditionViolation& e) {
    return PRECONDITION_BASE - e.get_type();
  } catch (...) {
    return UNKNOWN_EXCEPTION;
  }
}

error_code_t Crypto_init_elgamal_signer(Crypto_elgamal_signer_t signer, const byte_t* raw_private_key, uint key_length)
{
  try {
    new(signer) Elgamal::Signer(raw_private_key, key_length);
    return NO_EXCEPTION;
  } catch(Crypto::PreconditionViolation& e) {
    return PRECONDITION_BASE - e.get_type();
  } catch (...) {
    return UNKNOWN_EXCEPTION;
  }
}

error_code_t Crypto_init_elgamal_verifier(Crypto_elgamal_verifier_t verifier, const byte_t* raw_public_key, uint key_length)
{
  try {
    new(verifier) Elgamal::Verifier(raw_public_key, key_length);
    return NO_EXCEPTION;
  } catch(Crypto::PreconditionViolation& e) {
    return PRECONDITION_BASE - e.get_type();
  } catch (...) {
    return UNKNOWN_EXCEPTION;
  }
}

error_code_t Crypto_init_cbc_aes_signer(Crypto_cbc_aes_signer_t signer, const byte_t* mac_key, uint key_length, const byte_t* initial_state, number_size_t state_length)
{
  try {
    new(signer) CBCAESSigner(AES::Encrypter(mac_key, key_length), initial_state, state_length);
    return NO_EXCEPTION;
  } catch(Crypto::PreconditionViolation& e) {
    return PRECONDITION_BASE - e.get_type();
  } catch (...) {
    return UNKNOWN_EXCEPTION;
  }
}

error_code_t Crypto_init_cbc_aes_verifier(Crypto_cbc_aes_signer_t verifier, const byte_t* mac_key, uint key_length, const byte_t* initial_state, number_size_t state_length)
{
  try {
    new(verifier) CBCAESVerifier(AES::Encrypter(mac_key, key_length), initial_state, state_length);
    return NO_EXCEPTION;
  } catch(Crypto::PreconditionViolation& e) {
    return PRECONDITION_BASE - e.get_type();
  } catch (...) {
    return UNKNOWN_EXCEPTION;
  }
}

error_code_t Crypto_init_dh_key_exchange(Crypto_dh_key_exchange_t key_exchange)
{
  try {
    new(key_exchange) DH::KeyExchange();
    return NO_EXCEPTION;
  } catch(Crypto::PreconditionViolation& e) {
    return PRECONDITION_BASE - e.get_type();
  } catch (...) {
    return UNKNOWN_EXCEPTION;
  }
}

error_code_t Crypto_generate_aes_keys(const byte_t* secret, message_size_t secret_length, byte_t* cipher_key, byte_t* mac_key)
{
  try {
    // TODO This has to be exchanged since it might be insecure for some hash functions. (Probably not for SHA-2, though)
    byte_t digest[256];
    SHA2Hasher hasher (256);
    hasher.hash(secret, secret_length, digest + 0);
    memcpy(cipher_key, digest + 0, 128);
    memcpy(mac_key, digest + 128, 128);
    return NO_EXCEPTION;
  } catch(Crypto::PreconditionViolation& e) {
    return PRECONDITION_BASE - e.get_type();
  } catch (...) {
    return UNKNOWN_EXCEPTION;
  }
}

// Destructors
error_code_t Crypto_deinit_cbc_elgamal_encrypter(Crypto_cbc_elgamal_encrypter_t encrypter)
{
  try {
    delete reinterpret_cast<CBCElgamalEncrypter*>(encrypter);
    return NO_EXCEPTION;
  } catch(Crypto::PreconditionViolation& e) {
    return PRECONDITION_BASE - e.get_type();
  } catch (...) {
    return UNKNOWN_EXCEPTION;
  }
}

error_code_t Crypto_deinit_cbc_elgamal_decrypter(Crypto_cbc_elgamal_decrypter_t decrypter)
{
  try {
    delete reinterpret_cast<CBCElgamalDecrypter*>(decrypter);
    return NO_EXCEPTION;
  } catch(Crypto::PreconditionViolation& e) {
    return PRECONDITION_BASE - e.get_type();
  } catch (...) {
    return UNKNOWN_EXCEPTION;
  }
}

error_code_t Crypto_deinit_cbc_aes_encrypter(Crypto_cbc_aes_encrypter_t encrypter)
{
  try {
    if (typeid(encrypter) != typeid(CBCAESEncrypter*)) {
      return CAST_EXCEPTION;
    }
    delete reinterpret_cast<CBCAESEncrypter*>(encrypter);
    return NO_EXCEPTION;
  } catch(Crypto::PreconditionViolation& e) {
    return PRECONDITION_BASE - e.get_type();
  } catch (...) {
    return UNKNOWN_EXCEPTION;
  }
}

error_code_t Crypto_deinit_cbc_aes_decrypter(Crypto_cbc_aes_decrypter_t decrypter)
{
  try {
    if (typeid(decrypter) != typeid(CBCAESDecrypter*)) {
      return CAST_EXCEPTION;
    }
    delete reinterpret_cast<CBCAESDecrypter*>(decrypter);
    return NO_EXCEPTION;
  } catch(Crypto::PreconditionViolation& e) {
    return PRECONDITION_BASE - e.get_type();
  } catch (...) {
    return UNKNOWN_EXCEPTION;
  }
}

error_code_t Crypto_deinit_elgamal_signer(Crypto_elgamal_signer_t signer)
{
  try {
    if (typeid(signer) != typeid(Elgamal::Signer*)) {
      return CAST_EXCEPTION;
    }
    delete reinterpret_cast<Elgamal::Signer*>(signer);
    return NO_EXCEPTION;
  } catch(Crypto::PreconditionViolation& e) {
    return PRECONDITION_BASE - e.get_type();
  } catch (...) {
    return UNKNOWN_EXCEPTION;
  }
}

error_code_t Crypto_deinit_elgamal_verifier(Crypto_elgamal_verifier_t verifier)
{
  try {
    if (typeid(verifier) != typeid(Elgamal::Verifier*)) {
      return CAST_EXCEPTION;
    }
    delete reinterpret_cast<Elgamal::Verifier*>(verifier);
    return NO_EXCEPTION;
  } catch(Crypto::PreconditionViolation& e) {
    return PRECONDITION_BASE - e.get_type();
  } catch (...) {
    return UNKNOWN_EXCEPTION;
  }
}

error_code_t Crypto_deinit_cbc_aes_signer(Crypto_cbc_aes_signer_t signer)
{
  try {
    if (typeid(signer) != typeid(CBCAESSigner*)) {
      return CAST_EXCEPTION;
    }
    delete reinterpret_cast<CBCAESSigner*>(signer);
    return NO_EXCEPTION;
  } catch(Crypto::PreconditionViolation& e) {
    return PRECONDITION_BASE - e.get_type();
  } catch (...) {
    return UNKNOWN_EXCEPTION;
  }
}

error_code_t Crypto_deinit_cbc_aes_verifier(Crypto_cbc_aes_verifier_t verifier)
{
  try {
    if (typeid(verifier) != typeid(CBCAESVerifier*)) {
      return CAST_EXCEPTION;
    }
    delete reinterpret_cast<CBCAESVerifier*>(verifier);
    return NO_EXCEPTION;
  } catch(Crypto::PreconditionViolation& e) {
    return PRECONDITION_BASE - e.get_type();
  } catch (...) {
    return UNKNOWN_EXCEPTION;
  }
}

error_code_t Crypto_deinit_dh_key_exchange(Crypto_dh_key_exchange_t dh_key_exchange)
{
  try {
    if (typeid(dh_key_exchange) != typeid(DH::KeyExchange*)) {
      std::cout << typeid(dh_key_exchange).name() << " " << typeid(DH::KeyExchange*).name() << std::endl;
      return CAST_EXCEPTION;
    }
    delete reinterpret_cast<DH::KeyExchange*>(dh_key_exchange);
    return NO_EXCEPTION;
  } catch(Crypto::PreconditionViolation& e) {
    return PRECONDITION_BASE - e.get_type();
  } catch (...) {
    return UNKNOWN_EXCEPTION;
  }
}

// Queries
returned_message_size_t Crypto_cbc_elgamal_cipher_length(Crypto_cbc_elgamal_encrypter_t encrypter, message_size_t plain_length)
{
  try {
    return reinterpret_cast<CBCElgamalEncrypter*>(encrypter)->cipher_length(plain_length);
  } catch(Crypto::PreconditionViolation& e) {
    return PRECONDITION_BASE - e.get_type();
  } catch (...) {
    return UNKNOWN_EXCEPTION;
  }
}

returned_message_size_t Crypto_cbc_elgamal_max_plain_length(Crypto_cbc_elgamal_decrypter_t decrypter, message_size_t cipher_length)
{
  try {
    return reinterpret_cast<CBCElgamalDecrypter*>(decrypter)->max_plain_length(cipher_length);
  } catch(Crypto::PreconditionViolation& e) {
    return PRECONDITION_BASE - e.get_type();
  } catch (...) {
    return UNKNOWN_EXCEPTION;
  }
}

returned_message_size_t Crypto_cbc_aes_cipher_length(Crypto_cbc_aes_encrypter_t encrypter, message_size_t plain_length)
{
  try {
    if (typeid(encrypter) != typeid(CBCAESEncrypter*)) {
      return CAST_EXCEPTION;
    }
    return reinterpret_cast<CBCAESEncrypter*>(encrypter)->cipher_length(plain_length);
  } catch(Crypto::PreconditionViolation& e) {
    return PRECONDITION_BASE - e.get_type();
  } catch (...) {
    return UNKNOWN_EXCEPTION;
  }
}

returned_message_size_t Crypto_cbc_aes_max_plain_length(Crypto_cbc_aes_decrypter_t decrypter, message_size_t cipher_length)
{
  try {
    if (typeid(decrypter) != typeid(CBCAESDecrypter*)) {
      return CAST_EXCEPTION;
    }
    return reinterpret_cast<CBCAESDecrypter*>(decrypter)->max_plain_length(cipher_length);
  } catch(Crypto::PreconditionViolation& e) {
    return PRECONDITION_BASE - e.get_type();
  } catch (...) {
    return UNKNOWN_EXCEPTION;
  }
}

returned_message_size_t Crypto_elgamal_signature_length_signer(Crypto_elgamal_signer_t signer)
{
  try {
    if (typeid(signer) != typeid(Elgamal::Signer*)) {
      return CAST_EXCEPTION;
    }
    return reinterpret_cast<Elgamal::Signer*>(signer)->signature_length();
  } catch(Crypto::PreconditionViolation& e) {
    return PRECONDITION_BASE - e.get_type();
  } catch (...) {
    return UNKNOWN_EXCEPTION;
  }
}

returned_message_size_t Crypto_cbc_aes_signature_length_signer(Crypto_cbc_aes_signer_t signer)
{
  try {
    if (typeid(signer) != typeid(CBCAESSigner*)) {
      return CAST_EXCEPTION;
    }
    return reinterpret_cast<CBCAESSigner*>(signer)->signature_length();
  } catch(Crypto::PreconditionViolation& e) {
    return PRECONDITION_BASE - e.get_type();
  } catch (...) {
    return UNKNOWN_EXCEPTION;
  }
}

returned_message_size_t Crypto_elgamal_signature_length_verifier(Crypto_elgamal_verifier_t verifier)
{
  try {
    if (typeid(verifier) != typeid(Elgamal::Verifier*)) {
      return CAST_EXCEPTION;
    }
    return reinterpret_cast<Elgamal::Verifier*>(verifier)->signature_length();
  } catch(Crypto::PreconditionViolation& e) {
    return PRECONDITION_BASE - e.get_type();
  } catch (...) {
    return UNKNOWN_EXCEPTION;
  }
}

returned_message_size_t Crypto_cbc_aes_signature_length_verifier(Crypto_cbc_aes_verifier_t verifier)
{
  try {
    if (typeid(verifier) != typeid(CBCAESVerifier*)) {
      return CAST_EXCEPTION;
    }
    return reinterpret_cast<CBCAESVerifier*>(verifier)->signature_length();
  } catch(Crypto::PreconditionViolation& e) {
    return PRECONDITION_BASE - e.get_type();
  } catch (...) {
    return UNKNOWN_EXCEPTION;
  }
}

returned_message_size_t Crypto_dh_key_exchange_group_length(Crypto_dh_key_exchange_t key_exchange)
{
  try {
    if (typeid(key_exchange) != typeid(DH::KeyExchange*)) {
      return CAST_EXCEPTION;
    }
    DH::KeyExchange* ke = reinterpret_cast<DH::KeyExchange*>(key_exchange);
    if (!ke->group_chosen()) {
      return PRECONDITION_BASE + ConditionType::NoGroupChosen;
    }
    return ke->group_length();
  } catch(Crypto::PreconditionViolation& e) {
    return PRECONDITION_BASE - e.get_type();
  } catch (...) {
    return UNKNOWN_EXCEPTION;
  }
}

returned_message_size_t Crypto_dh_key_exchange_gen_power_length(Crypto_dh_key_exchange_t key_exchange)
{
  try {
    if (typeid(key_exchange) != typeid(DH::KeyExchange*)) {
      return CAST_EXCEPTION;
    }
    DH::KeyExchange* ke = reinterpret_cast<DH::KeyExchange*>(key_exchange);
    if (!ke->group_chosen()) {
      return PRECONDITION_BASE + ConditionType::NoGroupChosen;
    }
    if (!ke->own_part_chosen()) {
      ke->choose_own_part(random_device);
    }
    return ke->own_part_length();
  } catch(Crypto::PreconditionViolation& e) {
    return PRECONDITION_BASE - e.get_type();
  } catch (...) {
    return UNKNOWN_EXCEPTION;
  }
}

returned_message_size_t Crypto_dh_key_exchange_key_length(Crypto_dh_key_exchange_t key_exchange)
{
  try {
    if (typeid(key_exchange) != typeid(DH::KeyExchange*)) {
      return CAST_EXCEPTION;
    }
    DH::KeyExchange* ke = reinterpret_cast<DH::KeyExchange*>(key_exchange);
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
  } catch(Crypto::PreconditionViolation& e) {
    return PRECONDITION_BASE - e.get_type();
  } catch (...) {
    return UNKNOWN_EXCEPTION;
  }
}

returned_bool_t Crypto_dh_key_exchange_group_chosen(Crypto_dh_key_exchange_t key_exchange)
{
  try {
    if (typeid(key_exchange) != typeid(DH::KeyExchange*)) {
      return CAST_EXCEPTION;
    }
    return reinterpret_cast<DH::KeyExchange*>(key_exchange)->group_chosen();
  } catch(Crypto::PreconditionViolation& e) {
    return PRECONDITION_BASE - e.get_type();
  } catch (...) {
    return UNKNOWN_EXCEPTION;
  }
}

returned_bool_t Crypto_dh_key_exchange_own_part_chosen(Crypto_dh_key_exchange_t key_exchange)
{
  try {
    if (typeid(key_exchange) != typeid(DH::KeyExchange*)) {
      return CAST_EXCEPTION;
    }
    return reinterpret_cast<DH::KeyExchange*>(key_exchange)->own_part_chosen();
  } catch(Crypto::PreconditionViolation& e) {
    return PRECONDITION_BASE - e.get_type();
  } catch (...) {
    return UNKNOWN_EXCEPTION;
  }
}

returned_bool_t Crypto_dh_key_exchange_other_part_set(Crypto_dh_key_exchange_t key_exchange)
{
  try {
    if (typeid(key_exchange) != typeid(DH::KeyExchange*)) {
      return CAST_EXCEPTION;
    }
    return reinterpret_cast<DH::KeyExchange*>(key_exchange)->other_part_set();
  } catch(Crypto::PreconditionViolation& e) {
    return PRECONDITION_BASE - e.get_type();
  } catch (...) {
    return UNKNOWN_EXCEPTION;
  }
}

returned_bool_t Crypto_dh_key_exchange_key_ready(Crypto_dh_key_exchange_t key_exchange)
{
  try {
    if (typeid(key_exchange) != typeid(DH::KeyExchange*)) {
      return CAST_EXCEPTION;
    }
    return reinterpret_cast<DH::KeyExchange*>(key_exchange)->key_ready();
  } catch(Crypto::PreconditionViolation& e) {
    return PRECONDITION_BASE - e.get_type();
  } catch (...) {
    return UNKNOWN_EXCEPTION;
  }
}

// Operations
returned_message_size_t Crypto_cbc_elgamal_encrypt(Crypto_cbc_elgamal_encrypter_t encrypter, const byte_t* plain, message_size_t length, byte_t* cipher)
{
  try {
    return reinterpret_cast<CBCElgamalEncrypter*>(encrypter)->encrypt(plain, length, cipher);
  } catch(Crypto::PreconditionViolation& e) {
    return PRECONDITION_BASE - e.get_type();
  } catch (...) {
    return UNKNOWN_EXCEPTION;
  }
}

returned_message_size_t Crypto_cbc_elgamal_decrypt(Crypto_cbc_elgamal_decrypter_t decrypter, const byte_t* cipher, message_size_t length, byte_t* plain)
{
  try {
    return reinterpret_cast<CBCElgamalDecrypter*>(decrypter)->decrypt(cipher, length, plain);
  } catch(Crypto::PreconditionViolation& e) {
    return PRECONDITION_BASE - e.get_type();
  } catch (...) {
    return UNKNOWN_EXCEPTION;
  }
}

returned_message_size_t Crypto_cbc_aes_encrypt(Crypto_cbc_aes_encrypter_t encrypter, const byte_t* plain, message_size_t length, byte_t* cipher)
{
  try {
    if (typeid(encrypter) != typeid(CBCAESEncrypter*)) {
      return CAST_EXCEPTION;
    }
    return reinterpret_cast<CBCAESEncrypter*>(encrypter)->encrypt(plain, length, cipher);
  } catch(Crypto::PreconditionViolation& e) {
    return PRECONDITION_BASE - e.get_type();
  } catch (...) {
    return UNKNOWN_EXCEPTION;
  }
}

returned_message_size_t Crypto_cbc_aes_decrypt(Crypto_cbc_aes_decrypter_t decrypter, const byte_t* cipher, message_size_t length, byte_t* plain)
{
  try {
    if (typeid(decrypter) != typeid(CBCAESDecrypter*)) {
      return CAST_EXCEPTION;
    }
    return reinterpret_cast<CBCAESDecrypter*>(decrypter)->decrypt(cipher, length, plain);
  } catch(Crypto::PreconditionViolation& e) {
    return PRECONDITION_BASE - e.get_type();
  } catch (...) {
    return UNKNOWN_EXCEPTION;
  }
}

returned_message_size_t Crypto_elgamal_sign(Crypto_elgamal_signer_t signer, byte_t* message, message_size_t length)
{
  try {
    if (typeid(signer) != typeid(Elgamal::Signer*)) {
      return CAST_EXCEPTION;
    }
    return reinterpret_cast<Elgamal::Signer*>(signer)->sign(message, length);
  } catch(Crypto::PreconditionViolation& e) {
    return PRECONDITION_BASE - e.get_type();
  } catch (...) {
    return UNKNOWN_EXCEPTION;
  }
}

returned_bool_t Crypto_elgamal_verify(Crypto_elgamal_verifier_t verifier, const byte_t* message, message_size_t length)
{
  try {
    if (typeid(verifier) != typeid(Elgamal::Verifier*)) {
      return CAST_EXCEPTION;
    }
    return reinterpret_cast<Elgamal::Verifier*>(verifier)->verify(message, length);
  } catch(Crypto::PreconditionViolation& e) {
    return PRECONDITION_BASE - e.get_type();
  } catch (...) {
    return UNKNOWN_EXCEPTION;
  }
}

returned_message_size_t Crypto_cbc_aes_sign(Crypto_cbc_aes_signer_t signer, byte_t* message, message_size_t length)
{
  try {
    if (typeid(signer) != typeid(CBCAESSigner*)) {
      return CAST_EXCEPTION;
    }
    return reinterpret_cast<CBCAESSigner*>(signer)->sign(message, length);
  } catch(Crypto::PreconditionViolation& e) {
    return PRECONDITION_BASE - e.get_type();
  } catch (...) {
    return UNKNOWN_EXCEPTION;
  }
}

returned_bool_t Crypto_cbc_aes_verify(Crypto_cbc_aes_verifier_t verifier, const byte_t* message, message_size_t length)
{
  try {
    if (typeid(verifier) != typeid(CBCAESVerifier*)) {
      return CAST_EXCEPTION;
    }
    return reinterpret_cast<CBCAESVerifier*>(verifier)->verify(message, length);
  } catch(Crypto::PreconditionViolation& e) {
    return PRECONDITION_BASE - e.get_type();
  } catch (...) {
    return UNKNOWN_EXCEPTION;
  }
}

error_code_t Crypto_dh_key_exchange_choose_group(Crypto_dh_key_exchange_t key_exchange, number_size_t bits)
{
  try {
    if (typeid(key_exchange) != typeid(DH::KeyExchange*)) {
      return CAST_EXCEPTION;
    }
    reinterpret_cast<DH::KeyExchange*>(key_exchange)->choose_group(bits);
    return NO_EXCEPTION;
  } catch(Crypto::PreconditionViolation& e) {
    return PRECONDITION_BASE - e.get_type();
  } catch (...) {
    return UNKNOWN_EXCEPTION;
  }
}

returned_message_size_t Crypto_dh_key_exchange_group(Crypto_dh_key_exchange_t key_exchange, byte_t* raw_group)
{
  try {
    if (typeid(key_exchange) != typeid(DH::KeyExchange*)) {
      return CAST_EXCEPTION;
    }
    return reinterpret_cast<DH::KeyExchange*>(key_exchange)->write_group(raw_group);
  } catch(Crypto::PreconditionViolation& e) {
    return PRECONDITION_BASE - e.get_type();
  } catch (...) {
    return UNKNOWN_EXCEPTION;
  }
}

returned_message_size_t Crypto_dh_key_exchange_gen_power(Crypto_dh_key_exchange_t key_exchange, byte_t* raw_gen_power)
{
  try {
    if (typeid(key_exchange) != typeid(DH::KeyExchange*)) {
      return CAST_EXCEPTION;
    }
    return reinterpret_cast<DH::KeyExchange*>(key_exchange)->write_own_part(raw_gen_power);
  } catch(Crypto::PreconditionViolation& e) {
    return PRECONDITION_BASE - e.get_type();
  } catch (...) {
    return UNKNOWN_EXCEPTION;
  }
}

returned_message_size_t Crypto_dh_key_exchange_key(Crypto_dh_key_exchange_t key_exchange, byte_t* raw_key)
{
  try {
    if (typeid(key_exchange) != typeid(DH::KeyExchange*)) {
      return CAST_EXCEPTION;
    }
    return reinterpret_cast<DH::KeyExchange*>(key_exchange)->write_key(raw_key);
  } catch(Crypto::PreconditionViolation& e) {
    return PRECONDITION_BASE - e.get_type();
  } catch (...) {
    return UNKNOWN_EXCEPTION;
  }
}

returned_message_size_t Crypto_dh_key_exchange_set_other_gen_power(Crypto_dh_key_exchange_t key_exchange, byte_t* raw_gen_power, message_size_t length)
{
  try {
    if (typeid(key_exchange) != typeid(DH::KeyExchange*)) {
      return CAST_EXCEPTION;
    }
    reinterpret_cast<DH::KeyExchange*>(key_exchange)->read_other_part(raw_gen_power, length);
    return NO_EXCEPTION;
  } catch(Crypto::PreconditionViolation& e) {
    return PRECONDITION_BASE - e.get_type();
  } catch (...) {
    return UNKNOWN_EXCEPTION;
  }
}

returned_message_size_t Crypto_dh_key_exchange_set_group(Crypto_dh_key_exchange_t key_exchange, byte_t* raw_group, message_size_t length)
{
  try {
    if (typeid(key_exchange) != typeid(DH::KeyExchange*)) {
      return CAST_EXCEPTION;
    }
    reinterpret_cast<DH::KeyExchange*>(key_exchange)->read_group(raw_group, length);
    return NO_EXCEPTION;
  } catch(Crypto::PreconditionViolation& e) {
    return PRECONDITION_BASE - e.get_type();
  } catch (...) {
    return UNKNOWN_EXCEPTION;
  }
}

}
