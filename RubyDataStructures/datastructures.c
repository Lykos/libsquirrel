#include "datastructures.h"
#include "limits.h"

#define CTC(X) ({ extern int __attribute__((error("assertion failure: '" #X "' not true"))) compile_time_check(); ((X)?0:compile_time_check()),0; })

static VALUE DataStructures;

void Init_datastructures(void)
{
  DataStructures = rb_define_module("DataStructures");
  rb_define_method(DataStructures, "multiply", method_multiply, 2);
}

inline packed_bignum_t pack_bignum(VALUE bignum)
{
  CTC(sizeof(BDIGIT) == sizeof(unsigned int));
  CTC(sizeof(unsigned long int) == 2 * sizeof(unsigned int));
  rb_to_int(bignum);
  packed_bignum_t result;
  if (FIXNUM_P(bignum)) {
    long int tmp = FIX2LONG(bignum);
    result.sign = tmp >= 0;
    unsigned long int tmp2 = (result.sign ? tmp : -tmp);
    result.num_parts = 2;
    result.parts = malloc(2 * sizeof(unsigned int));
    result.parts[0] = (unsigned int)(tmp2);
    result.parts[1] = (unsigned int)(tmp2 >> (sizeof(unsigned int) * CHAR_BIT));
  } else {
    result.num_parts = RBIGNUM_LEN(bignum);
    result.sign = RBIGNUM_POSITIVE_P(bignum);
    result.parts = (unsigned int*)(RBIGNUM_DIGITS(bignum));
  }
  return result;
}

inline VALUE unpack_bignum(packed_bignum_t packed_bignum)
{
  if (packed_bignum.num_parts == 1) {
    unsigned long int tmp2 = packed_bignum.parts[0];
    long int tmp = (packed_bignum.sign ? tmp2 : -tmp2);
    return LONG2FIX(tmp);
  }
  VALUE bignum = rb_big_new(packed_bignum.num_parts, packed_bignum.sign);
  return rb_big_norm(bignum);
}

VALUE method_multiply(VALUE self, VALUE a, VALUE b)
{
  long_int_t c = big_to_long(pack_bignum(a));
  long_int_t d = big_to_long(pack_bignum(b));
  mult_eq(c, d);
  return unpack_bignum(long_to_big(c));
}
