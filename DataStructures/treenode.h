#ifndef DATASTRUCTURES_TREENODE_H
#define DATASTRUCTURES_TREENODE_H

#include "infiniterandom.h"
#include <iostream>

namespace DataStructures {

  template <typename T>
  class TreeNode
  {
  public:
    typedef TreeNode<T>* NodePointer;

    typedef char direction;

  public:
    TreeNode(const TreeNode& other);

    TreeNode(const T& element);

    std::pair< NodePointer, index_type > remove_all(const T& element);

    std::pair< NodePointer, bool > remove(const T& element);

    inline T& get_element() { return m_element; }

    inline const T& get_element() const { return m_element; }

    inline index_type size() const { return m_size; }

    inline direction element_direction(const T& element) const { return element < m_element ? TREE_LEFT : TREE_RIGHT; }

    inline index_type size(direction dir) const { return m_children[dir] == NULL ? 0 : m_children[dir]->size(); }

    inline bool childless() const { return m_children[TREE_LEFT] == NULL && m_children[TREE_RIGHT] == NULL; }

    inline virtual ~TreeNode() {}

  protected:
    inline virtual direction remove_direction() const { return size(TREE_LEFT) < size(TREE_RIGHT) ? TREE_LEFT : TREE_RIGHT; }

    inline NodePointer rotate(direction dir);

  public:
    inline index_type calculated_size() const { return size(TREE_LEFT) + 1 + size(TREE_RIGHT); }

    T m_element;

    index_type m_size;

    ArrayList<NodePointer> m_children;

  };

  template <typename T>
  TreeNode<T>::TreeNode(const TreeNode<T> &other):
    m_element (other.m_element),
    m_size (other.m_size),
    m_children (2, NULL)
  {
    for (direction dir = TREE_LEFT; dir <= TREE_RIGHT; ++dir) {
      if (other.m_children[dir] != NULL) {
        m_children[dir] = new TreeNode<T>(*other.m_children[dir]);
      }
    }
  }

  template <typename T>
  TreeNode<T>::TreeNode(const T& element):
    m_element (element),
    m_size (1),
    m_children (2, NULL)
  {
  }

  template <typename T>
  std::pair<typename TreeNode<T>::NodePointer, index_type> TreeNode<T>::remove_all(const T& element)
  {
    typedef std::pair< NodePointer, index_type > Result;
    if (m_element == element) {
      Result left_res = m_children[TREE_LEFT] == NULL ? Result(NULL, 0) : m_children[TREE_LEFT]->remove_all(element);
      Result right_res = m_children[TREE_RIGHT] == NULL ? Result(NULL, 0) : m_children[TREE_RIGHT]->remove_all(element);
      m_children[TREE_LEFT] = left_res.first;
      m_children[TREE_RIGHT] = right_res.first;
      index_type left_n = left_res.second;
      index_type right_n = right_res.second;
      m_size -= left_n + right_n;
      Result result = remove(element);
      assert(result.second);
      return std::make_pair(result.first, 1 + left_n + right_n);
    } else {
      index_type dir = element_direction(element);
      if (m_children[dir] == NULL) {
        return std::make_pair(this, 0);
      } else {
        Result result = m_children[dir]->remove_all(element);
        m_children[dir] = result.first;
        m_size -= result.second;
        return std::make_pair(this, result.second);
      }
    }
  }

  template <typename T>
  std::pair<typename TreeNode<T>::NodePointer, bool> TreeNode<T>::remove(const T& element)
  {
    if (m_element == element) {
      NodePointer first_parent = NULL;
      if (m_size > 1) {
        direction old_dir = remove_direction();
        first_parent = rotate(old_dir);
        --(first_parent->m_size);
        NodePointer old_parent = first_parent;
        while (m_size > 1) {
          direction new_dir = remove_direction();
          NodePointer new_parent = rotate(new_dir);
          --(new_parent->m_size);
          old_parent->m_children[1 - old_dir] = new_parent;
          old_parent = new_parent;
          old_dir = new_dir;
        }
        old_parent->m_children[1 - old_dir] = NULL;
      }
      delete this;
      return std::make_pair(first_parent, true);
    } else {
      direction dir = element_direction(element);
      if (m_children[dir] == NULL) {
        return std::make_pair(this, false);
      } else {
        std::pair< NodePointer, bool > result = m_children[dir]->remove(element);
        bool removed = result.second;
        m_children[dir] = result.first;
        m_size -= removed;
        return std::make_pair(this, removed);
      }
    }
  }

}

#endif // DATASTRUCTURES_TREENODE_H
