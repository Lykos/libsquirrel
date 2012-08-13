#ifndef TREAPNODE_H
#define TREAPNODE_H

#include "infiniterandom.h"
#include "treapiterator.h"
#include "treapconstiterator.h"
#include <iostream>

#define LEFT 0
#define RIGHT 1
#define assert_size() assert(m_size == left_size() + 1 + right_size())

namespace DataStructures {

  template <typename T>
  std::ostream& operator<<(std::ostream& out, const TreapNode<T>& it);

  template <typename T>
  class TreapNode
  {
    friend std::ostream& operator<< <> (std::ostream& out, const TreapNode<T>& it);
  public:
    typedef TreapConstIterator<T> const_iterator;

    typedef TreapIterator<T> iterator;

  private:
    typedef TreapNode<T>* NodePointer;

    typedef typename iterator::NodeInfo NodeInfo;

    typedef typename const_iterator::ConstNodeInfo ConstNodeInfo;

  public:
    TreapNode(const TreapNode& other);

    TreapNode(const T& element);

    void insert(NodePointer *incoming_pointer_address, const T& element);

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

    bool remove(NodePointer *incoming_pointer_address, const T& element);

    inline T& get_element() { return m_element; }

    inline const T& get_element() const { return m_element; }

    inline index_type size() const { return m_size; }

    iterator iterator_at(ArrayList<NodeInfo>& parent_stack, index_type index, index_type left_part);

    const_iterator iterator_at(ArrayList<ConstNodeInfo>& parent_stack, index_type index, index_type left_part) const;

    iterator begin();

    iterator end();

    const_iterator begin() const;

    const_iterator end() const;

    ~TreapNode();
  private:

    typedef index_type direction;

    inline direction element_direction(const T& element) const { return element < m_element ? LEFT : RIGHT; }

    inline direction min_rand_direction() const;

    inline void rotate(NodePointer *incoming_pointer_address, direction dir);

    inline index_type left_size() const { return m_children[LEFT] == NULL ? 0 : m_children[LEFT]->size(); }

    inline index_type right_size() const { return m_children[RIGHT] == NULL ? 0 : m_children[RIGHT]->size(); }

    index_type m_size;

    T m_element;

    InfiniteRandom m_randomness;

    ArrayList<NodePointer> m_children;

  };

  template <typename T>
  TreapNode<T>::TreapNode(const TreapNode<T> &other):
    m_size (other.m_size),
    m_element (other.m_element),
    m_randomness (other.m_randomness),
    m_children (2, NULL)
  {
    for (direction dir = LEFT; dir <= RIGHT; ++dir) {
      if (other.m_children[dir] != NULL) {
        m_children[dir] = new TreapNode<T>(*other.m_children[dir]);
      }
    }
  }

  template <typename T>
  TreapNode<T>::TreapNode(const T& element):
    m_size (1),
    m_element (element),
    m_children (2, NULL)
  {
  }

  template <typename T>
  typename TreapNode<T>::const_iterator TreapNode<T>::iterator_at(ArrayList<ConstNodeInfo>& parent_stack, index_type index, index_type left_part) const
  {
    assert(left_part <= index && index < left_part + m_size);
    ConstNodeInfo info {this, left_part};
    parent_stack.push(info);
    index_type left = left_size() + left_part;
    if (index == left) {
      return const_iterator(parent_stack, left_part);
    } else if (index < left) {
      return m_children[LEFT]->iterator_at(parent_stack, index, left_part);
    } else {
      return m_children[RIGHT]->iterator_at(parent_stack, index, left + 1);
    }
  }

  template <typename T>
  typename TreapNode<T>::iterator TreapNode<T>::iterator_at(ArrayList<NodeInfo>& parent_stack, index_type index, index_type left_part)
  {
    assert(left_part <= index && index < left_part + m_size);
    NodeInfo info {this, left_part};
    parent_stack.push(info);
    index_type left = left_part + left_size();
    if (index == left) {
      return iterator(parent_stack, left_part);
    } else if (index < left) {
      return m_children[LEFT]->iterator_at(parent_stack, index, left_part);
    } else {
      return m_children[RIGHT]->iterator_at(parent_stack, index, left + 1);
    }
  }

  template <typename T>
  void TreapNode<T>::insert(NodePointer *incoming_pointer_address, const T& element)
  {
    ++m_size;
    direction dir = element_direction(element);
    if (m_children[dir] == NULL) {
      m_children[dir] = new TreapNode<T>(element);
    } else {
      m_children[dir]->insert(&m_children[dir], element);
    }
    if (m_children[dir]->m_randomness < m_randomness) {
      rotate(incoming_pointer_address, dir);
    }
    assert_size();
  }

  template <typename T>
  bool TreapNode<T>::search(const T& element) const
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
  typename TreapNode<T>::iterator TreapNode<T>::upper_bound(ArrayList<NodeInfo>& parent_stack, const T& element, index_type left_part)
  {
    NodeInfo info {this, left_part};
    parent_stack.push(info);
    if (m_children[LEFT] == NULL && element < m_element) {
      return iterator(parent_stack, left_part);
    }
    if (m_children[RIGHT] == NULL && element >= m_element) {
      return parent_stack[0].node->end();
    }
    if (element < m_element) {
       iterator left_upper_bound = m_children[LEFT]->upper_bound(parent_stack, element, left_part);
       if (left_upper_bound == parent_stack[0].node->end()) {
         return iterator(parent_stack, left_part + left_size());
       } else {
         return left_upper_bound;
       }
    } else {
      return m_children[RIGHT]->upper_bound(parent_stack, element, left_part + 1 + left_size());
    }
  }

  template <typename T>
  typename TreapNode<T>::const_iterator TreapNode<T>::upper_bound(ArrayList<ConstNodeInfo>& parent_stack, const T& element, index_type left_part) const
  {
    parent_stack.push(ConstNodeInfo(this, left_part));
    if (m_children[LEFT] == NULL && element < m_element) {
      return iterator(parent_stack, left_part);
    }
    if (m_children[RIGHT] == NULL && element >= m_element) {
      return parent_stack[0].node->end();
    }
    if (element < m_element) {
       const_iterator left_upper_bound = m_children[LEFT]->upper_bound(parent_stack, element, left_part);
       if (left_upper_bound == parent_stack[0].node->end()) {
         return const_iterator(parent_stack, left_part + left_size());
       } else {
         return left_upper_bound;
       }
    } else {
      return m_children[RIGHT]->upper_bound(parent_stack, element, left_part + 1 + left_size());
    }
  }

  template <typename T>
  typename TreapNode<T>::const_iterator TreapNode<T>::lower_bound(ArrayList<ConstNodeInfo>& parent_stack, const T& element, index_type left_part) const
  {
    parent_stack.push(ConstNodeInfo(this, left_part));
    if (m_children[LEFT] == NULL && element <= m_element) {
      return iterator(parent_stack, left_part);
    }
    if (m_children[RIGHT] == NULL && element > m_element) {
      return parent_stack[0].node->end();
    }
    if (element < m_element) {
      return m_children[LEFT]->lower_bound(parent_stack, element, left_part);
    } else if (element > m_element) {
      return m_children[RIGHT]->lower_bound(parent_stack, element, left_part + 1 + left_size());
    } else {
      const_iterator left_lower_bound = m_children[LEFT]->lower_bound(parent_stack, element, left_part);
      if (left_lower_bound == parent_stack[0].node->end()) {
        return const_iterator(parent_stack, left_part + left_size());
      } else {
        return left_lower_bound;
      }
    }
  }

  template <typename T>
  typename TreapNode<T>::iterator TreapNode<T>::lower_bound(ArrayList<NodeInfo>& parent_stack, const T& element, index_type left_part)
  {
    NodeInfo info {this, left_part};
    parent_stack.push(info);
    if (m_children[LEFT] == NULL && element <= m_element) {
      return iterator(parent_stack, left_part);
    }
    if (m_children[RIGHT] == NULL && element > m_element) {
      return parent_stack[0].node->end();
    }
    if (element < m_element) {
      return m_children[LEFT]->lower_bound(parent_stack, element, left_part);
    } else if (element > m_element) {
      return m_children[RIGHT]->lower_bound(parent_stack, element, left_part + 1 + left_size());
    } else {
      iterator left_lower_bound = m_children[LEFT]->lower_bound(parent_stack, element, left_part);
      if (left_lower_bound == parent_stack[0].node->end()) {
        return iterator(parent_stack, left_part + left_size());
      } else {
        return left_lower_bound;
      }
    }
  }

  template <typename T>
  std::pair< typename TreapNode<T>::iterator, typename TreapNode<T>::iterator > TreapNode<T>::equal_range(ArrayList<NodeInfo>& parent_stack, const T& element, index_type left_part)
  {
    iterator lower (lower_bound(parent_stack, element, left_part));
    iterator upper (lower);
    while (*upper == element) {
      ++upper;
    }
    return make_pair(lower, upper);
  }

  template <typename T>
  std::pair< typename TreapNode<T>::const_iterator, typename TreapNode<T>::const_iterator > TreapNode<T>::equal_range(ArrayList<ConstNodeInfo>& parent_stack, const T& element, index_type left_part) const
  {
    const_iterator lower (lower_bound(parent_stack, element, left_part));
    const_iterator upper (lower);
    while (*upper == element) {
      ++upper;
    }
    return make_pair(lower, upper);
  }

  template <typename T>
  const T& TreapNode<T>::operator[](index_type index) const
  {
    assert(index < m_size);
    index_type left = left_size();
    if (index < left) {
      return m_children[LEFT]->operator[](index);
    } else if (index > left) {
      return m_children[RIGHT]->operator[](index - 1 - left);
    } else {
      return m_element;
    }
  }

  template <typename T>
  T& TreapNode<T>::operator[](index_type index)
  {
    assert(index < m_size);
    index_type left = left_size();
    if (index < left) {
      return m_children[LEFT]->operator[](index);
    } else if (index > left) {
      return m_children[RIGHT]->operator[](index - 1 - left);
    } else {
      return m_element;
    }
  }

  template <typename T>
  index_type TreapNode<T>::remove_all(NodePointer *incoming_pointer_address, const T& element)
  {
    if (m_element == element) {
      index_type left_n = m_children[LEFT] == NULL ? 0 : m_children[LEFT]->remove_all(&m_children[LEFT], element);
      index_type right_n = m_children[RIGHT] == NULL ? 0 : m_children[RIGHT]->remove_all(&m_children[RIGHT], element);
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
  bool TreapNode<T>::remove(NodePointer *incoming_pointer_address, const T& element)
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
  typename TreapNode<T>::iterator TreapNode<T>::begin()
  {
    ArrayList<NodeInfo> empty_info;
    return iterator_at(empty_info, 0, 0);
  }

  template <typename T>
  typename TreapNode<T>::iterator TreapNode<T>::end()
  {
    ArrayList<NodeInfo> empty_info;
    return iterator(empty_info, m_size);
  }

  template <typename T>
  typename TreapNode<T>::const_iterator TreapNode<T>::begin() const
  {
    ArrayList<ConstNodeInfo> empty_info;
    return iterator_at(empty_info, 0, 0);
  }

  template <typename T>
  typename TreapNode<T>::const_iterator TreapNode<T>::end() const
  {
    ArrayList<ConstNodeInfo> empty_info;
    return iterator(empty_info, m_size);
  }

  template <typename T>
  TreapNode<T>::~TreapNode()
  {
    for (index_type dir = LEFT; dir <= RIGHT; ++dir) {
      delete m_children[dir];
    }
  }

  template <typename T>
  inline void TreapNode<T>::rotate(NodePointer *incoming_pointer_address, index_type direction)
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
  inline typename TreapNode<T>::direction TreapNode<T>::min_rand_direction() const
  {
    assert(m_size > 1);
    assert(m_children[LEFT] != NULL || m_children[RIGHT] != NULL);
    if (m_children[LEFT] == NULL) {
      return RIGHT;
    } else if (m_children[RIGHT] == NULL) {
      return LEFT;
    } else {
      return m_children[LEFT]->m_randomness < m_children[RIGHT]->m_randomness ? LEFT : RIGHT;
    }
  }

  template <typename T>
  std::ostream& operator<<(std::ostream& out, const TreapNode<T>& treap)
  {
    if (treap.m_children[LEFT] != NULL) {
      out << *(treap.m_children[LEFT]) << ", ";
    }
    out << treap.m_element;
    if (treap.m_children[RIGHT] != NULL) {
      out << ", " << *(treap.m_children[RIGHT]);
    }
    return out;
  }

}

#undef LEFT
#undef RIGHT

#endif // TREAPNODE_H
