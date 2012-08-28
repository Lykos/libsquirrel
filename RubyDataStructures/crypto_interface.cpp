#include "crypto_interface.h"
#include "elgamal_encrypter.h"
#include "elgamal_decrypter.h"
#include "elgamal_verifier.h"
#include "elgamal_signer.h"
#include "cbc_encrypter.h"
#include "cbc_decrypter.h"
#include "cbc_mac.h"
#include "aes_encrypter.h"
#include "aes_decrypter.h"
#include "dh_keyexchange.h"
#include "sha256hasher.h"
#include <cstring>

extern "C" {

using namespace Crypto;

typedef CBC::Encrypter<Elgamal::Encrypter> CBCElgamalEncrypter;

typedef CBC::Decrypter<Elgamal::Decrypter> CBCElgamalDecrypter;

typedef CBC::Encrypter<AES::Encrypter> CBCAESEncrypter;

typedef CBC::Decrypter<AES::Decrypter> CBCAESDecrypter;

typedef CBC::MAC<AES::Encrypter> CBCAESSigner;

typedef CBC::MAC<AES::Encrypter> CBCAESVerifier;

// Constructors
Crypto_cbc_elgamal_encrypter_t Crypto_init_cbc_elgamal_encrypter(const byte_t* raw_public_key, uint key_length, const byte_t* initial_state, number_size_t state_length)
{
  return new CBCElgamalEncrypter(Elgamal::Encrypter(raw_public_key, key_length), initial_state, state_length);
}

Crypto_cbc_elgamal_decrypter_t Crypto_init_cbc_elgamal_decrypter(const byte_t* raw_private_key, uint key_length, const byte_t* initial_state, number_size_t state_length)
{
  return new CBCElgamalDecrypter(Elgamal::Decrypter(raw_private_key, key_length), initial_state, state_length);
}

Crypto_cbc_aes_encrypter_t Crypto_init_cbc_aes_encrypter(const byte_t* cipher_key, uint key_length, const byte_t* initial_state, number_size_t state_length)
{
  return new CBCAESEncrypter(AES::Encrypter(cipher_key, key_length), initial_state, state_length);
}

Crypto_cbc_aes_decrypter_t Crypto_init_cbc_aes_decrypter(const byte_t* cipher_key, uint key_length, const byte_t* initial_state, number_size_t state_length)
{
  return new CBCAESDecrypter(AES::Decrypter(cipher_key, key_length), initial_state, state_length);
}

Crypto_elgamal_signer_t Crypto_init_elgamal_signer(const byte_t* raw_private_key, uint key_length)
{
  return new Elgamal::Signer(raw_private_key, key_length);
}

Crypto_elgamal_verifier_t Crypto_init_elgamal_verifier(const byte_t* raw_public_key, uint key_length)
{
  return new Elgamal::Verifier(raw_public_key, key_length);
}

Crypto_cbc_aes_signer_t Crypto_init_cbc_aes_signer(const byte_t* mac_key, uint key_length, const byte_t* initial_state, number_size_t state_length)
{
  return new CBCAESSigner(AES::Encrypter(mac_key, key_length), initial_state, state_length);
}

Crypto_cbc_aes_verifier_t Crypto_init_cbc_aes_verifier(const byte_t* mac_key, uint key_length, const byte_t* initial_state, number_size_t state_length)
{
  return new CBCAESVerifier(AES::Encrypter(mac_key, key_length), initial_state, state_length);
}

Crypto_dh_key_exchange_t Crypto_init_dh_key_exchange()
{
  return new DH::KeyExchange();
}

Crypto_aes_key_pair_t Crypto_generate_aes_keys(const byte_t* secret, message_size_t secret_length)
{
  // TODO This has to be exchanged since it might be insecure for some hash functions. (Probably not for SHA-2, though)
  byte_t digest[SHA256_DIGEST_BYTE_SIZE];
  SHA2Hasher hasher;
  hasher.hash(secret, secret_length, digest + 0);
  Crypto_aes_key_pair_t pair;
  pair.cipher_key = new byte_t[SHA256_DIGEST_BYTE_SIZE / 2];
  pair.mac_key = new byte_t[SHA256_DIGEST_BYTE_SIZE / 2];
  memcpy(pair.cipher_key, digest + 0, SHA256_DIGEST_BYTE_SIZE / 2);
  memcpy(pair.cipher_key, digest + SHA256_DIGEST_BYTE_SIZE / 2, SHA256_DIGEST_BYTE_SIZE / 2);
  return pair;
}

// Destructors
void Crypto_deinit_cbc_elgamal_encrypter(Crypto_cbc_elgamal_encrypter_t encrypter)
{
  delete static_cast<CBCElgamalEncrypter*>(encrypter);
}

void Crypto_deinit_cbc_elgamal_decrypter(Crypto_cbc_elgamal_decrypter_t decrypter)
{
  delete static_cast<CBCElgamalDecrypter*>(decrypter);
}

void Crypto_deinit_cbc_aes_encrypter(Crypto_cbc_aes_encrypter_t encrypter)
{
  delete static_cast<CBCAESEncrypter*>(encrypter);
}

void Crypto_deinit_cbc_aes_decrypter(Crypto_cbc_aes_decrypter_t decrypter)
{
  delete static_cast<CBCAESDecrypter*>(decrypter);
}

void Crypto_deinit_elgamal_signer(Crypto_elgamal_signer_t signer)
{
  delete static_cast<Elgamal::Signer*>(signer);
}

void Crypto_deinit_elgamal_verifier(Crypto_elgamal_verifier_t verifier)
{
  delete static_cast<Elgamal::Verifier*>(verifier);
}

void Crypto_deinit_cbc_aes_signer(Crypto_cbc_aes_signer_t signer)
{
  delete static_cast<CBCAESSigner*>(signer);
}

void Crypto_deinit_cbc_aes_verifier(Crypto_cbc_aes_verifier_t verifier)
{
  delete static_cast<CBCAESVerifier*>(verifier);
}

void Crypto_deinit_dh_key_exchange(Crypto_dh_key_exchange_t dh_key_exchange)
{
  delete static_cast<DH::KeyExchange*>(dh_key_exchange);
}

void Crypto_deinit_aes_keys(Crypto_aes_key_pair_t key_pair)
{
  delete[] key_pair.cipher_key;
  delete[] key_pair.mac_key;
}

// Queries
message_size_t Crypto_cbc_elgamal_cipher_length(Crypto_cbc_elgamal_encrypter_t encrypter, message_size_t plain_length)
{
  return static_cast<CBCElgamalEncrypter*>(encrypter)->get_cipher_length(plain_length);
}

message_size_t Crypto_cbc_elgamal_max_plain_length(Crypto_cbc_elgamal_decrypter_t decrypter, message_size_t cipher_length)
{
  return static_cast<CBCElgamalDecrypter*>(decrypter)->get_max_plain_length(cipher_length);
}

message_size_t Crypto_cbc_aes_cipher_length(Crypto_cbc_aes_encrypter_t encrypter, message_size_t plain_length)
{
  return static_cast<CBCAESEncrypter*>(encrypter)->get_cipher_length(plain_length);
}

message_size_t Crypto_cbc_aes_max_plain_length(Crypto_cbc_aes_decrypter_t decrypter, message_size_t cipher_length)
{
  return static_cast<CBCAESDecrypter*>(decrypter)->get_max_plain_length(cipher_length);
}

message_size_t Crypto_elgamal_signature_length_signer(Crypto_elgamal_signer_t signer)
{
  return static_cast<Elgamal::Signer*>(signer)->signature_length();
}

message_size_t Crypto_cbc_aes_signature_length_signer(Crypto_cbc_aes_signer_t signer)
{
  return static_cast<CBCAESSigner*>(signer)->signature_length();
}

message_size_t Crypto_elgamal_signature_length_verifier(Crypto_elgamal_verifier_t verifier)
{
  return static_cast<Elgamal::Verifier*>(verifier)->signature_length();
}

message_size_t Crypto_cbc_aes_signature_length_verifier(Crypto_cbc_aes_verifier_t verifier)
{
  return static_cast<CBCAESVerifier*>(verifier)->signature_length();
}

message_size_t Crypto_dh_key_exchange_group_length(Crypto_dh_key_exchange_t key_exchange)
{
  DH::KeyExchange* ke = static_cast<DH::KeyExchange*>(key_exchange);
  if (!ke->group_chosen()) {
    return ke->group_length();
  } else {
    return 0;
  }
}

message_size_t Crypto_dh_key_exchange_gen_power_length(Crypto_dh_key_exchange_t key_exchange)

message_size_t Crypto_dh_key_exchange_key_length(Crypto_dh_key_exchange_t key_exchange)

bool_t Crypto_dh_key_exchange_group_chosen(Crypto_dh_key_exchange_t key_exchange)

bool_t Crypto_dh_key_exchange_exponent_chosen(Crypto_dh_key_exchange_t key_exchange)

bool_t Crypto_dh_key_exchange_other_partial_set(Crypto_dh_key_exchange_t key_exchange)

bool_t Crypto_dh_key_exchange_key_ready(Crypto_dh_key_exchange_t key_exchange)

// Operations
message_size_t Crypto_cbc_elgamal_encrypt(Crypto_cbc_elgamal_encrypter_t encrypter, const byte_t* plain, message_size_t length, byte_t* cipher)

message_size_t Crypto_cbc_elgamal_decrypt(Crypto_cbc_elgamal_decrypter_t decrypter, const byte_t* cipher, message_size_t length, byte_t* plain)

message_size_t Crypto_cbc_aes_encrypt(Crypto_cbc_aes_encrypter_t encrypter, const byte_t* plain, message_size_t length, byte_t* cipher)

message_size_t Crypto_cbc_aes_decrypt(Crypto_cbc_aes_decrypter_t decrypter, const byte_t* cipher, message_size_t length, byte_t* plain)

message_size_t Crypto_elgamal_sign(Crypto_cbc_elgamal_encrypter_t encrypter, byte_t* message, message_size_t length)

bool_t Crypto_elgamal_verify(Crypto_cbc_elgamal_decrypter_t decrypter, byte_t* message, message_size_t length)

message_size_t Crypto_cbc_aes_sign(Crypto_cbc_aes_encrypter_t encrypter, const byte_t* message, message_size_t length)

bool_t Crypto_cbc_aes_verify(Crypto_cbc_aes_decrypter_t decrypter, const byte_t* message, message_size_t length)

message_size_t Crypto_dh_key_exchange_group(Crypto_dh_key_exchange_t key_exchange, byte_t* raw_group)

message_size_t Crypto_dh_key_exchange_gen_power(Crypto_dh_key_exchange_t key_exchange, byte_t* raw_gen_power)

message_size_t Crypto_dh_key_exchange_key(Crypto_dh_key_exchange_t key_exchange, byte_t* raw_key)

message_size_t Crypto_dh_key_exchange_set_other_gen_power(Crypto_dh_key_exchange_t key_exchange, byte_t* raw_gen_power, message_size_t length)

message_size_t Crypto_dh_key_exchange_set_group(Crypto_dh_key_exchange_t key_exchange, byte_t* raw_group, message_size_t length)

}
