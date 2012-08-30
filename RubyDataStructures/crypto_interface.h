#ifndef CRYPTO_INTERFACE_H
#define CRYPTO_INTERFACE_H

#include "Crypto/conditiontype.h"

#ifdef __cplusplus
extern "C" {
#endif

// Error codes
#define NO_EXCEPTION 1
#define UNKNOWN_EXCEPTION (-1)
#define TYPE_EXCEPTION (-2)
#define DOUBLE_INITIALIZE_EXCEPTION (-3)
#define NO_INITIALIZE_EXCEPTION (-4)
#define PRECONDITION_BASE (-20)

typedef unsigned char byte_t;

typedef unsigned int number_size_t;

typedef unsigned long int message_size_t;

typedef char error_code_t;

// Either a boolean or a negative error code
typedef char returned_bool_t;

// Either the size or a negative error code
typedef long int returned_message_size_t;

typedef enum {
  CryptoElgamalKeyGenerator,
  CryptoCBCElgamalEncrypter,
  CryptoCBCElgamalDecrypter,
  CryptoCBCAESEncrypter,
  CryptoCBCAESDecrypter,
  CryptoElgamalSigner,
  CryptoElgamalVerifier,
  CryptoCBCAESSigner,
  CryptoCBCAESVerifier,
  CryptoDHKeyExchange
} Crypto_type_t;

typedef struct {
  Crypto_type_t type;
  void* ptr;
} Crypto_object_t;

// Constructors
error_code_t Crypto_init_elgamal_key_generator(Crypto_object_t* key_generator);

error_code_t Crypto_init_cbc_elgamal_encrypter(Crypto_object_t* encrypter, const byte_t* raw_public_key, number_size_t key_length, const byte_t* initial_state, number_size_t state_length);

error_code_t Crypto_init_cbc_elgamal_decrypter(Crypto_object_t* decrypter, const byte_t* raw_private_key, number_size_t key_length, const byte_t* initial_state, number_size_t state_length);

error_code_t Crypto_init_cbc_aes_encrypter(Crypto_object_t* encrypter, const byte_t* cipher_key, number_size_t key_length, const byte_t* initial_state, number_size_t state_length);

error_code_t Crypto_init_cbc_aes_decrypter(Crypto_object_t* decrypter, const byte_t* cipher_key, number_size_t key_length, const byte_t* initial_state, number_size_t state_length);

error_code_t Crypto_init_elgamal_signer(Crypto_object_t* signer, const byte_t* raw_private_key, number_size_t key_length);

error_code_t Crypto_init_elgamal_verifier(Crypto_object_t* verifier, const byte_t* raw_public_key, number_size_t key_length);

error_code_t Crypto_init_cbc_aes_signer(Crypto_object_t* signer, const byte_t* mac_key, number_size_t key_length, const byte_t* initial_state, number_size_t state_length);

error_code_t Crypto_init_cbc_aes_verifier(Crypto_object_t* verifier, const byte_t* mac_key, number_size_t key_length, const byte_t* initial_state, number_size_t state_length);

error_code_t Crypto_init_dh_key_exchange(Crypto_object_t* key_exchange);

// Destructors
error_code_t Crypto_deinit_cbc_elgamal_encrypter(Crypto_object_t* encrypter);

error_code_t Crypto_deinit_cbc_elgamal_decrypter(Crypto_object_t* decrypter);

error_code_t Crypto_deinit_cbc_aes_encrypter(Crypto_object_t* encrypter);

error_code_t Crypto_deinit_cbc_aes_decrypter(Crypto_object_t* decrypter);

error_code_t Crypto_deinit_elgamal_signer(Crypto_object_t* signer);

error_code_t Crypto_deinit_elgamal_verifier(Crypto_object_t* verifier);

error_code_t Crypto_deinit_cbc_aes_signer(Crypto_object_t* signer);

error_code_t Crypto_deinit_cbc_aes_verifier(Crypto_object_t* verifier);

error_code_t Crypto_deinit_dh_key_exchange(Crypto_object_t* dh_key_exchange);

// Queries
returned_message_size_t Crypto_cbc_elgamal_cipher_length(Crypto_object_t* encrypter, message_size_t plain_length);

returned_message_size_t Crypto_cbc_elgamal_max_plain_length(Crypto_object_t* decrypter, message_size_t cipher_length);

returned_message_size_t Crypto_cbc_aes_cipher_length(Crypto_object_t* encrypter, message_size_t plain_length);

returned_message_size_t Crypto_cbc_aes_max_plain_length(Crypto_object_t* decrypter, message_size_t cipher_length);

returned_message_size_t Crypto_elgamal_signature_length_signer(Crypto_object_t* signer);

returned_message_size_t Crypto_elgamal_signature_length_verifier(Crypto_object_t* verifier);

returned_message_size_t Crypto_cbc_aes_signature_length_signer(Crypto_object_t* signer);

returned_message_size_t Crypto_cbc_aes_signature_length_verifier(Crypto_object_t* verifier);

returned_message_size_t Crypto_dh_key_exchange_group_length(Crypto_object_t* key_exchange);

returned_message_size_t Crypto_dh_key_exchange_gen_power_length(Crypto_object_t* key_exchange);

returned_message_size_t Crypto_dh_key_exchange_key_length(Crypto_object_t* key_exchange);

returned_bool_t Crypto_dh_key_exchange_group_chosen(Crypto_object_t* key_exchange);

returned_bool_t Crypto_dh_key_exchange_own_part_chosen(Crypto_object_t* key_exchange);

returned_bool_t Crypto_dh_key_exchange_other_part_set(Crypto_object_t* key_exchange);

returned_bool_t Crypto_dh_key_exchange_key_ready(Crypto_object_t* key_exchange);

// Operations
error_code_t Crypto_generate_aes_keys(const byte_t* secret, message_size_t secret_length, byte_t* cipher_key, byte_t* mac_key);

returned_message_size_t Crypto_cbc_elgamal_encrypt(Crypto_object_t* encrypter, const byte_t* plain, message_size_t length, byte_t* cipher);

returned_message_size_t Crypto_cbc_elgamal_decrypt(Crypto_object_t* decrypter, const byte_t* cipher, message_size_t length, byte_t* plain);

returned_message_size_t Crypto_cbc_aes_encrypt(Crypto_object_t* encrypter, const byte_t* plain, message_size_t length, byte_t* cipher);

returned_message_size_t Crypto_cbc_aes_decrypt(Crypto_object_t* decrypter, const byte_t* cipher, message_size_t length, byte_t* plain);

returned_message_size_t Crypto_elgamal_sign(Crypto_object_t* signer, byte_t* message, message_size_t length);

returned_bool_t Crypto_elgamal_verify(Crypto_object_t* verifier, const byte_t* message, message_size_t length);

returned_message_size_t Crypto_cbc_aes_sign(Crypto_object_t* signer, byte_t* message, message_size_t length);

returned_bool_t Crypto_cbc_aes_verify(Crypto_object_t* verifier, const byte_t* message, message_size_t length);

error_code_t Crypto_dh_key_exchange_choose_group(Crypto_object_t* key_exchange, number_size_t bits);

returned_message_size_t Crypto_dh_key_exchange_group(Crypto_object_t* key_exchange, byte_t* raw_group);

returned_message_size_t Crypto_dh_key_exchange_gen_power(Crypto_object_t* key_exchange, byte_t* raw_gen_power);

returned_message_size_t Crypto_dh_key_exchange_key(Crypto_object_t* key_exchange, byte_t* raw_key);

returned_message_size_t Crypto_dh_key_exchange_set_other_gen_power(Crypto_object_t* key_exchange, byte_t* raw_gen_power, message_size_t length);

returned_message_size_t Crypto_dh_key_exchange_set_group(Crypto_object_t* key_exchange, byte_t* raw_group, message_size_t length);

#ifdef __cplusplus
}
#endif

#endif // CRYPTO_INTERFACE_H
