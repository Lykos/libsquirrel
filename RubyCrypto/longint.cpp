#include "longint.h"
#include "DataStructures/longint.h"

extern "C" void Init_LongInt() {

}

/* TODO Port this to rice
#define CTC(X) ({ extern int __attribute__((error("assertion failure: '" #X "' not true"))) compile_time_check(); ((X)?0:compile_time_check()),0; })
#define RBIGNUM_DIGITS_SET(b, v, l) \
  if (RBASIC(b)->flags & RBIGNUM_EMBED_FLAG) { \
  memcpy(RBIGNUM(b)->as.ary + 0, v, sizeof(BDIGIT) * l); \
  memset(RBIGNUM(b)->as.ary + l, 0, sizeof(BDIGIT) * (RBIGNUM_EMBED_LEN_MAX - l));  \
  } else { \
  RBIGNUM(b)->as.heap.digits = v; \
  }

using namespace DataStructures;

void mult_eq(long_int_t a, long_int_t b)
{
  LongInt& c = *static_cast<LongInt*>(a);
  LongInt& d = *static_cast<LongInt*>(b);
  c *= d;
}

typedef LongInt::packed_longint_t packed_longint_t;

long_int_t big_to_long(packed_bignum_t big_num)
{
  packed_longint_t packed_longint;
  packed_longint.sign = big_num.sign;
  packed_longint.parts = big_num.parts;
  packed_longint.num_parts = big_num.num_parts;
  LongInt* long_int = new LongInt(packed_longint);
  return long_int_t(long_int);
}

packed_bignum_t long_to_big(long_int_t long_int)
{
  const LongInt* i = static_cast<LongInt*>(long_int);
  packed_longint_t packed_longint = i->pack();
  packed_bignum_t bignum;
  bignum.sign = packed_longint.sign;
  bignum.parts = packed_longint.parts;
  bignum.num_parts = packed_longint.num_parts;
  delete i;
  return bignum;
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
  RBIGNUM_DIGITS_SET(bignum, packed_bignum.parts, packed_bignum.num_parts);
  return rb_big_norm(bignum);
}

VALUE method_multiply(VALUE self, VALUE a, VALUE b)
{
  long_int_t c = big_to_long(pack_bignum(a));
  long_int_t d = big_to_long(pack_bignum(b));
  mult_eq(c, d);
  return unpack_bignum(long_to_big(c));
}*/
