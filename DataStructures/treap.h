#ifndef DATASTRUCTURES_TREAP_H
#define DATASTRUCTURES_TREAP_H

#include <ostream>
#include "basetree.h"
#include "treapnode.h"

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
    TreapNode<T>* current = BaseTree<T, TreapNode<T> >::internal_insert(element);
    TreapNode<T>* parent = current->parent;
    direction parent_direction = current->parent_direction;
    while (parent != NULL && current->randomness < parent->randomness) {
      BaseTree<T, TreapNode<T> >::rotate(parent, parent_direction);
      parent = current->parent;
      parent_direction = current->parent_direction;
    }
  }

  template <typename T>
  inline bool Treap<T>::remove(const T &element)
  {
    TreapNode<T>* current = BaseTree<T, TreapNode<T> >::root();
    while (current != NULL) {
      if (current->element == element) {
        while (current->is_inner()) {
          direction dir = current->min_size_direction();
          BaseTree<T, TreapNode<T> >::rotate(current, dir);
        }
        BaseTree<T, TreapNode<T> >::non_inner_remove(current);
        return true;
      }
      direction dir = current->element_direction(element);
      current = current->children[dir];
    }
    return false;
  }

}

#endif // DATASTRUCTURES_TREAP_H
