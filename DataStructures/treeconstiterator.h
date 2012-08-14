#ifndef TreeConstIterator_H
#define TreeConstIterator_H

#include "baseiterator.h"

namespace DataStructures {

  template <typename T, typename Node>
  TreeConstIterator<T, Node> operator+(index_type i, const TreeConstIterator<T, Node>& it);

  template <typename T, typename Node>
  class TreeConstIterator : public BaseIterator<T>
  {
    friend TreeConstIterator<T, Node> operator+ <> (index_type i, const TreeConstIterator<T, Node>& it);
    friend class TreeIterator<T, Node>;
  public:
    typedef struct { const Node *node; index_type left_part; } ConstNodeInfo;
    TreeConstIterator(const ArrayList<ConstNodeInfo> &parent_stack = ArrayList<ConstNodeInfo>(), index_type index = 0);
    TreeConstIterator(const TreeIterator<T, Node>& other);
    TreeConstIterator(const TreeConstIterator<T, Node>& other);
    difference_type operator-(const TreeIterator<T, Node>& other) const;
    difference_type operator-(const TreeConstIterator<T, Node>& other) const;
    TreeConstIterator<T, Node> operator++(int);
    TreeConstIterator<T, Node>& operator++();
    TreeConstIterator<T, Node> operator--(int);
    TreeConstIterator<T, Node>& operator--();
    TreeConstIterator<T, Node>& operator=(const TreeConstIterator<T, Node>& other);
    TreeConstIterator<T, Node> operator+(index_type i) const;
    TreeConstIterator<T, Node> operator-(index_type i) const;
    TreeConstIterator<T, Node>& operator+=(index_type i);
    TreeConstIterator<T, Node>& operator-=(index_type i);
    const T& operator*();
    const T& operator[](index_type i);
  private:
    typedef typename TreeIterator<T, Node>::NodeInfo NodeInfo;
    ArrayList<ConstNodeInfo> m_parent_stack;
    inline void local_search();
    inline const Node& node() const { return *m_parent_stack.top().node; }
    inline index_type left_part() const { return m_parent_stack.top().left_part; }
  };

  template <typename T, typename Node>
  TreeConstIterator<T, Node>::TreeConstIterator(const ArrayList<ConstNodeInfo> &parent_stack, index_type index):
    BaseIterator<T> (index),
    m_parent_stack (parent_stack)
  {
  }

  template <typename T, typename Node>
  TreeConstIterator<T, Node>::TreeConstIterator(const TreeIterator<T, Node>& other):
    BaseIterator<T> (other.m_index)
  {
    for (typename ArrayList<NodeInfo>::const_iterator it = other.m_parent_stack.begin(); it != other.m_parent_stack.end(); ++it) {
      ConstNodeInfo info {(*it).node, (*it).left_part};
      m_parent_stack.push(info);
    }
  }

  template <typename T, typename Node>
  TreeConstIterator<T, Node>::TreeConstIterator(const TreeConstIterator<T, Node>& other):
    BaseIterator<T> (other.m_index),
    m_parent_stack (other.m_parent_stack)
  {
  }

  template <typename T, typename Node>
  difference_type TreeConstIterator<T, Node>::operator-(const TreeIterator<T, Node>& other) const
  {
    return BaseIterator<T>::m_index - other.m_index;
  }

  template <typename T, typename Node>
  difference_type TreeConstIterator<T, Node>::operator-(const TreeConstIterator<T, Node>& other) const
  {
    return BaseIterator<T>::m_index - other.m_index;
  }

  template <typename T, typename Node>
  TreeConstIterator<T, Node> operator+(index_type index, const TreeConstIterator<T, Node>& other)
  {
    return other + index;
  }

  template <typename T, typename Node>
  TreeConstIterator<T, Node> TreeConstIterator<T, Node>::operator++(int)
  {
    TreeConstIterator<T, Node> old (*this);
    operator++();
    return old;
  }

  template <typename T, typename Node>
  TreeConstIterator<T, Node>& TreeConstIterator<T, Node>::operator++()
  {
    ++BaseIterator<T>::m_index;
    local_search();
    return *this;
  }

  template <typename T, typename Node>
  TreeConstIterator<T, Node> TreeConstIterator<T, Node>::operator--(int)
  {
    TreeConstIterator<T, Node> old (*this);
    operator--();
    return old;
  }

  template <typename T, typename Node>
  TreeConstIterator<T, Node>& TreeConstIterator<T, Node>::operator--()
  {
    --BaseIterator<T>::m_index;
    local_search();
    return *this;
  }

  template <typename T, typename Node>
  TreeConstIterator<T, Node>& TreeConstIterator<T, Node>::operator=(const TreeConstIterator& other)
  {
    BaseIterator<T>::m_index = other.m_index;
    m_parent_stack = other.m_parent_stack;
    return *this;
  }

  template <typename T, typename Node>
  TreeConstIterator<T, Node> TreeConstIterator<T, Node>::operator+(index_type index) const
  {
    TreeConstIterator<T, Node> other (*this);
    return other += index;
  }

  template <typename T, typename Node>
  TreeConstIterator<T, Node> TreeConstIterator<T, Node>::operator-(index_type index) const
  {
    TreeConstIterator<T, Node> other (*this);
    return other -= index;
  }

  template <typename T, typename Node>
  TreeConstIterator<T, Node>& TreeConstIterator<T, Node>::operator+=(index_type index)
  {
    BaseIterator<T>::m_index += index;
    local_search();
    return *this;
  }

  template <typename T, typename Node>
  TreeConstIterator<T, Node>& TreeConstIterator<T, Node>::operator-=(index_type index)
  {
    BaseIterator<T>::m_index -= index;
    local_search();
    return *this;
  }

  template <typename T, typename Node>
  const T& TreeConstIterator<T, Node>::operator*()
  {
    return m_parent_stack.top().node->get_element();
  }

  template <typename T, typename Node>
  const T& TreeConstIterator<T, Node>::operator[](index_type index)
  {
    return *(operator+(index));
  }

  template <typename T, typename Node>
  inline void TreeConstIterator<T, Node>::local_search()
  {
    while (BaseIterator<T>::m_index < left_part() || BaseIterator<T>::m_index >= left_part() + node().size()) {
      if (m_parent_stack.size() > 1) {
        m_parent_stack.pop();
      } else {
        return;
      }
    }
    node().iterator_at(m_parent_stack, BaseIterator<T>::m_index, left_part());
  }

}

#endif // TreeConstIterator_H
