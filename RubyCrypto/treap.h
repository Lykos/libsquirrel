#ifndef TREAP_H
#define TREAP_H

#ifdef __cplusplus
#include <rice/Data_Type.hpp>

class Treap
{};

extern Rice::Data_Type<Treap> rb_cTreap;

extern "C" {
#endif

void Init_Treap();

#ifdef __cplusplus
}
#endif

#endif // TREAP_H
