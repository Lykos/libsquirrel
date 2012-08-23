#include "longint_interface.h"
#include "longint.h"

using namespace DataStructures;

extern "C" {

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
  const LongInt& i = *static_cast<LongInt*>(long_int);
  packed_longint_t packed_longint = i.pack();
  packed_bignum_t bignum;
  bignum.sign = packed_longint.sign;
  bignum.parts = packed_longint.parts;
  bignum.num_parts = packed_longint.num_parts;
  return bignum;
}

}
