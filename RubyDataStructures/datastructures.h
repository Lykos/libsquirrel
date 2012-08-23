#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H

#include <ruby.h>
#include "longint_interface.h"

VALUE method_multiply(VALUE self, VALUE a, VALUE b);

inline unsigned long int bignum_size(VALUE bignum);

inline packed_bignum_t pack_bignum(VALUE bignum);

inline VALUE unpack_bignum(packed_bignum_t packed_bignum);

void Init_datastructures(void);

#endif // DATASTRUCTURES_H
