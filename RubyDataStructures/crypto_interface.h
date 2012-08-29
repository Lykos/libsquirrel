#ifndef CRYPTO_INTERFACE_H
#define CRYPTO_INTERFACE_H

#ifdef __cplusplus
extern "C" {
#endif

// Error codes
#define NO_EXCEPTION 1
#define UNKNOWN_EXCEPTION (-1)
#define CAST_EXCEPTION (-2)
#define KEY_EXCHANGE_NO_GROUP_CHOSEN (-12)
#define KEY_EXCHANGE_NO_OWN_PART_CHOSEN (-13)
#define KEY_EXCHANGE_NO_OTHER_PART_SET (-14)
#define KEY_EXCHANGE_KEY_NOT_READY (-15)
#define PRECONDITION_BASE (-20)

typedef unsigned char byte_t;

typedef unsigned int number_size_t;

typedef unsigned long int message_size_t;

typedef char error_code_t;

// Either a boolean or a negative error code
typedef char returned_bool_t;

// Either the size or a negative error code
typedef long int returned_message_size_t;

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

extern const message_size_t Crypto_cbc_elgamal_encrypter_length;

typedef struct {
  Crypto_cbc_elgamal_encrypter_t encrypter;
  error_code_t error_code;
} returned_Crypto_cbc_elgamal_encrypter_t;

typedef struct {
  Crypto_cbc_elgamal_decrypter_t decrypter;
  error_code_t error_code;
} returned_Crypto_cbc_elgamal_decrypter_t;

typedef struct {
  Crypto_cbc_aes_encrypter_t encrypter;
  error_code_t error_code;
} returned_Crypto_cbc_aes_encrypter_t;


typedef struct {
  Crypto_cbc_aes_decrypter_t decrypter;
  error_code_t error_code;
} returned_Crypto_cbc_aes_decrypter_t;


typedef struct {
  Crypto_elgamal_signer_t signer;
  error_code_t error_code;
} returned_Crypto_elgamal_signer_t;


typedef struct {
  Crypto_elgamal_verifier_t verifier;
  error_code_t error_code;
} returned_Crypto_elgamal_verifier_t;


typedef struct {
  Crypto_cbc_aes_signer_t signer;
  error_code_t error_code;
} returned_Crypto_cbc_aes_signer_t;


typedef struct {
  Crypto_cbc_aes_verifier_t verifier;
  error_code_t error_code;
} returned_Crypto_cbc_aes_verifier_t;


typedef struct {
  Crypto_dh_key_exchange_t key_exchange;
  error_code_t error_code;
} returned_Crypto_dh_key_exchange_t;


typedef struct {
  Crypto_group_t group;
  error_code_t error_code;
} returned_Crypto_group_t;

typedef struct {
  byte_t* cipher_key;
  byte_t* mac_key;
  error_code_t error_code;
} returned_Crypto_aes_key_pair_t;

// Constructors
error_code_t Crypto_init_cbc_elgamal_encrypter(Crypto_cbc_elgamal_encrypter_t encrypter, const byte_t* raw_public_key, number_size_t key_length, const byte_t* initial_state, number_size_t state_length);

returned_Crypto_cbc_elgamal_decrypter_t Crypto_init_cbc_elgamal_decrypter(const byte_t* raw_private_key, number_size_t key_length, const byte_t* initial_state, number_size_t state_length);

returned_Crypto_cbc_aes_encrypter_t Crypto_init_cbc_aes_encrypter(const byte_t* cipher_key, number_size_t key_length, const byte_t* initial_state, number_size_t state_length);

returned_Crypto_cbc_aes_decrypter_t Crypto_init_cbc_aes_decrypter(const byte_t* cipher_key, number_size_t key_length, const byte_t* initial_state, number_size_t state_length);

returned_Crypto_elgamal_signer_t Crypto_init_elgamal_signer(const byte_t* raw_private_key, number_size_t key_length);

returned_Crypto_elgamal_verifier_t Crypto_init_elgamal_verifier(const byte_t* raw_public_key, number_size_t key_length);

returned_Crypto_cbc_aes_signer_t Crypto_init_cbc_aes_signer(const byte_t* mac_key, number_size_t key_length, const byte_t* initial_state, number_size_t state_length);

returned_Crypto_cbc_aes_verifier_t Crypto_init_cbc_aes_verifier(const byte_t* mac_key, number_size_t key_length, const byte_t* initial_state, number_size_t state_length);

returned_Crypto_dh_key_exchange_t Crypto_init_dh_key_exchange();

returned_Crypto_aes_key_pair_t Crypto_generate_aes_keys(const byte_t* secret, message_size_t secret_length);

// Destructors
error_code_t Crypto_deinit_cbc_elgamal_encrypter(Crypto_cbc_elgamal_encrypter_t encrypter);

error_code_t Crypto_deinit_cbc_elgamal_decrypter(Crypto_cbc_elgamal_decrypter_t decrypter);

error_code_t Crypto_deinit_cbc_aes_encrypter(Crypto_cbc_aes_encrypter_t encrypter);

error_code_t Crypto_deinit_cbc_aes_decrypter(Crypto_cbc_aes_decrypter_t decrypter);

error_code_t Crypto_deinit_elgamal_signer(Crypto_elgamal_signer_t signer);

error_code_t Crypto_deinit_elgamal_verifier(Crypto_elgamal_verifier_t verifier);

error_code_t Crypto_deinit_cbc_aes_signer(Crypto_cbc_aes_signer_t signer);

error_code_t Crypto_deinit_cbc_aes_verifier(Crypto_cbc_aes_verifier_t verifier);

error_code_t Crypto_deinit_dh_key_exchange(Crypto_dh_key_exchange_t dh_key_exchange);

// Queries
returned_message_size_t Crypto_cbc_elgamal_cipher_length(Crypto_cbc_elgamal_encrypter_t encrypter, message_size_t plain_length);

returned_message_size_t Crypto_cbc_elgamal_max_plain_length(Crypto_cbc_elgamal_decrypter_t decrypter, message_size_t cipher_length);

returned_message_size_t Crypto_cbc_aes_cipher_length(Crypto_cbc_aes_encrypter_t encrypter, message_size_t plain_length);

returned_message_size_t Crypto_cbc_aes_max_plain_length(Crypto_cbc_aes_decrypter_t decrypter, message_size_t cipher_length);

returned_message_size_t Crypto_elgamal_signature_length_signer(Crypto_elgamal_signer_t signer);

returned_message_size_t Crypto_cbc_aes_signature_length_signer(Crypto_cbc_aes_signer_t signer);

returned_message_size_t Crypto_elgamal_signature_length_verifier(Crypto_elgamal_verifier_t verifier);

returned_message_size_t Crypto_cbc_aes_signature_length_verifier(Crypto_cbc_aes_verifier_t verifier);

returned_message_size_t Crypto_dh_key_exchange_group_length(Crypto_dh_key_exchange_t key_exchange);

returned_message_size_t Crypto_dh_key_exchange_gen_power_length(Crypto_dh_key_exchange_t key_exchange);

returned_message_size_t Crypto_dh_key_exchange_key_length(Crypto_dh_key_exchange_t key_exchange);

returned_bool_t Crypto_dh_key_exchange_group_chosen(Crypto_dh_key_exchange_t key_exchange);

returned_bool_t Crypto_dh_key_exchange_own_part_chosen(Crypto_dh_key_exchange_t key_exchange);

returned_bool_t Crypto_dh_key_exchange_other_part_set(Crypto_dh_key_exchange_t key_exchange);

returned_bool_t Crypto_dh_key_exchange_key_ready(Crypto_dh_key_exchange_t key_exchange);

// Operations
returned_message_size_t Crypto_cbc_elgamal_encrypt(Crypto_cbc_elgamal_encrypter_t encrypter, const byte_t* plain, message_size_t length, byte_t* cipher);

returned_message_size_t Crypto_cbc_elgamal_decrypt(Crypto_cbc_elgamal_decrypter_t decrypter, const byte_t* cipher, message_size_t length, byte_t* plain);

returned_message_size_t Crypto_cbc_aes_encrypt(Crypto_cbc_aes_encrypter_t encrypter, const byte_t* plain, message_size_t length, byte_t* cipher);

returned_message_size_t Crypto_cbc_aes_decrypt(Crypto_cbc_aes_decrypter_t decrypter, const byte_t* cipher, message_size_t length, byte_t* plain);

returned_message_size_t Crypto_elgamal_sign(Crypto_cbc_elgamal_encrypter_t signer, byte_t* message, message_size_t length);

returned_bool_t Crypto_elgamal_verify(Crypto_cbc_elgamal_decrypter_t verifier, const byte_t* message, message_size_t length);

returned_message_size_t Crypto_cbc_aes_sign(Crypto_cbc_aes_encrypter_t signer, byte_t* message, message_size_t length);

returned_bool_t Crypto_cbc_aes_verify(Crypto_cbc_aes_decrypter_t verifier, const byte_t* message, message_size_t length);

error_code_t Crypto_dh_key_exchange_choose_group(Crypto_dh_key_exchange_t key_exchange, number_size_t bits);

returned_message_size_t Crypto_dh_key_exchange_group(Crypto_dh_key_exchange_t key_exchange, byte_t* raw_group);

returned_message_size_t Crypto_dh_key_exchange_gen_power(Crypto_dh_key_exchange_t key_exchange, byte_t* raw_gen_power);

returned_message_size_t Crypto_dh_key_exchange_key(Crypto_dh_key_exchange_t key_exchange, byte_t* raw_key);

returned_message_size_t Crypto_dh_key_exchange_set_other_gen_power(Crypto_dh_key_exchange_t key_exchange, byte_t* raw_gen_power, message_size_t length);

returned_message_size_t Crypto_dh_key_exchange_set_group(Crypto_dh_key_exchange_t key_exchange, byte_t* raw_group, message_size_t length);

#ifdef __cplusplus
}
#endif

#endif // CRYPTO_INTERFACE_H
