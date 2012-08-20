#ifndef DATASTRUCTURES_AVLTREE_H
#define DATASTRUCTURES_AVLTREE_H

#include "basetypes.h"
#include "avlnode.h"
#include "basetree.h"
#include <ostream>

namespace DataStructures {

  typedef char balance_t;

  static const balance_t BALANCE_SIGN[] = {-1, 1};

  template <typename T>
  inline std::ostream& operator<<(std::ostream& out, const AVLTree<T>& it);

  template <typename T>
  class DATASTRUCTURESSHARED_EXPORT AVLTree : public BaseTree<T, AVLNode<T> >
  {
    friend std::ostream& operator<< <> (std::ostream& out, const AVLTree<T>& it);

  public:
    inline AVLTree();

    inline AVLTree(const AVLTree<T>& other);

    inline void insert(const T &element);

    template <typename Iterator>
    inline AVLTree(const Iterator& begin, const Iterator& end);

  private:
    typedef typename AVLNode<T>::balance_t balance_t;

    typedef typename BaseTree<T, AVLNode<T> >::way_point_t way_point_t;

    typedef typename BaseTree<T, AVLNode<T> >::NodePointer NodePointer;

    typedef typename BaseTree<T, AVLNode<T> >::direction direction;

    typedef typename BaseTree<T, AVLNode<T> >::parent_stack_t parent_stack_t;

  };

  template <typename T>
  inline std::ostream& operator<<(std::ostream& out, const AVLTree<T>& tree)
  {
    out << "AVLTree[";
    for (typename AVLTree<T>::const_iterator it = tree.begin(); it < tree.end(); ++it) {
      out << (*it).get_element();
      if (it + 1 < tree.end()) {
        out << ", ";
      }
    }
    out << "]";
    return out;
  }

  template <typename T>
  inline AVLTree<T>::AVLTree():
    BaseTree<T, AVLNode<T> >()
  {
  }

  template <typename T>
  inline AVLTree<T>::AVLTree(const AVLTree<T>& other):
    BaseTree<T, AVLNode<T> >(other)
  {
  }

  template <typename T>
  template <typename Iterator>
  inline AVLTree<T>::AVLTree(const Iterator& begin, const Iterator& end):
    BaseTree<T, AVLNode<T> > (begin, end)
  {
  }

  template <typename T>
  inline void AVLTree<T>::insert(const T& element)
  {
    if (BaseTree<T, AVLNode<T> >::m_root == NULL) {
      BaseTree<T, AVLNode<T> >::m_root = new AVLNode<T>(element);
      return;
    }
    parent_stack_t parent_stack;
    BaseTree<T, AVLNode<T> >::insert_with_stack(BaseTree<T, AVLNode<T> >::m_root, element, parent_stack);
    way_point_t last_point = parent_stack.pop();
    NodePointer child = last_point.node;
    balance_t old_balance = child->m_balance;
    child->m_balance += BALANCE_SIGN[last_point.dir];
    while (!parent_stack.is_empty() && child->m_balance != 0 && child->m_balance != old_balance) {
      way_point_t way_point = parent_stack.pop();
      NodePointer current = way_point.node;
      direction dir = way_point.dir;
      current->m_balance += BALANCE_SIGN[dir];
      if (current->m_balance == 2 * BALANCE_SIGN[dir]) {
        if (child->m_balance == BALANCE_SIGN[dir]) {
          // Normal rotation
          old_balance = child->m_balance;
          child->m_balance = 0;
          current->m_balance = 0;
          if (parent_stack.is_empty()) {
            BaseTree<T, AVLNode<T> >::rotate_root(dir);
          } else {
            way_point_t parent = parent_stack.back();
            BaseTree<T, AVLNode<T> >::rotate(parent.node, parent.dir, dir);
          }
          // Child stays the same because of the rotation
        } else {
          // Zic zac rotation
          // Note that current->child(1 - dir) is guaranteed to exist in the case.
          NodePointer new_child = child->child(1 - dir);
          balance_t lower_balance = new_child->m_balance;
          old_balance = new_child->m_balance;
          new_child->m_balance = 0;
          if (lower_balance == BALANCE_SIGN[dir]) {
            current->m_balance = 0;
            child->m_balance = 1;
          } else if (lower_balance == BALANCE_SIGN[1 - dir]) {
            current->m_balance = -1;
            child->m_balance = 0;
          } else {
            assert(lower_balance == 0);
            current->m_balance = 0;
            child->m_balance = 0;
          }
          BaseTree<T, AVLNode<T> >::rotate(current, dir, 1 - dir);
          if (parent_stack.is_empty()) {
            BaseTree<T, AVLNode<T> >::rotate_root(dir);
          } else {
            way_point_t parent = parent_stack.back();
            BaseTree<T, AVLNode<T> >::rotate(parent.node, parent.dir, dir);
          }
          assert_balance(child);
          child = new_child;
        }
      } else {
        child = current;
      }
      assert_balance(child);
      assert_balance(current);
    }
  }
  
} // namespace DataStructures

#endif // DATASTRUCTURES_AVLTREE_H
