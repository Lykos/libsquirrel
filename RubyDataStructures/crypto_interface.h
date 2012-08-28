#ifndef CRYPTO_INTERFACE_H
#define CRYPTO_INTERFACE_H

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned char byte_t;

typedef unsigned int number_size_t;

typedef unsigned long int message_size_t;

typedef byte_t bool_t;

typedef struct {
  byte_t* cipher_key;
  byte_t* mac_key;
} Crypto_aes_key_pair_t;

typedef void* Crypto_cbc_elgamal_encrypter_t;

typedef void* Crypto_cbc_elgamal_decrypter_t;

typedef void* Crypto_cbc_aes_encrypter_t;

typedef void* Crypto_cbc_aes_decrypter_t;

typedef void* Crypto_elgamal_signer_t;

typedef void* Crypto_elgamal_verifier_t;

typedef void* Crypto_cbc_aes_signer_t;

typedef void* Crypto_cbc_aes_verifier_t;

typedef void* Crypto_dh_key_exchange_t;

typedef void* Crypto_group_t;

typedef void* Crypto_partial_key_t;

// Constructors
Crypto_cbc_elgamal_encrypter_t Crypto_init_cbc_elgamal_encrypter(const byte_t* raw_public_key, number_size_t key_length, const byte_t* initial_state, number_size_t state_length);

Crypto_cbc_elgamal_decrypter_t Crypto_init_cbc_elgamal_decrypter(const byte_t* raw_private_key, number_size_t key_length, const byte_t* initial_state, number_size_t state_length);

Crypto_cbc_aes_encrypter_t Crypto_init_cbc_aes_encrypter(const byte_t* cipher_key, number_size_t key_length, const byte_t* initial_state, number_size_t state_length);

Crypto_cbc_aes_decrypter_t Crypto_init_cbc_aes_decrypter(const byte_t* cipher_key, number_size_t key_length, const byte_t* initial_state, number_size_t state_length);

Crypto_elgamal_signer_t Crypto_init_elgamal_signer(const byte_t* raw_private_key, number_size_t key_length);

Crypto_elgamal_verifier_t Crypto_init_elgamal_verifier(const byte_t* raw_public_key, number_size_t key_length);

Crypto_cbc_aes_signer_t Crypto_init_cbc_aes_signer(const byte_t* mac_key, number_size_t key_length, const byte_t* initial_state, number_size_t state_length);

Crypto_cbc_aes_verifier_t Crypto_init_cbc_aes_verifier(const byte_t* mac_key, number_size_t key_length, const byte_t* initial_state, number_size_t state_length);

Crypto_dh_key_exchange_t Crypto_init_dh_key_exchange();

Crypto_aes_key_pair_t Crypto_generate_aes_keys(const byte_t* secret, message_size_t secret_length);

// Destructors
void Crypto_deinit_cbc_elgamal_encrypter(Crypto_cbc_elgamal_encrypter_t encrypter);

void Crypto_deinit_cbc_elgamal_decrypter(Crypto_cbc_elgamal_decrypter_t decrypter);

void Crypto_deinit_cbc_aes_encrypter(Crypto_cbc_aes_encrypter_t encrypter);

void Crypto_deinit_cbc_aes_decrypter(Crypto_cbc_aes_decrypter_t decrypter);

void Crypto_deinit_elgamal_signer(Crypto_elgamal_signer_t signer);

void Crypto_deinit_elgamal_verifier(Crypto_elgamal_verifier_t verifier);

void Crypto_deinit_cbc_aes_signer(Crypto_cbc_aes_signer_t signer);

void Crypto_deinit_cbc_aes_verifier(Crypto_cbc_aes_verifier_t verifier);

void Crypto_deinit_dh_key_exchange(Crypto_dh_key_exchange_t dh_key_exchange);

void Crypto_deinit_aes_keys(Crypto_aes_key_pair_t key_pair);

// Queries
message_size_t Crypto_cbc_elgamal_cipher_length(Crypto_cbc_elgamal_encrypter_t encrypter, message_size_t plain_length);

message_size_t Crypto_cbc_elgamal_max_plain_length(Crypto_cbc_elgamal_decrypter_t decrypter, message_size_t cipher_length);

message_size_t Crypto_cbc_aes_cipher_length(Crypto_cbc_aes_encrypter_t encrypter, message_size_t plain_length);

message_size_t Crypto_cbc_aes_max_plain_length(Crypto_cbc_aes_decrypter_t decrypter, message_size_t cipher_length);

message_size_t Crypto_elgamal_signature_length_signer(Crypto_elgamal_signer_t signer);

message_size_t Crypto_cbc_aes_signature_length_signer(Crypto_cbc_aes_signer_t signer);

message_size_t Crypto_elgamal_signature_length_verifier(Crypto_elgamal_verifier_t verifier);

message_size_t Crypto_cbc_aes_signature_length_verifier(Crypto_cbc_aes_verifier_t verifier);

message_size_t Crypto_dh_key_exchange_group_length(Crypto_dh_key_exchange_t key_exchange);

message_size_t Crypto_dh_key_exchange_gen_power_length(Crypto_dh_key_exchange_t key_exchange);

message_size_t Crypto_dh_key_exchange_key_length(Crypto_dh_key_exchange_t key_exchange);

bool_t Crypto_dh_key_exchange_group_chosen(Crypto_dh_key_exchange_t key_exchange);

bool_t Crypto_dh_key_exchange_exponent_chosen(Crypto_dh_key_exchange_t key_exchange);

bool_t Crypto_dh_key_exchange_other_partial_set(Crypto_dh_key_exchange_t key_exchange);

bool_t Crypto_dh_key_exchange_key_ready(Crypto_dh_key_exchange_t key_exchange);

// Operations
message_size_t Crypto_cbc_elgamal_encrypt(Crypto_cbc_elgamal_encrypter_t encrypter, const byte_t* plain, message_size_t length, byte_t* cipher);

message_size_t Crypto_cbc_elgamal_decrypt(Crypto_cbc_elgamal_decrypter_t decrypter, const byte_t* cipher, message_size_t length, byte_t* plain);

message_size_t Crypto_cbc_aes_encrypt(Crypto_cbc_aes_encrypter_t encrypter, const byte_t* plain, message_size_t length, byte_t* cipher);

message_size_t Crypto_cbc_aes_decrypt(Crypto_cbc_aes_decrypter_t decrypter, const byte_t* cipher, message_size_t length, byte_t* plain);

message_size_t Crypto_elgamal_sign(Crypto_cbc_elgamal_encrypter_t encrypter, byte_t* message, message_size_t length);

bool_t Crypto_elgamal_verify(Crypto_cbc_elgamal_decrypter_t decrypter, byte_t* message, message_size_t length);

message_size_t Crypto_cbc_aes_sign(Crypto_cbc_aes_encrypter_t encrypter, const byte_t* message, message_size_t length);

bool_t Crypto_cbc_aes_verify(Crypto_cbc_aes_decrypter_t decrypter, const byte_t* message, message_size_t length);

message_size_t Crypto_dh_key_exchange_group(Crypto_dh_key_exchange_t key_exchange, byte_t* raw_group);

message_size_t Crypto_dh_key_exchange_gen_power(Crypto_dh_key_exchange_t key_exchange, byte_t* raw_gen_power);

message_size_t Crypto_dh_key_exchange_key(Crypto_dh_key_exchange_t key_exchange, byte_t* raw_key);

message_size_t Crypto_dh_key_exchange_set_other_gen_power(Crypto_dh_key_exchange_t key_exchange, byte_t* raw_gen_power, message_size_t length);

message_size_t Crypto_dh_key_exchange_set_group(Crypto_dh_key_exchange_t key_exchange, byte_t* raw_group, message_size_t length);

#ifdef __cplusplus
}
#endif

#endif // CRYPTO_INTERFACE_H
