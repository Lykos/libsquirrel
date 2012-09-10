#ifndef DATASTRUCTURES_HEAP_H
#define DATASTRUCTURES_HEAP_H

#include "baselist.h"
#include "less.h"
#include <initializer_list>

namespace DataStructures {

  template <typename T, typename Compare = Less<T> >
  class Heap : public BaseList<T>
  {
  public:
    typedef typename BaseList<T>::size_type size_type;

    inline explicit Heap(const Compare& compare = Compare());

    inline Heap(const Heap<T, Compare>& other);

    inline Heap(std::initializer_list<T> list);

    template <typename InputIterator>
    inline Heap(InputIterator begin, InputIterator end, const Compare& compare = Compare());

    template <typename InputIterator>
    inline void push_all(InputIterator begin, InputIterator end);

    inline void push(const T& element);

    inline T pop();

    inline const T& top() const;

    inline T& top();

    inline void reorganize();

    inline void clear();

  private:
    Compare m_compare;

    inline void bubble_up(size_type index);

    inline void bubble_down(size_type index);

    inline size_type min_child(size_type index) const;

  };
  
}

#include "heap.hpp"

#endif // DATASTRUCTURES_HEAP_H
