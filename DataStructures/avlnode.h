#ifndef DATASTRUCTURES_AVLNODE_H
#define DATASTRUCTURES_AVLNODE_H

#include "basetypes.h"
#include "treenode.h"
#include "stdexcept"

#define assert_balance(node_pointer) { assert(node_pointer->m_balance == -1 || node_pointer->m_balance == 0 || node_pointer->m_balance == 1); }

namespace DataStructures {

  template <typename T>
  class AVLNode : public TreeNode<T>
  {
  public:
    typedef char balance_t;

  private:
    typedef typename TreeNode<T>::NodePointer NodePointer;

    typedef AVLNode<T>* AVLNodePointer;

    typedef const AVLNode<T>* ConstAVLNodePointer;

  public:
    typedef typename TreeNode<T>::direction direction;

    inline AVLNode(const AVLNode& other);

    inline AVLNode(const T& element);

    balance_t m_balance;

    inline ConstAVLNodePointer child(direction dir) const { return static_cast<const AVLNodePointer>(TreeNode<T>::m_children[dir]); }

    inline AVLNodePointer child(direction dir) { return static_cast<AVLNodePointer>(TreeNode<T>::m_children[dir]); }

  protected:
    inline direction remove_direction() const { throw std::logic_error("Not implemented."); }

  private:
    inline direction min_balance_direction() const;

  };


  template <typename T>
  AVLNode<T>::AVLNode(const AVLNode<T> &other):
    TreeNode<T>(other),
    m_balance (other.m_balance)
  {
  }

  template <typename T>
  AVLNode<T>::AVLNode(const T& element):
    TreeNode<T>(element),
    m_balance (0)
  {
  }

  template <typename T>
  inline typename AVLNode<T>::direction AVLNode<T>::min_balance_direction() const
  {
    assert(TreeNode<T>::m_size > 1);
    assert(TreeNode<T>::m_children[TREE_LEFT] != NULL || TreeNode<T>::m_children[TREE_RIGHT] != NULL);
    if (TreeNode<T>::m_children[TREE_LEFT] == NULL) {
      return TREE_RIGHT;
    } else if (TreeNode<T>::m_children[TREE_RIGHT] == NULL) {
      return TREE_LEFT;
    } else {
      return child(TREE_LEFT)->m_balance < child(TREE_RIGHT)->m_balance ? TREE_LEFT : TREE_RIGHT;
    }
  }
  
} // namespace DataStructures

#endif // DATASTRUCTURES_AVLNODE_H
