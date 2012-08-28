#ifndef CRYPTO_INTERFACE_H
#define CRYPTO_INTERFACE_H

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned char byte_t;

typedef unsigned long int size_t;

typedef void* Crypto_elgamal_public_key_t;

typedef void* Crypto_elgamal_private_key_t;

typedef byte_t* Crypto_aes_key_t;

typedef struct {
  Crypto_aes_key_t cipher_key;
  Crypto_aes_key_t mac_key;
} Crypto_aes_key_pair_t;

typedef void* Crypto_cbc_elgamal_encrypter_t;

typedef void* Crypto_cbc_elgamal_decrypter_t;

typedef void* Crypto_cbc_aes_encrypter_t;

typedef void* Crypto_cbc_aes_decrypter_t;

typedef void* Crypto_elgamal_signer_t;

typedef void* Crypto_elgamal_verifier_t;

typedef void* Crypto_cbc_aes_signer_t;

typedef void* Crypto_cbc_aes_verifier_t;

Crypto_elgamal_public_key_t Crypto_read_elgamal_public_key(const byte_t* key_string);

Crypto_elgamal_public_key_t Crypto_read_elgamal_private_key(const byte_t* key_string);

Crypto_aes_key_pair_t Crypto_generate_aes_keys(const byte_t* secret);

Crypto_cbc_elgamal_encrypter_t Crypto_init_cbc_elgamal_encrypter(Crypto_elgamal_public_key_t private_key);

Crypto_cbc_elgamal_decrypter_t Crypto_init_cbc_elgamal_decrypter(Crypto_elgamal_private_key_t private_key);

Crypto_cbc_aes_encrypter_t Crypto_init_cbc_aes_encrypter(Crypto_aes_key_t cipher_key);

Crypto_cbc_aes_decrypter_t Crypto_init_cbc_aes_decrypter(Crypto_aes_key_t cipher_key);

Crypto_elgamal_signer_t Crypto_init_elgamal_signer(Crypto_elgamal_private_key_t private_key);

Crypto_elgamal_verifier_t Crypto_init_elgamal_verifier(Crypto_elgamal_public_key_t public_key);

Crypto_cbc_aes_signer_t Crypto_init_cbc_aes_signer(Crypto_aes_key_t mac_key);

Crypto_cbc_aes_verifier_t Crypto_init_cbc_aes_verifier(Crypto_aes_key_t mac_key);

Crypto_cbc_elgamal_encrypter_t Crypto_deinit_cbc_elgamal_encrypter(Crypto_elgamal_public_key_t private_key);

Crypto_cbc_elgamal_decrypter_t Crypto_deinit_cbc_elgamal_decrypter(Crypto_elgamal_private_key_t private_key);

Crypto_cbc_aes_encrypter_t Crypto_deinit_cbc_aes_encrypter(Crypto_aes_key_t cipher_key);

Crypto_cbc_aes_decrypter_t Crypto_deinit_cbc_aes_decrypter(Crypto_aes_key_t cipher_key);

Crypto_elgamal_signer_t Crypto_deinit_elgamal_signer(Crypto_elgamal_private_key_t private_key);

Crypto_elgamal_verifier_t Crypto_deinit_elgamal_verifier(Crypto_elgamal_public_key_t public_key);

Crypto_cbc_aes_signer_t Crypto_deinit_cbc_aes_signer(Crypto_aes_key_t mac_key);

Crypto_cbc_aes_verifier_t Crypto_deinit_cbc_aes_verifier(Crypto_aes_key_t mac_key);

size_t Crypto_cbc_elgamal_cipher_length(size_t plain_length);

size_t Crypto_cbc_elgamal_max_plain_length(size_t cipher_length);

size_t Crypto_cbc_aes_cipher_length(size_t plain_length);

size_t Crypto_cbc_aes_max_plain_length(size_t cipher_length);

size_t Crypto_elgamal_signature_length(Crypto_elgamal_signer_t signer);

size_t Crypto_cbc_aes_signature_length(Crypto_cbc_aes_signer_t signer);

size_t Crypto_elgamal_signature_length(Crypto_elgamal_verifier_t signer);

size_t Crypto_cbc_aes_signature_length(Crypto_cbc_aes_verifier_t signer);

size_t Crypto_cbc_elgamal_encrypt(Crypto_cbc_elgamal_encrypter_t encrypter, const byte_t* plain, size_t length, byte_t* cipher);

size_t Crypto_cbc_elgamal_decrypt(Crypto_cbc_elgamal_decrypter_t decrypter, const byte_t* cipher, size_t length, byte_t* plain);

size_t Crypto_cbc_aes_encrypt(Crypto_cbc_aes_encrypter_t encrypter, const byte_t* plain, size_t length, byte_t* cipher);

size_t Crypto_cbc_aes_decrypt(Crypto_cbc_aes_decrypter_t decrypter, const byte_t* cipher, size_t length, byte_t* plain);

size_t Crypto_elgamal_sign(Crypto_cbc_elgamal_encrypter_t encrypter, byte_t* message, size_t length);

size_t Crypto_elgamal_verify(Crypto_cbc_elgamal_decrypter_t decrypter, byte_t* message, size_t length);

byte_t Crypto_cbc_aes_sign(Crypto_cbc_aes_encrypter_t encrypter, const byte_t* message, size_t length);

byte_t Crypto_cbc_aes_verify(Crypto_cbc_aes_decrypter_t decrypter,  const byte_t* message, size_t length);

#ifdef __cplusplus
}
#endif

#endif // CRYPTO_INTERFACE_H
