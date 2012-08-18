#ifndef DATASTRUCTURES_TREAP_H
#define DATASTRUCTURES_TREAP_H

#include <sstream>
#include <ostream>
#include "basetypes.h"
#include "DataStructures_global.h"
#include "basetree.h"
#include "treapnode.h"

namespace DataStructures {

  template <typename T>
  std::ostream& operator<<(std::ostream& out, const Treap<T>& it);

  template <typename T>
  class DATASTRUCTURESSHARED_EXPORT Treap : public BaseTree<T, TreapNode<T> >
  {
    friend std::ostream& operator<< <> (std::ostream& out, const Treap<T>& it);

  public:
    Treap();

    Treap(const Treap<T>& other);

    template <typename Begin, typename End>
    Treap(Begin begin, End end);

  };

  template <typename T>
  std::ostream& operator<<(std::ostream& out, const Treap<T>& treap)
  {
    out << "Treap[";
    if (treap.m_root != NULL) {
      out << *(treap.m_root);
    }
    out << "]";
    return out;
  }

  template <typename T>
  Treap<T>::Treap():
    BaseTree<T, TreapNode<T> >()
  {
  }

  template <typename T>
  Treap<T>::Treap(const Treap<T>& other):
    BaseTree<T, TreapNode<T> >(other)
  {
  }

  template <typename T>
  template <typename Begin, typename End>
  Treap<T>::Treap(Begin begin, End end):
    BaseTree<T, TreapNode<T> > (begin, end)
  {
  }

}

#endif // DATASTRUCTURES_TREAP_H
