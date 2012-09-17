#include "treap.h"
#include "crypto.h"
#include <rice/Constructor.hpp>

using namespace Rice;

Data_Type<Treap> rb_cTreap;

void Init_Treap()
{
  rb_cTreap = define_class_under<Treap>(rb_mCrypto, "Treap")
  .define_constructor(Constructor<Treap>());
}
