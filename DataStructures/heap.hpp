#ifndef DATASTRUCTURES_HEAP_HPP
#define DATASTRUCTURES_HEAP_HPP

#include "heap.h"
#include "less.h"
#include "baselist.h"
#include "heaparithmetic.h"

namespace DataStructures {

  template <typename T, typename Compare>
  inline Heap<T, Compare>::Heap(std::initializer_list<T> list):
    Heap<T, Compare>(list.begin(), list.end())
  {}


  template <typename T, typename Compare>
  Heap<T, Compare>::Heap(const Compare& compare):
    BaseList<T>(),
    m_compare (compare)
  {}

  template <typename T, typename Compare>
  Heap<T, Compare>::Heap(const Heap<T, Compare> &other):
    BaseList<T>(other),
    m_compare (other.m_compare)
  {}

  template <typename T, typename Compare>
  template <typename InputIterator>
  Heap<T, Compare>::Heap(InputIterator begin, InputIterator end, const Compare& compare):
    BaseList<T>(),
    m_compare (compare)
  {
    push_all(begin, end);
  }

  template <typename T, typename Compare>
  const T& Heap<T, Compare>::top() const
  {
    PREC_EMPTY();
    return BaseList<T>::at(0);
  }

  template <typename T, typename Compare>
  T& Heap<T, Compare>::top()
  {
    PREC_EMPTY();
    return BaseList<T>::at(0);
  }

  template <typename T, typename Compare>
  inline void Heap<T, Compare>::reorganize()
  {}

  template <typename T, typename Compare>
  template <typename InputIterator>
  void Heap<T, Compare>::push_all(InputIterator begin, InputIterator end)
  {
    size_type i = BaseList<T>::size();
    BaseList<T>::prepare_size(BaseList<T>::size() + (end - begin));
    for (; begin != end; ++begin, ++i) {
      BaseList<T>::create(i, *begin);
      bubble_up(i);
    }
  }

  template <typename T, typename Compare>
  void Heap<T, Compare>::push(const T& element)
  {
    size_type old_size = BaseList<T>::size();
    BaseList<T>::prepare_size(BaseList<T>::size() + 1);
    BaseList<T>::create(old_size, element);
    bubble_up(old_size);
  }

  template <typename T, typename Compare>
  T Heap<T, Compare>::pop()
  {
    PREC_EMPTY();
    T element = BaseList<T>::at(0);
    BaseList<T>::destroy(0);
    BaseList<T>::move(0, BaseList<T>::size() - 1);
    BaseList<T>::prepare_size(BaseList<T>::size() - 1);
    bubble_down(0);
    return element;
  }

  template <typename T, typename Compare>
  inline typename Heap<T, Compare>::size_type Heap<T, Compare>::min_child(size_type index) const
  {
    size_type left = HeapArithmetic::left_child(index);
    size_type right = HeapArithmetic::right_child(index);
    assert(left < BaseList<T>::size());
    if (right >= BaseList<T>::size()) {
      return left;
    } else {
      return m_compare(BaseList<T>::at(left), BaseList<T>::at(right)) ? left : right;
    }
  }

  template <typename T, typename Compare>
  inline void Heap<T, Compare>::bubble_up(size_type index)
  {
    while (index > 0) {
      size_type new_index = HeapArithmetic::parent(index);
      if (m_compare(BaseList<T>::at(new_index), BaseList<T>::at(index))) {
        return;
      }
      BaseList<T>::swap(new_index, index);
      index = new_index;
    }
  }

  template <typename T, typename Compare>
  inline void Heap<T, Compare>::bubble_down(size_type index)
  {
    while (HeapArithmetic::left_child(index) < BaseList<T>::size()) {
      size_type new_index = min_child(index);
      if (m_compare(BaseList<T>::at(index), BaseList<T>::at(new_index))) {
        return;
      }
      BaseList<T>::swap(new_index, index);
      index = new_index;
    }
  }
  
}

#endif // DATASTRUCTURES_HEAP_HPP
