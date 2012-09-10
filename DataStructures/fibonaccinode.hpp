#ifndef DATASTRUCTURES_FIBONACCINODE_HPP
#define DATASTRUCTURES_FIBONACCINODE_HPP

#include "fibonaccinode.h"

namespace DataStructures {
  
  template <typename T>
  FibonacciNode<T, Compare>::FibonacciNode(const FibonacciHeap<T>* heap,
                               const T& element):
    m_heap (heap),
    m_element (element)
  {
    m_left = this;
    m_right = this;
  }

  template <typename T>
  const T& FibonacciNode<T, Compare>::element() const
  {
    return m_element;
  }

  template <typename T>
  T& FibonacciNode<T, Compare>::element()
  {
    return m_element;
  }

} // namespace DataStructures

#endif // DATASTRUCTURES_FIBONACCINODE_HPP
