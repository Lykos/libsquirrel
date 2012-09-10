#ifndef DATASTRUCTURES_TREAP_H
#define DATASTRUCTURES_TREAP_H

#include "basetree.h"
#include "treapnode.h"
#include "less.h"
#include <ostream>
#include <initializer_list>

namespace DataStructures {

  template <typename T, typename Compare>
  class Treap;

  template <typename T, typename Compare>
  inline std::ostream& operator<<(std::ostream& out, const Treap<T, Compare>& it);

  template <typename T, typename Compare = Less<T> >
  class Treap : public BaseTree<T, TreapNode<T>, Compare>
  {
    friend std::ostream& operator<< <> (std::ostream& out, const Treap<T>& it);

  public:
    inline explicit Treap(const Compare& compare = Compare());

    inline Treap(std::initializer_list<T> list);

    template <typename InputIterator>
    inline Treap(InputIterator begin, InputIterator end, const Compare& compare = Compare());

    inline void insert(const T &element);

    inline bool remove(const T &element);

  protected:
    typedef typename BaseTree<T, TreapNode<T>, Compare>::direction direction;

  };

}

#include "treap.hpp"

#endif // DATASTRUCTURES_TREAP_H
