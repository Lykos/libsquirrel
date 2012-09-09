#ifndef DATASTRUCTURES_HEAP_H
#define DATASTRUCTURES_HEAP_H

#include "baselist.h"

namespace DataStructures {

  template <typename T>
  class Heap : public BaseList<T>
  {
  public:
    typedef typename BaseList<T>::size_type size_type;

    inline Heap();

    inline Heap(const Heap<T>& other);

    template <typename Iterator>
    inline Heap(Iterator begin, Iterator end);

    template <typename Iterator>
    inline void push_all(Iterator begin, Iterator end);

    inline void push(const T& element);

    inline T pop();

    inline const T& top() const;

    inline T& top();

    inline void reorganize();

    inline void clear();

  private:

    inline void bubble_up(size_type index);

    inline void bubble_down(size_type index);

    inline size_type min_child(size_type index) const;

  };
  
}

#include "heap.hpp"

#endif // DATASTRUCTURES_HEAP_H
