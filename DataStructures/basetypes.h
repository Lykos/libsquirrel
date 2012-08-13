#ifndef BASETYPES_H
#define BASETYPES_H

#include "DataStructures_global.h"

namespace DataStructures {

  typedef unsigned long long int index_type;
  typedef long long int difference_type;

  template <typename T>
  class BaseList;

  template <typename T, typename List>
  class ListIterator;

  template <typename T, typename List>
  class ListConstIterator;

  template <typename T>
  class DATASTRUCTURESSHARED_EXPORT ArrayList;

  template <typename T>
  class TreapIterator;

  template <typename T>
  class TreapConstIterator;

  template <typename T>
  class TreapNode;

  template <typename T>
  class DATASTRUCTURESSHARED_EXPORT Treap;

}

#endif // BASETYPES_H
