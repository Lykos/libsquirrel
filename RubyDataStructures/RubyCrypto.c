#include "RubyCrypto.h"
#include "crypto_interface.h"

static VALUE Crypto;

static VALUE ElgamalEncrypter;

static VALUE Bla;

void mark_elgamal_encrypter(Crypto_cbc_elgamal_encrypter_t self)
{
}

void free_elgamal_encrypter(Crypto_cbc_elgamal_encrypter_t self)
{
  Crypto_deinit_cbc_elgamal_decrypter(self);
}

VALUE alloc_elgamal_encrypter(VALUE klass)
{
  return Data_Wrap_Struct(klass, mark_elgamal_encrypter, free_elgamal_encrypter, malloc(Crypto_cbc_elgamal_encrypter_length));
}

VALUE init_elgamal_encrypter(VALUE self, VALUE key, VALUE state)
{
  if (!TYPE(key) == T_STRING) {
    rb_raise(rb_eTypeError, "The first argument key for ElgamalEncrypter has to be a string.");
  }
  if (!TYPE(state) == T_STRING) {
    rb_raise(rb_eTypeError, "The first argument key for ElgamalEncrypter has to be a string.");
  }
  VALUE ret_key = StringValue(key);
  const char* raw_public_key = RSTRING_PTR(ret_key);
  ulong key_length = RSTRING_LEN(ret_key);
  VALUE ret_state = StringValue(state);
  const char* initial_state = RSTRING_PTR(ret_state);
  ulong state_length = RSTRING_LEN(ret_state);
  Crypto_cbc_elgamal_encrypter_t encrypter;
  Data_Get_Struct(self, Crypto_cbc_elgamal_encrypter_t, encrypter);
  error_code_t err = Crypto_init_cbc_elgamal_encrypter(encrypter, raw_public_key, key_length, initial_state, state_length);
  if (err < 0) {
    rb_raise(rb_eArgError, "The ElgamalEncrypter could not be constructed. Probably the initial_state is too short.");
  }
  return self;
}

void Init_RubyCrypto(void)
{
  Bla = rb_define_class("Bla", rb_cObject);
  Crypto = rb_define_module("Crypto");
  ElgamalEncrypter = rb_define_class_under(Crypto, "ElgamalEncrypter", rb_cObject);
  rb_define_alloc_func(ElgamalEncrypter, alloc_elgamal_encrypter);
  rb_define_method(ElgamalEncrypter, "initialize", init_elgamal_encrypter, 2);
}

