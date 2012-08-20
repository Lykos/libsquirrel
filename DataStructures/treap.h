#ifndef DATASTRUCTURES_TREAP_H
#define DATASTRUCTURES_TREAP_H

#include <ostream>
#include "basetypes.h"
#include "DataStructures_global.h"
#include "basetree.h"
#include "treapnode.h"

namespace DataStructures {

  template <typename T>
  inline std::ostream& operator<<(std::ostream& out, const Treap<T>& it);

  template <typename T>
  class DATASTRUCTURESSHARED_EXPORT Treap : public BaseTree<T, TreapNode<T> >
  {
    friend std::ostream& operator<< <> (std::ostream& out, const Treap<T>& it);

  public:
    inline Treap();

    inline Treap(const Treap<T>& other);

    template <typename Iterator>
    inline Treap(const Iterator& begin, const Iterator& end);

    inline void insert(const T &element);

  protected:
    typedef typename BaseTree<T, TreapNode<T> >::way_point_t way_point_t;

    typedef typename BaseTree<T, TreapNode<T> >::parent_stack_t parent_stack_t;

    typedef typename BaseTree<T, TreapNode<T> >::NodePointer NodePointer;

    typedef typename BaseTree<T, TreapNode<T> >::direction direction;

  };

  template <typename T>
  inline std::ostream& operator<<(std::ostream& out, const Treap<T>& treap)
  {
    out << "Treap[";
    for (typename Treap<T>::const_iterator it = treap.begin(); it < treap.end(); ++it) {
      out << (*it).get_element();
      if (it + 1 < treap.end()) {
        out << ", ";
      }
    }
    out << "]";
    return out;
  }

  template <typename T>
  inline Treap<T>::Treap():
    BaseTree<T, TreapNode<T> >()
  {
  }

  template <typename T>
  inline Treap<T>::Treap(const Treap<T>& other):
    BaseTree<T, TreapNode<T> >(other)
  {
  }

  template <typename T>
  template <typename Iterator>
  inline Treap<T>::Treap(const Iterator& begin, const Iterator& end):
    BaseTree<T, TreapNode<T> > (begin, end)
  {
  }

  template <typename T>
  inline void Treap<T>::insert(const T &element)
  {
    if (BaseTree<T, TreapNode<T> >::m_root == NULL) {
      BaseTree<T, TreapNode<T> >::m_root = new TreapNode<T>(element);
      return;
    }
    parent_stack_t parent_stack;
    BaseTree<T, TreapNode<T> >::insert_with_stack(BaseTree<T, TreapNode<T> >::m_root, element, parent_stack);
    way_point_t last_point = parent_stack.pop();
    NodePointer current = last_point.node;
    direction dir = last_point.dir;
    while (current->child(dir)->m_randomness < current->m_randomness) {
      if (parent_stack.is_empty()) {
        BaseTree<T, TreapNode<T> >::rotate_root(dir);
        return;
      } else {
        way_point_t parent = parent_stack.pop();
        BaseTree<T, TreapNode<T> >::rotate(parent.node, parent.dir, dir);
        current = parent.node;
        dir = parent.dir;
      }
    }
  }


}

#endif // DATASTRUCTURES_TREAP_H
