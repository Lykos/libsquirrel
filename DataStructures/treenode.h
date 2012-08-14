#ifndef TREENODE_H
#define TREENODE_H

#include "infiniterandom.h"
#include "treeiterator.h"
#include "treeconstiterator.h"
#include <iostream>

#define TREE_LEFT 0
#define TREE_RIGHT 1
#define assert_size() assert(m_size == left_size() + 1 + right_size())

namespace DataStructures {

  template <typename T>
  std::ostream& operator<<(std::ostream& out, const TreeNode<T>& it);

  template <typename T>
  class TreeNode
  {
    friend std::ostream& operator<< <> (std::ostream& out, const TreeNode<T>& it);
  public:
    typedef TreeConstIterator<T> const_iterator;

    typedef TreeIterator<T> iterator;

  private:
    typedef TreeNode<T>* NodePointer;

    typedef typename iterator::NodeInfo NodeInfo;

    typedef typename const_iterator::ConstNodeInfo ConstNodeInfo;

  public:
    TreeNode(const TreeNode& other);

    TreeNode(const T& element);

    virtual void insert(NodePointer *incoming_pointer_address, const T& element);

    bool search(const T& element) const;

    iterator lower_bound(ArrayList<NodeInfo>& parent_stack, const T& element, index_type left_part);

    iterator upper_bound(ArrayList<NodeInfo>& parent_stack,const T& element, index_type left_part);

    std::pair< iterator, iterator > equal_range(ArrayList<NodeInfo>& parent_stack,const T& element, index_type left_part);

    T& operator[](index_type index);

    const_iterator lower_bound(ArrayList<ConstNodeInfo>& parent_stack,const T& element, index_type left_part) const;

    const_iterator upper_bound(ArrayList<ConstNodeInfo>& parent_stack,const T& element, index_type left_part) const;

    std::pair< const_iterator, const_iterator > equal_range(ArrayList<ConstNodeInfo>& parent_stack, const T& element, index_type left_part) const;

    const T& operator[](index_type index) const;

    index_type remove_all(NodePointer *incoming_pointer_address, const T& element);

    virtual bool remove(NodePointer *incoming_pointer_address, const T& element);

    inline T& get_element() { return m_element; }

    inline const T& get_element() const { return m_element; }

    inline index_type size() const { return m_size; }

    iterator iterator_at(ArrayList<NodeInfo>& parent_stack, index_type index, index_type left_part);

    const_iterator iterator_at(ArrayList<ConstNodeInfo>& parent_stack, index_type index, index_type left_part) const;

    iterator begin();

    iterator end();

    const_iterator begin() const;

    const_iterator end() const;

    virtual ~TreeNode();

  protected:

    typedef index_type direction;

    inline direction element_direction(const T& element) const { return element < m_element ? TREE_LEFT : TREE_RIGHT; }

    inline direction min_rand_direction() const;

    inline void rotate(NodePointer *incoming_pointer_address, direction dir);

    inline index_type left_size() const { return m_children[TREE_LEFT] == NULL ? 0 : m_children[TREE_LEFT]->size(); }

    inline index_type right_size() const { return m_children[TREE_RIGHT] == NULL ? 0 : m_children[TREE_RIGHT]->size(); }

    index_type m_size;

    T m_element;

    ArrayList<NodePointer> m_children;

  };

  template <typename T>
  TreeNode<T>::TreeNode(const TreeNode<T> &other):
    m_size (other.m_size),
    m_element (other.m_element),
    m_randomness (other.m_randomness),
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
    m_size (1),
    m_element (element),
    m_children (2, NULL)
  {
  }

  template <typename T>
  typename TreeNode<T>::const_iterator TreeNode<T>::iterator_at(ArrayList<ConstNodeInfo>& parent_stack, index_type index, index_type left_part) const
  {
    assert(left_part <= index && index < left_part + m_size);
    ConstNodeInfo info {this, left_part};
    parent_stack.push(info);
    index_type left = left_size() + left_part;
    if (index == left) {
      return const_iterator(parent_stack, left_part);
    } else if (index < left) {
      return m_children[TREE_LEFT]->iterator_at(parent_stack, index, left_part);
    } else {
      return m_children[TREE_RIGHT]->iterator_at(parent_stack, index, left + 1);
    }
  }

  template <typename T>
  typename TreeNode<T>::iterator TreeNode<T>::iterator_at(ArrayList<NodeInfo>& parent_stack, index_type index, index_type left_part)
  {
    assert(left_part <= index && index < left_part + m_size);
    NodeInfo info {this, left_part};
    parent_stack.push(info);
    index_type left = left_part + left_size();
    if (index == left) {
      return iterator(parent_stack, left_part);
    } else if (index < left) {
      return m_children[TREE_LEFT]->iterator_at(parent_stack, index, left_part);
    } else {
      return m_children[TREE_RIGHT]->iterator_at(parent_stack, index, left + 1);
    }
  }

  template <typename T>
  void TreeNode<T>::insert(NodePointer *incoming_pointer_address, const T& element)
  {
    ++m_size;
    direction dir = element_direction(element);
    if (m_children[dir] == NULL) {
      m_children[dir] = new TreeNode<T>(element);
    } else {
      m_children[dir]->insert(&m_children[dir], element);
    }
    if (m_children[dir]->m_randomness < m_randomness) {
      rotate(incoming_pointer_address, dir);
    }
    assert_size();
  }

  template <typename T>
  bool TreeNode<T>::search(const T& element) const
  {
    if (element == m_element) {
      return true;
    }
    direction dir = element_direction(element);
    if (m_children[dir] == NULL) {
      return false;
    } else {
      return m_children[dir]->search(element);
    }
  }

  template <typename T>
  typename TreeNode<T>::iterator TreeNode<T>::upper_bound(ArrayList<NodeInfo>& parent_stack, const T& element, index_type left_part)
  {
    NodeInfo info {this, left_part};
    parent_stack.push(info);
    if (m_children[TREE_LEFT] == NULL && element < m_element) {
      return iterator(parent_stack, left_part);
    }
    if (m_children[TREE_RIGHT] == NULL && element >= m_element) {
      return parent_stack[0].node->end();
    }
    if (element < m_element) {
       iterator left_upper_bound = m_children[TREE_LEFT]->upper_bound(parent_stack, element, left_part);
       if (left_upper_bound == parent_stack[0].node->end()) {
         return iterator(parent_stack, left_part + left_size());
       } else {
         return left_upper_bound;
       }
    } else {
      return m_children[TREE_RIGHT]->upper_bound(parent_stack, element, left_part + 1 + left_size());
    }
  }

  template <typename T>
  typename TreeNode<T>::const_iterator TreeNode<T>::upper_bound(ArrayList<ConstNodeInfo>& parent_stack, const T& element, index_type left_part) const
  {
    parent_stack.push(ConstNodeInfo(this, left_part));
    if (m_children[TREE_LEFT] == NULL && element < m_element) {
      return iterator(parent_stack, left_part);
    }
    if (m_children[TREE_RIGHT] == NULL && element >= m_element) {
      return parent_stack[0].node->end();
    }
    if (element < m_element) {
       const_iterator left_upper_bound = m_children[TREE_LEFT]->upper_bound(parent_stack, element, left_part);
       if (left_upper_bound == parent_stack[0].node->end()) {
         return const_iterator(parent_stack, left_part + left_size());
       } else {
         return left_upper_bound;
       }
    } else {
      return m_children[TREE_RIGHT]->upper_bound(parent_stack, element, left_part + 1 + left_size());
    }
  }

  template <typename T>
  typename TreeNode<T>::const_iterator TreeNode<T>::lower_bound(ArrayList<ConstNodeInfo>& parent_stack, const T& element, index_type left_part) const
  {
    parent_stack.push(ConstNodeInfo(this, left_part));
    if (m_children[TREE_LEFT] == NULL && element <= m_element) {
      return iterator(parent_stack, left_part);
    }
    if (m_children[TREE_RIGHT] == NULL && element > m_element) {
      return parent_stack[0].node->end();
    }
    if (element < m_element) {
      return m_children[TREE_LEFT]->lower_bound(parent_stack, element, left_part);
    } else if (element > m_element) {
      return m_children[TREE_RIGHT]->lower_bound(parent_stack, element, left_part + 1 + left_size());
    } else {
      const_iterator left_lower_bound = m_children[TREE_LEFT]->lower_bound(parent_stack, element, left_part);
      if (left_lower_bound == parent_stack[0].node->end()) {
        return const_iterator(parent_stack, left_part + left_size());
      } else {
        return left_lower_bound;
      }
    }
  }

  template <typename T>
  typename TreeNode<T>::iterator TreeNode<T>::lower_bound(ArrayList<NodeInfo>& parent_stack, const T& element, index_type left_part)
  {
    NodeInfo info {this, left_part};
    parent_stack.push(info);
    if (m_children[TREE_LEFT] == NULL && element <= m_element) {
      return iterator(parent_stack, left_part);
    }
    if (m_children[TREE_RIGHT] == NULL && element > m_element) {
      return parent_stack[0].node->end();
    }
    if (element < m_element) {
      return m_children[TREE_LEFT]->lower_bound(parent_stack, element, left_part);
    } else if (element > m_element) {
      return m_children[TREE_RIGHT]->lower_bound(parent_stack, element, left_part + 1 + left_size());
    } else {
      iterator left_lower_bound = m_children[TREE_LEFT]->lower_bound(parent_stack, element, left_part);
      if (left_lower_bound == parent_stack[0].node->end()) {
        return iterator(parent_stack, left_part + left_size());
      } else {
        return left_lower_bound;
      }
    }
  }

  template <typename T>
  std::pair< typename TreeNode<T>::iterator, typename TreeNode<T>::iterator > TreeNode<T>::equal_range(ArrayList<NodeInfo>& parent_stack, const T& element, index_type left_part)
  {
    iterator lower (lower_bound(parent_stack, element, left_part));
    iterator upper (lower);
    while (*upper == element) {
      ++upper;
    }
    return make_pair(lower, upper);
  }

  template <typename T>
  std::pair< typename TreeNode<T>::const_iterator, typename TreeNode<T>::const_iterator > TreeNode<T>::equal_range(ArrayList<ConstNodeInfo>& parent_stack, const T& element, index_type left_part) const
  {
    const_iterator lower (lower_bound(parent_stack, element, left_part));
    const_iterator upper (lower);
    while (*upper == element) {
      ++upper;
    }
    return make_pair(lower, upper);
  }

  template <typename T>
  const T& TreeNode<T>::operator[](index_type index) const
  {
    assert(index < m_size);
    index_type left = left_size();
    if (index < left) {
      return m_children[TREE_LEFT]->operator[](index);
    } else if (index > left) {
      return m_children[TREE_RIGHT]->operator[](index - 1 - left);
    } else {
      return m_element;
    }
  }

  template <typename T>
  T& TreeNode<T>::operator[](index_type index)
  {
    assert(index < m_size);
    index_type left = left_size();
    if (index < left) {
      return m_children[TREE_LEFT]->operator[](index);
    } else if (index > left) {
      return m_children[TREE_RIGHT]->operator[](index - 1 - left);
    } else {
      return m_element;
    }
  }

  template <typename T>
  index_type TreeNode<T>::remove_all(NodePointer *incoming_pointer_address, const T& element)
  {
    if (m_element == element) {
      index_type left_n = m_children[TREE_LEFT] == NULL ? 0 : m_children[TREE_LEFT]->remove_all(&m_children[TREE_LEFT], element);
      index_type right_n = m_children[TREE_RIGHT] == NULL ? 0 : m_children[TREE_RIGHT]->remove_all(&m_children[TREE_RIGHT], element);
      m_size -= left_n + right_n;
      remove(incoming_pointer_address, element);
      return 1 + left_n + right_n;
    } else {
      index_type dir = element_direction(element);
      if (m_children[dir] == NULL) {
        return 0;
      } else {
        index_type removed =  m_children[dir]->remove_all(&m_children[dir], element);
        m_size -= removed;
        assert_size();
        return removed;
      }
    }
  }

  template <typename T>
  bool TreeNode<T>::remove(NodePointer *incoming_pointer_address, const T& element)
  {
    if (m_element == element) {
      while (m_size > 1) {
        direction dir = min_rand_direction();
        rotate(incoming_pointer_address, dir);
        NodePointer new_parent = *incoming_pointer_address;
        --(new_parent->m_size);
        incoming_pointer_address = &(new_parent->m_children[1 - dir]);
        assert(*incoming_pointer_address == this);
      }
      delete this;
      *incoming_pointer_address = NULL;
      return true;
    } else {
      index_type dir = element_direction(element);
      if (m_children[dir] == NULL) {
        return false;
      } else {
        bool removed = m_children[dir]->remove(&m_children[dir], element);
        m_size -= removed;
        assert_size();
        return removed;
      }
    }
  }

  template <typename T>
  typename TreeNode<T>::iterator TreeNode<T>::begin()
  {
    ArrayList<NodeInfo> empty_info;
    return iterator_at(empty_info, 0, 0);
  }

  template <typename T>
  typename TreeNode<T>::iterator TreeNode<T>::end()
  {
    ArrayList<NodeInfo> empty_info;
    return iterator(empty_info, m_size);
  }

  template <typename T>
  typename TreeNode<T>::const_iterator TreeNode<T>::begin() const
  {
    ArrayList<ConstNodeInfo> empty_info;
    return iterator_at(empty_info, 0, 0);
  }

  template <typename T>
  typename TreeNode<T>::const_iterator TreeNode<T>::end() const
  {
    ArrayList<ConstNodeInfo> empty_info;
    return iterator(empty_info, m_size);
  }

  template <typename T>
  TreeNode<T>::~TreeNode()
  {
    for (index_type dir = TREE_LEFT; dir <= TREE_RIGHT; ++dir) {
      delete m_children[dir];
    }
  }

  template <typename T>
  inline void TreeNode<T>::rotate(NodePointer *incoming_pointer_address, index_type direction)
  {
    // Precondition
    assert(m_children[direction] != NULL);

    // Define a few aliases
    NodePointer new_parent = m_children[direction];
    NodePointer new_this_child = new_parent->m_children[1 - direction];
    NodePointer parent_child = new_parent->m_children[direction];

    // Change the pointers
    *incoming_pointer_address = new_parent;
    new_parent->m_children[1 - direction] = this;
    m_children[direction] = new_this_child;

    // Correct the sizes
    index_type old_size = m_size;
    m_size -= 1 + (parent_child == NULL ? 0 : parent_child->size());
    new_parent->m_size = old_size;

    // Postcondition
    assert(new_parent->m_size == new_parent->left_size() + 1 + new_parent->right_size());
    assert_size();
  }

  template <typename T>
  std::ostream& operator<<(std::ostream& out, const TreeNode<T>& node)
  {
    if (node.m_children[TREE_LEFT] != NULL) {
      out << *(node.m_children[TREE_LEFT]) << ", ";
    }
    out << node.m_element;
    if (node.m_children[TREE_RIGHT] != NULL) {
      out << ", " << *(node.m_children[TREE_RIGHT]);
    }
    return out;
  }

}

#endif // TREENODE_H
