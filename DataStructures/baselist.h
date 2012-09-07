#ifndef DATASTRUCTURES_BASELIST_H
#define DATASTRUCTURES_BASELIST_H

#include "arithmetichelper.h"
#include <cstddef>
#include <climits>
#include <algorithm>
#include <iterator>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <cassert>
#include <cstring>

#ifndef NDEBUG
#define list_check_index(index) assert(index < BaseList<T>::size()); if (index >= BaseList<T>::size()) { std::ostringstream oss; oss << __FILE__ << "(" << __LINE__ << "): Invalid index " << index << " for list of size " << BaseList<T>::size() << "."; throw typename BaseList<T>::range_error(oss.str()); }
#else
#define list_check_index(index)
#endif
#ifndef NDEBUG
#define check_empty() if (BaseList<T>::is_empty()) { std::ostringstream oss; oss << __FILE__ << "(" << __LINE__ << "): Cannot take the top of an empty list."; throw typename BaseList<T>::empty_list_error(oss.str()); }
#else
#define check_empty()
#endif

namespace DataStructures {

  template <typename T>
  class BaseList
  {
  public:
    typedef size_t size_type;

    typedef ptrdiff_t difference_type;

    static const size_type DEFAULT_MIN_CAPACITY;

    typedef std::logic_error empty_list_error;

    typedef std::out_of_range range_error;

    typedef T value_type;

    typedef T& reference_type;

    typedef T* pointer_type;

    inline BaseList();

    explicit inline BaseList(size_type initial_size, const T& element = T());

    inline BaseList(const BaseList<T>& other);

    // inline BaseList(BaseList<T>&& other);

    inline virtual BaseList<T>& operator=(const BaseList<T>& other);

    // inline virtual BaseList<T>& operator=(BaseList<T>&& other);

    inline virtual void reorganize() {}

    template <typename Iterator>
    BaseList(const Iterator& begin, const Iterator& end);

    inline virtual ~BaseList();

    inline size_type size() const { return m_size; }

    inline bool is_empty() const { return m_size == 0; }

    inline virtual void clear() { destroy_part(0, m_size); prepare_size(0); }

    inline size_type min_capacity() const { return m_min_capacity; }

    inline void set_min_capacity(size_type min_capacity);

    inline size_type capacity() const { return m_capacity; }

    inline void set_shrinkable(bool is_shrinkable) { m_is_shrinkable = is_shrinkable; }

    inline bool is_shrinkable() const { return m_is_shrinkable; }

  private:
    static const size_type CAPACITY_DECREASE_FACTOR;

    T* m_content;

    size_type m_size;

    size_type m_capacity;

    size_type m_min_capacity;

    bool m_is_shrinkable;

  protected:
    inline void prepare_size(size_type new_size);

    inline T* data() { return m_content; }

    inline const T* data() const { return m_content; }

    inline const T& at(size_type index) const { return m_content[index]; }

    inline T& at(size_type index) { return m_content[index]; }

    inline void create(size_type index, const T& element) { new(m_content + index) T(element); }

    inline void replace(size_type index, const T& element) { m_content[index] = element; }

    inline void destroy(size_type index) { m_content[index].~T(); }

    inline void destroy_part(size_type begin, size_type length) { for (size_type i = begin; i < begin + length; ++i) destroy(i); }

    inline void add_content(const T * data, size_type insert_position, size_type length);

    inline void move(size_type target, size_type source);

    inline void move_part(size_type insert_position, size_type start, size_type length);

    inline void swap(size_type index1, size_type index2);

    inline void swap_parts(size_type start1, size_type start2, size_type length);

    inline void init_capacity(size_type initial_capacity);

    inline void adjust_capacity(size_type new_capacity);

  };

  template <typename TargetIterator, typename SourceIterator>
  void copy(const TargetIterator& target_begin,
            const TargetIterator& target_end,
            const SourceIterator& source_begin,
            const SourceIterator& source_end);

  template <typename T>
  const typename BaseList<T>::size_type BaseList<T>::DEFAULT_MIN_CAPACITY(16);

  template <typename T>
  const typename BaseList<T>::size_type BaseList<T>::CAPACITY_DECREASE_FACTOR(4);

  template <typename T>
  BaseList<T>::BaseList():
    m_content (NULL),
    m_size (0),
    m_min_capacity (DEFAULT_MIN_CAPACITY),
    m_is_shrinkable (false)
  {
    adjust_capacity(0);
  }

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
  template <typename Iterator>
  BaseList<T>::BaseList(const Iterator& begin, const Iterator& end):
    m_content (NULL),
    m_size (end - begin),
    m_min_capacity (DEFAULT_MIN_CAPACITY),
    m_is_shrinkable (false)
  {
    adjust_capacity (end - begin);
    size_type i = 0;
    for (Iterator it = begin; it < end; ++it, ++i) {
      create(i, *it);
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
    assert(m_min_capacity > 0);
  }

  template <typename T>
  BaseList<T>::~BaseList()
  {
    clear();
    free(m_content);
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
    // TODO efficiency
    clear();
    m_min_capacity = other.m_min_capacity;
    prepare_size(other.m_size);
    add_content(other.m_content, 0, other.m_size);
    return *this;
  }

  template <typename T>
  inline void BaseList<T>::set_min_capacity(size_type min_capacity)
  {
    m_min_capacity = min_capacity;
    if (m_capacity < m_min_capacity) {
      adjust_capacity(m_min_capacity);
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
    memmove(m_content + target, m_content + source, sizeof(T));
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
    memmove(m_content + insert_position, m_content + start, length * sizeof(T));
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

  template <typename TargetIterator, typename SourceIterator>
  void copy(const TargetIterator& target_begin,
            const TargetIterator& target_end,
            const SourceIterator& source_begin,
            const SourceIterator& source_end)
  {
    TargetIterator target_it (target_begin);
    SourceIterator source_it (source_begin);
    for (; target_it < target_end && source_it < source_end; ++target_it, ++source_it)
    {
      *target_it = *source_it;
    }
  }

}
#endif // DATASTRUCTURES_BASELIST_H
