#include "RubyCrypto.h"
#include "crypto_interface.h"
#include "Crypto/conditiontype.h"

#define READ_STRING(str, n, k, len) \
  if (!TYPE(str) == T_STRING) { \
    rb_raise(rb_eTypeError, "Argument " #n " " #str " for " #k " has to be a String."); \
  } \
  number_size_t len; \
{ \
  VALUE ret_str = StringValue(str); \
  const char* hex_str = RSTRING_PTR(ret_str); \
  len = RSTRING_LEN(ret_str); \
  hex = from_hex(hex_str, len); \
  len /= 2; \
  if (hex == NULL) { \
  rb_raise(rb_eArgError, "The " #n " argument " #str " for " #k " has to be a String with hexadecimal content."); \
  } \
}

#define READ_HEX(str, n, k, hex, len) \
  if (!TYPE(str) == T_STRING) { \
    rb_raise(rb_eTypeError, "Argument " #n " " #str " for " #k " has to be a String."); \
  } \
  number_size_t len; \
  byte_t* hex; \
  { \
    VALUE ret_str = StringValue(str); \
    const char* hex_str = RSTRING_PTR(ret_str); \
    len = RSTRING_LEN(ret_str); \
    hex = from_hex(hex_str, len); \
    len /= 2; \
    if (hex == NULL) { \
      rb_raise(rb_eArgError, "The " #n " argument " #str " for " #k " has to be a String with hexadecimal content."); \
    } \
  }

void check_error(error_code_t err)
{
  if (err < 0) {
    char msg[100];
    sprintf(msg, "Something in the extension went wrong. Internal error code is %d.", err);
    rb_raise(rb_eException, msg);
  }
}

char* to_hex(const byte_t* binary_string, number_size_t length) {
  static const char hex_chars[] = "0123456789ABCDEF";
  char* hex = (char*) malloc(length * 2 * sizeof(char));
  uint i;
  for (i = 0; i < length; ++i) {
    byte_t byte = binary_string[i];
    hex[2 * i] = hex_chars[(byte >> 4) & 0xF];
    hex[2 * i + 1] = hex_chars[byte & 0xF];
  }
  return hex;
}

byte_t* from_hex(const char* hex_string, number_size_t length) {
  char *binary = (char*) malloc(length / 2 * sizeof(char));
  uint i;
  for (i = 0; i < length; ++i) {
    char c = hex_string[i];
    byte_t out;
    if (c >= '0' && c <= '9') {
      out = c - '0';
    } else if (c >= 'A' && c <= 'F') {
      out = 10 + c - 'A';
    } else if (c >= 'a' && c <= 'f') {
      out = 10 + c - 'a';
    } else {
      free(binary);
      return NULL;
    }
    if (i % 2 == 0) {
      binary[i / 2] = out << 4;
    } else {
      binary[i / 2] |= out;
    }
  }
  return binary;
}

static VALUE Crypto;

static VALUE ElgamalEncrypter;

void nop(void* self) {}

VALUE ElgamalEncrypter_alloc(VALUE klass)
{
  return Data_Wrap_Struct(klass, nop, Crypto_deinit_cbc_elgamal_decrypter, malloc(Crypto_cbc_elgamal_encrypter_length));
}

VALUE ElgamalEncrypter_init(VALUE self, VALUE key, VALUE state)
{
  READ_HEX(key, 1, ElgamalEncrypter, raw_public_key, key_length);
  READ_HEX(state, 2, ElgamalEncrypter, initial_state, state_length);
  Crypto_cbc_elgamal_encrypter_t encrypter;
  Data_Get_Struct(self, Crypto_cbc_elgamal_encrypter_t, encrypter);
  error_code_t err = Crypto_init_cbc_elgamal_encrypter(encrypter, raw_public_key, key_length, initial_state, state_length);
  free(raw_public_key);
  free(initial_state);
  ConditionType prec_err = -(err - PRECONDITION_BASE);
  switch (prec_err) {
  case PublicKeyModulusLengthLength:
    rb_raise(rb_eArgError, "Argument 1 is too short to store the length of the modulus of the key.");
    break;
  case PublicKeyModulusLength:
    rb_raise(rb_eArgError, "Argument 1 is too short to store the modulus of the key or the modulus length is wrong.");
    break;
  case PublicKeyGeneratorLengthLength:
    rb_raise(rb_eArgError, "Argument 1 is too short to store the length of the generator of the key.");
    break;
  case PublicKeyGeneratorLength:
    rb_raise(rb_eArgError, "Argument 1 is too short to store the generator of the key or the generator length is wrong.");
    break;
  case PublicKeyGenPowerLengthLength:
    rb_raise(rb_eArgError, "Argument 1 is too short to store the length of the generator power of the key.");
    break;
  case PublicKeyGenPowerLength:
    rb_raise(rb_eArgError, "Argument 1 is too short to store the generator power of the key or the generator power length is wrong.");
    break;
  case StateLength:
    rb_raise(rb_eArgError, "Argument 2 is too short to store a valid initial state.");
    break;
  default: nop(NULL);
  }
  check_error(err);
  return self;
}

VALUE ElgamalEncrypter_encrypt(VALUE self, VALUE key, VALUE state)
{

  Crypto_cbc_elgamal_encrypter_t encrypter;
}

void Init_RubyCrypto(void)
{
  Crypto = rb_define_module("Crypto");
  ElgamalEncrypter = rb_define_class_under(Crypto, "ElgamalEncrypter", rb_cObject);
  rb_define_alloc_func(ElgamalEncrypter, alloc_elgamal_encrypter);
  rb_define_method(ElgamalEncrypter, "initialize", init_elgamal_encrypter, 2);
}

