#include "RubyCrypto.h"

static VALUE Crypto;

static VALUE ElgamalEncrypter;

void Init_RubyCrypto(void)
{
  Crypto = rb_define_module("Crypto");
  ElgamalEncrypter = rb_define_class_under(Crypto, "ElgamalEncrypter", rb_cObject);
}
