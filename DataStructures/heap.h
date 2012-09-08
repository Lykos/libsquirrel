#ifndef DATASTRUCTURES_HEAP_H
#define DATASTRUCTURES_HEAP_H

#include "baselist.h"

namespace DataStructures {

  template <typename T>
  class Heap : public BaseList<T>
  {
  public:
    typedef typename BaseList<T>::size_type size_type;

    Heap();

    Heap(const Heap<T>& other);

    template <typename Begin, typename End>
    Heap(Begin begin, End end);

    template <typename Begin, typename End>
    void push_all(const Begin& begin, const End& end);

    void push(const T& element);

    T pop();

    const T& top() const;

    T& top();

  private:

    inline void bubble_up(size_type index);

    inline void bubble_down(size_type index);

    inline size_type min_child(size_type index) const;

  };
  
}

#include "heap.hpp"

#endif // DATASTRUCTURES_HEAP_H
