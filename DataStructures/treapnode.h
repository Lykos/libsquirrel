#ifndef DATASTRUCTURES_TREAPNODE_H
#define DATASTRUCTURES_TREAPNODE_H

#include "infiniterandom.h"
#include "treenode.h"

namespace DataStructures {

  template <typename T>
  class TreapNode : public TreeNode<T>
  {
  protected:
    typedef TreapNode<T>* TreapNodePointer;

    typedef const TreapNode<T>* ConstTreapNodePointer;

  public:
    typedef typename TreeNode<T>::NodePointer NodePointer;

    typedef typename TreeNode<T>::direction direction;

    inline TreapNode(const TreapNode& other);

    inline TreapNode(const T& element);

    InfiniteRandom m_randomness;

    inline ConstTreapNodePointer child(direction dir) const { return static_cast<const TreapNodePointer>(TreeNode<T>::m_children[dir]); }

    inline TreapNodePointer child(direction dir) { return static_cast<TreapNodePointer>(TreeNode<T>::m_children[dir]); }

  protected:
    inline direction min_rand_direction() const;

    inline direction remove_direction() const { return min_rand_direction(); }

  };

  template <typename T>
  inline TreapNode<T>::TreapNode(const TreapNode<T> &other):
    TreeNode<T>(other),
    m_randomness (other.m_randomness)
  {
  }

  template <typename T>
  TreapNode<T>::TreapNode(const T& element):
    TreeNode<T>(element),
    m_randomness ()
  {
  }

  template <typename T>
  inline typename TreapNode<T>::direction TreapNode<T>::min_rand_direction() const
  {
    assert(TreeNode<T>::m_size > 1);
    assert(TreeNode<T>::m_children[TREE_LEFT] != NULL || TreeNode<T>::m_children[TREE_RIGHT] != NULL);
    if (TreeNode<T>::m_children[TREE_LEFT] == NULL) {
      return TREE_RIGHT;
    } else if (TreeNode<T>::m_children[TREE_RIGHT] == NULL) {
      return TREE_LEFT;
    } else {
      return child(TREE_LEFT)->m_randomness < child(TREE_RIGHT)->m_randomness ? TREE_LEFT : TREE_RIGHT;
    }
  }

}

#endif // DATASTRUCTURES_TREAPNODE_H
