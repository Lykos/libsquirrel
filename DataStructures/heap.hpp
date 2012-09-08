#ifndef DATASTRUCTURES_HEAP_HPP
#define DATASTRUCTURES_HEAP_HPP

#include "baselist.h"
#include "heaparithmetic.h"

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

    const T& top() const { PREC_EMPTY(); return BaseList<T>::at(0); }

    T& top() { PREC_EMPTY(); return BaseList<T>::at(0); }

  private:

    inline void bubble_up(size_type index);

    inline void bubble_down(size_type index);

    inline size_type min_child(size_type index) const;

  };

  template <typename T>
  Heap<T>::Heap():
    BaseList<T>()
  {
  }

  template <typename T>
  Heap<T>::Heap(const Heap<T> &other):
    BaseList<T>(other)
  {
  }

  template <typename T>
  template <typename Begin, typename End>
  Heap<T>::Heap(Begin begin, End end):
    BaseList<T>()
  {
    push_all(begin, end);
  }

  template <typename T>
  template <typename Begin, typename End>
  void Heap<T>::push_all(const Begin& begin, const End& end)
  {
    if (begin > end) {
      return;
    }
    size_type i = BaseList<T>::size();
    BaseList<T>::prepare_size(BaseList<T>::size() + (end - begin));
    for (Begin it = begin; it != end; ++it, ++i) {
      BaseList<T>::create(i, *it);
      bubble_up(i);
    }
  }

  template <typename T>
  void Heap<T>::push(const T& element)
  {
    size_type old_size = BaseList<T>::size();
    BaseList<T>::prepare_size(BaseList<T>::size() + 1);
    BaseList<T>::create(old_size, element);
    bubble_up(old_size);
  }

  template <typename T>
  T Heap<T>::pop()
  {
    PREC_EMPTY();
    T element = BaseList<T>::at(0);
    BaseList<T>::destroy(0);
    BaseList<T>::move(0, BaseList<T>::size() - 1);
    BaseList<T>::prepare_size(BaseList<T>::size() - 1);
    bubble_down(0);
    return element;
  }

  template <typename T>
  inline typename Heap<T>::size_type Heap<T>::min_child(size_type index) const
  {
    size_type left = HeapArithmetic::left_child(index);
    size_type right = HeapArithmetic::right_child(index);
    assert(left < BaseList<T>::size());
    if (right >= BaseList<T>::size()) {
      return left;
    } else {
      return BaseList<T>::at(left) < BaseList<T>::at(right) ? left : right;
    }
  }

  template <typename T>
  inline void Heap<T>::bubble_up(size_type index)
  {
    while (index > 0) {
      size_type new_index = HeapArithmetic::parent(index);
      if (BaseList<T>::at(new_index) < BaseList<T>::at(index)) {
        return;
      }
      BaseList<T>::swap(new_index, index);
      index = new_index;
    }
  }

  template <typename T>
  inline void Heap<T>::bubble_down(size_type index)
  {
    while (HeapArithmetic::left_child(index) < BaseList<T>::size()) {
      size_type new_index = min_child(index);
      if (BaseList<T>::at(index) < BaseList<T>::at(new_index)) {
        return;
      }
      BaseList<T>::swap(new_index, index);
      index = new_index;
    }
  }
  
}

#endif // DATASTRUCTURES_HEAP_HPP
