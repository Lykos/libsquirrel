#ifndef DATASTRUCTURES_FIBONACCIHEAP_H
#define DATASTRUCTURES_FIBONACCIHEAP_H

#include "fibonaccinode.h"
#include "arraylist.h"

namespace DataStructures {
  
  template <typename T>
  class FibonacciHeap
  {
  public:
    inline FibonacciHeap();

    inline FibonacciHeap(const FibonacciHeap& other);

    template <typename Iterator>
    inline FibonacciHeap(const Iterator& begin, const Iterator& end);

    inline void insert(const T& element);

    inline void remove(const T& element);

    inline const T& top() const;

    inline T& top();

    inline T pop();

    inline void merge(const FibonacciHeap& other);

    inline void merge(FibonacciHeap&& other);

  private:
    typedef FibonacciNode<T>* NodePointer;

    ArrayList<NodePointer> m_children;

    size_type m_size;

    Treap<NodePointer> m_elements;

  };
  
} // namespace DataStructures

#endif // DATASTRUCTURES_FIBONACCIHEAP_H
