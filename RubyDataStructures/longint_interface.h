#ifndef LONGINT_H
#define LONGINT_H

#ifdef __cplusplus
extern "C" {
#endif

typedef void* long_int_t;

typedef struct {
  unsigned int* parts;
  unsigned long int num_parts;
  char sign;
} packed_bignum_t;

void mult_eq(long_int_t a, long_int_t b);

long_int_t big_to_long(packed_bignum_t big_num);

packed_bignum_t long_to_big(long_int_t long_int);

#ifdef __cplusplus
}
#endif

#endif // LONGINT_H
