#ifndef DATASTRUCTURES_HEAP_H
#define DATASTRUCTURES_HEAP_H

#include "DataStructures_global.h"
#include "baselist.h"

namespace DataStructures {

  inline index_type level_base(index_type index);

  index_type parent(index_type index);

  index_type right_child(index_type index);

  index_type left_child(index_type index);

  template <typename T>
  class DATASTRUCTURESSHARED_EXPORT Heap : public BaseList<T>
  {
  public:
    Heap();

    Heap(const Heap<T>& other);

    template <typename Begin, typename End>
    Heap(Begin begin, End end);

    template <typename Begin, typename End>
    void push_all(const Begin& begin, const End& end);

    void push(const T& element);

    T pop();

    const T& top() const { check_empty(); return BaseList<T>::m_content[0]; }

    T& top() { check_empty(); return BaseList<T>::m_content[0]; }

  private:

    inline void bubble_up(index_type index);

    inline void bubble_down(index_type index);

    inline index_type min_child(index_type index) const;

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
    index_type i = BaseList<T>::m_size;
    BaseList<T>::prepare_size(BaseList<T>::m_size + (end - begin));
    for (Begin it = begin; it != end; ++it, ++i) {
      BaseList<T>::m_content[i] = *it;
      bubble_up(i);
    }
  }

  template <typename T>
  void Heap<T>::push(const T& element)
  {
    index_type old_size = BaseList<T>::m_size;
    BaseList<T>::prepare_size(BaseList<T>::m_size + 1);
    BaseList<T>::m_content[old_size] = element;
    bubble_up(old_size);
  }

  template <typename T>
  T Heap<T>::pop()
  {
    check_empty();
    T element = BaseList<T>::m_content[0];
    BaseList<T>::m_content[0] = BaseList<T>::m_content[BaseList<T>::m_size - 1];
    BaseList<T>::destroy(BaseList<T>::m_size - 1);
    BaseList<T>::prepare_size(BaseList<T>::m_size - 1);
    bubble_down(0);
    return element;
  }

  template <typename T>
  inline index_type Heap<T>::min_child(index_type index) const
  {
    index_type left = left_child(index);
    index_type right = right_child(index);
    assert(left < BaseList<T>::m_size);
    if (right >= BaseList<T>::m_size) {
      return left;
    } else {
      return BaseList<T>::m_content[left] < BaseList<T>::m_content[right] ? left : right;
    }
  }

  template <typename T>
  inline void Heap<T>::bubble_up(index_type index)
  {
    while (index > 0) {
      index_type new_index = parent(index);
      if (BaseList<T>::m_content[new_index] < BaseList<T>::m_content[index]) {
        return;
      }
      std::swap(BaseList<T>::m_content[new_index], BaseList<T>::m_content[index]);
      index = new_index;
    }
  }

  template <typename T>
  inline void Heap<T>::bubble_down(index_type index)
  {
    while (left_child(index) < BaseList<T>::m_size) {
      index_type new_index = min_child(index);
      if (BaseList<T>::m_content[index] < BaseList<T>::m_content[new_index]) {
        return;
      }
      std::swap(BaseList<T>::m_content[new_index], BaseList<T>::m_content[index]);
      index = new_index;
    }
  }
  
}

#endif // DATASTRUCTURES_HEAP_H
