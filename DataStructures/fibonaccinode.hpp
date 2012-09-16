#ifndef DATASTRUCTURES_FIBONACCINODE_HPP
#define DATASTRUCTURES_FIBONACCINODE_HPP

#include "fibonaccinode.h"

namespace DataStructures {
  
  template <typename T, typename Compare>
  FibonacciNode<T, Compare>::FibonacciNode(const FibonacciHeap<T, Compare>* heap,
                                           const T& element):
    m_heap (heap),
    m_element (element)
  {
    m_left = this;
    m_right = this;
  }

  template <typename T, typename Compare>
  const T& FibonacciNode<T, Compare>::element() const
  {
    return m_element;
  }

  template <typename T, typename Compare>
  T& FibonacciNode<T, Compare>::element()
  {
    return m_element;
  }

} // namespace DataStructures

#endif // DATASTRUCTURES_FIBONACCINODE_HPP
