#ifndef DATASTRUCTURES_TREAP_HPP
#define DATASTRUCTURES_TREAP_HPP

#include "treap.h"
#include "basetree.h"
#include "treapnode.h"
#include <ostream>

namespace DataStructures {

  template <typename T, typename Compare>
  inline std::ostream& operator<<(std::ostream& out, const Treap<T, Compare>& treap)
  {
    out << "Treap[";
    for (typename Treap<T, Compare>::const_iterator it = treap.begin(); it < treap.end(); ++it) {
      out << *it;
      if (it + 1 < treap.end()) {
        out << ", ";
      }
    }
    out << "]";
    return out;
  }

  template <typename T, typename Compare>
  inline Treap<T, Compare>::Treap(std::initializer_list<T> list):
    Treap<T, Compare>(list.begin(), list.end())
  {}

  template <typename T, typename Compare>
  inline Treap<T, Compare>::Treap(const Compare& compare):
    BaseTree<T, TreapNode<T>, Compare>(compare)
  {}

  template <typename T, typename Compare>
  template <typename InputIterator>
  inline Treap<T, Compare>::Treap(InputIterator begin, InputIterator end, const Compare& compare):
    BaseTree<T, TreapNode<T>, Compare> (begin, end, compare)
  {}

  template <typename T, typename Compare>
  inline void Treap<T, Compare>::insert(const T &element)
  {
    TreapNode<T>* current = BaseTree<T, TreapNode<T>, Compare>::internal_insert(element);
    TreapNode<T>* parent = current->parent;
    direction parent_direction = current->parent_direction;
    while (parent != nullptr && current->randomness < parent->randomness) {
      BaseTree<T, TreapNode<T>, Compare>::rotate(parent, parent_direction);
      parent = current->parent;
      parent_direction = current->parent_direction;
    }
  }

  template <typename T, typename Compare>
  inline bool Treap<T, Compare>::remove(const T &element)
  {
    TreapNode<T>* current = BaseTree<T, TreapNode<T>, Compare>::m_root;
    while (current != nullptr) {
      if (current->element == element) {
        while (current->is_inner()) {
          direction dir = current->min_size_direction();
          BaseTree<T, TreapNode<T>, Compare>::rotate(current, dir);
        }
        BaseTree<T, TreapNode<T>, Compare>::non_inner_remove(current);
        return true;
      }
      direction dir = BaseTree<T, TreapNode<T>, Compare>::element_direction(current, element);
      current = current->children[dir];
    }
    return false;
  }

}

#endif // DATASTRUCTURES_TREAP_HPP
