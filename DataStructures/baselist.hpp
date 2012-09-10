#ifndef DATASTRUCTURES_BASELIST_HPP
#define DATASTRUCTURES_BASELIST_HPP

#include "baselist.h"
#include "arithmetichelper.h"
#include "conditiontype.h"
#include "preconditionviolation.h"
#include <climits>
#include <algorithm>
#include <ostream>

#define PREC_INDEX_LIST(index) PREC(OutOfRange, index < BaseList<T>::size())
#define PREC_EMPTY() PREC(EmptyList, !BaseList<T>::empty())
#define PREC_INDEX_INSERT_LIST(index) PREC(OutOfRange, index <= BaseList<T>::size())

namespace DataStructures {

  template <typename T>
  const typename BaseList<T>::size_type BaseList<T>::DEFAULT_MIN_CAPACITY(16);

  template <typename T>
  const typename BaseList<T>::size_type BaseList<T>::CAPACITY_DECREASE_FACTOR(4);

  template <typename T>
  BaseList<T>::BaseList(size_type initial_size, const T& element):
    m_content (NULL),
    m_size (initial_size),
    m_min_capacity (DEFAULT_MIN_CAPACITY),
    m_is_shrinkable (false)
  {
    adjust_capacity(initial_size);
    for (size_type i = 0; i < size(); ++i) {
      create(i, element);
    }
  }

  template <typename T>
  template <typename InputIterator>
  BaseList<T>::BaseList(InputIterator begin, InputIterator end):
    m_content (NULL),
    m_size (end - begin),
    m_min_capacity (DEFAULT_MIN_CAPACITY),
    m_is_shrinkable (false)
  {
    adjust_capacity(end - begin);
    size_type i = 0;
    for (; begin < end; ++begin, ++i) {
      create(i, *begin);
    }
  }

  /*
  template <typename T>
  BaseList<T>::BaseList(BaseList<T>&& other):
    m_content (other.m_content),
    m_size (other.m_size),
    m_min_capacity (other.m_min_capacity),
    m_is_shrinkable (other.m_is_shrinkable)
  {
    other.m_content = NULL;
    other.m_size = 0;
    assert(m_min_capacity > 0);
  }*/

  template <typename T>
  BaseList<T>::BaseList(const BaseList<T>& other):
    m_content (NULL),
    m_size (other.m_size),
    m_min_capacity (other.m_min_capacity),
    m_is_shrinkable (other.m_is_shrinkable)
  {
    adjust_capacity(other.m_size);
    add_content(other.m_content, 0, other.m_size);
  }

  template <typename T>
  BaseList<T>::~BaseList()
  {
    free(m_content);
  }

  template <typename T>
  inline typename BaseList<T>::size_type BaseList<T>::size() const
  {
    return m_size;
  }

  template <typename T>
  inline bool BaseList<T>::empty() const
  {
    return m_size == 0;
  }

  template <typename T>
  inline typename BaseList<T>::size_type BaseList<T>::min_capacity() const
  {
    return m_min_capacity;
  }

  template <typename T>
  inline void BaseList<T>::min_capacity(size_type min_capacity)
  {
    m_min_capacity = min_capacity;
    if (m_capacity < m_min_capacity) {
      adjust_capacity(m_min_capacity);
    }
  }

  template <typename T>
  inline typename BaseList<T>::size_type BaseList<T>::capacity() const
  {
    return m_capacity;
  }

  template <typename T>
  inline void BaseList<T>::shrinkable(bool is_shrinkable)
  {
    m_is_shrinkable = is_shrinkable;
  }

  template <typename T>
  inline bool BaseList<T>::shrinkable() const
  {
    return m_is_shrinkable;
  }

  /*
  template <typename T>
  inline BaseList<T>& BaseList<T>::operator=(BaseList<T>&& other)
  {
    if (this == &other) {
      return *this;
    }
    // TODO efficiency
    clear();
    free(m_content);
    m_content = other.m_content;
    m_size = other.m_size;
    m_min_capacity = other.m_min_capacity;
    m_is_shrinkable = other.m_is_shrinkable;
    other.m_content = NULL;
    other.m_size = 0;
    return *this;
  }*/

  template <typename T>
  inline BaseList<T>& BaseList<T>::operator=(const BaseList<T>& other)
  {
    if (this == &other) {
      return *this;
    }
    m_min_capacity = other.m_min_capacity;
    prepare_size(other.m_size);
    add_content(other.m_content, 0, other.m_size);
    return *this;
  }

  template <typename T>
  inline void BaseList<T>::create(size_type index, const T& element)
  {
    new(m_content + index) T(element);
  }

  template <typename T>
  inline void BaseList<T>::replace(size_type index, const T& element)
  {
    m_content[index] = element;
  }

  template <typename T>
  inline void BaseList<T>::destroy(size_type index) {
    m_content[index].~T();
  }

  template <typename T>
  inline void BaseList<T>::destroy_part(size_type begin, size_type length) {
    for (size_type i = begin; i < begin + length; ++i) {
      destroy(i);
    }
  }

  template <typename T>
  inline void BaseList<T>::add_content(const T * content, size_type insert_position, size_type length)
  {
    for (size_type i = 0; i < length; ++i) {
      create(insert_position + i, content[i]);
    }
  }

  template <typename T>
  inline void BaseList<T>::move(size_type target, size_type source)
  {
    m_content[target] = m_content[source];
  }

  template <typename T>
  inline void BaseList<T>::move_part(size_type insert_position, size_type start, size_type length)
  {
    if (length == 0) {
      return;
    }
    assert(insert_position < m_capacity);
    assert(start < m_capacity);
    assert(insert_position + length <= m_capacity);
    assert(start + length <= m_capacity);

    if (insert_position < start) {
      for (size_type i = 0; i < length; ++i) {
        m_content[insert_position + i] = m_content[start + i];
      }
    } else {
      for (size_type i = length; i > 0;) {
        --i;
        m_content[insert_position + i] = m_content[start + i];
      }
    }
  }

  template <typename T>
  inline void BaseList<T>::swap(size_type index1, size_type index2)
  {
    if (index1 == index2) {
      return;
    }
    std::swap(m_content[index1], m_content[index2]);
  }

  template <typename T>
  inline void BaseList<T>::swap_parts(size_type start1, size_type start2, size_type length)
  {
    if (length == 0) {
      return;
    }
    assert((start1 <= start2 && start1 + length <= start2) || (start2 <= start1 && start2 + length <= start1));
    std::swap_ranges(m_content + start1, m_content + start1 + length, m_content + start2);
  }

  template <typename T>
  inline T* BaseList<T>::data()
  {
    return m_content;
  }

  template <typename T>
  inline const T* BaseList<T>::data() const
  {
    return m_content;
  }

  template <typename T>
  inline const T& BaseList<T>::at(size_type index) const
  {
    return m_content[index];
  }

  template <typename T>
  inline T& BaseList<T>::at(size_type index)
  {
    return m_content[index];
  }

  template <typename T>
  inline void BaseList<T>::reserve(size_type capacity)
  {
    if (capacity > m_capacity) {
      adjust_capacity(capacity);
    }
  }

  template <typename T>
  inline void BaseList<T>::prepare_size(size_type new_size)
  {
    // TODO overflow is not dealt with!
    if (new_size > m_capacity) {
      reorganize();
      adjust_capacity(new_size);
      // Size has to be adjusted afterwards in order to ensure that all old values are copied but not more than that.
    } else if (m_is_shrinkable && new_size < m_capacity / CAPACITY_DECREASE_FACTOR && new_size < m_size) {
      // Size has to be adjusted before because the later data is lost anyway and copying could cause a segfault because
      // there is not enough space in the new array. It is assumed that the content is deinitialized already.
      reorganize();
      m_size = new_size;
      adjust_capacity(new_size);
    }
    m_size = new_size;
  }

  template <typename T>
  void BaseList<T>::adjust_capacity(size_type new_capacity)
  {
    assert(new_capacity >= m_size);
    m_capacity = std::max(size_type(ArithmeticHelper::next_pow2(new_capacity)), m_min_capacity);
    m_content = static_cast<T*>(realloc(m_content, m_capacity * sizeof(T)));
  }

}
#endif // DATASTRUCTURES_BASELIST_HPP
