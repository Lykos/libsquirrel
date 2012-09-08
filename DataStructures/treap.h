#ifndef DATASTRUCTURES_TREAP_H
#define DATASTRUCTURES_TREAP_H

#include "basetree.h"
#include "treapnode.h"
#include <ostream>

namespace DataStructures {

  template <typename T>
  class Treap;

  template <typename T>
  inline std::ostream& operator<<(std::ostream& out, const Treap<T>& it);

  template <typename T>
  class Treap : public BaseTree<T, TreapNode<T> >
  {
    friend std::ostream& operator<< <> (std::ostream& out, const Treap<T>& it);

  public:
    inline Treap();

    inline Treap(const Treap<T>& other);

    template <typename Iterator>
    inline Treap(const Iterator& begin, const Iterator& end);

    inline void insert(const T &element);

    inline bool remove(const T &element);

  protected:
    typedef typename BaseTree<T, TreapNode<T> >::direction direction;

  };

}

#include "treap.hpp"

#endif // DATASTRUCTURES_TREAP_H
