#ifndef BASELIST_H
#define BASELIST_H

#include "DataStructures_global.h"
#include <climits>
#include <algorithm>
#include <iterator>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <cassert>

#include "basetypes.h"
#ifndef NDEBUG
#define check_index(index) if (index >= BaseList<T>::m_size) { std::ostringstream oss; oss << "Invalid index " << index << " for array list of size " << BaseList<T>::m_size << "."; throw typename BaseList<T>::range_error(oss.str()); }
#else
#define check_index(index)
#endif


namespace DataStructures {

  template <typename T>
  class BaseList
  {
  public:
    static const index_type DEFAULT_MIN_CAPACITY;

    typedef std::logic_error empty_list_error;

    typedef std::out_of_range range_error;

    explicit BaseList(index_type initial_size, const T& element);

    BaseList(const BaseList<T>& other);

    virtual BaseList<T>& operator=(const BaseList<T>& other);

/*
    template <typename BeginIterator, typename EndIterator>
    BaseList(const BeginIterator& begin, const EndIterator& end);*/

    template <typename BeginIterator, typename EndIterator>
    void push_all(const BeginIterator& begin, const EndIterator& end);

    virtual ~BaseList();

    inline index_type size() const { return m_size; }

    inline bool is_empty() const { return m_size == 0; }

    virtual const T& operator[](index_type i) const = 0;

    virtual T& operator[](index_type i) = 0;

    inline void clear() { prepare_size(0); }

    inline index_type get_min_capacity() const { return m_min_capacity; }

    inline void set_min_capacity(index_type min_capacity);

    inline index_type get_capacity() const { return m_capacity; }

    inline void set_shrinkable(bool is_shrinkable) { m_is_shrinkable = is_shrinkable; }

    inline bool is_shrinkable() const { return m_is_shrinkable; }

    void prepare_size(index_type new_size);

  protected:
    static const index_type CAPACITY_DECREASE_FACTOR;

    T* m_content;

    index_type m_size;

    index_type m_capacity;

    index_type m_min_capacity;

    bool m_is_shrinkable;

    virtual void copy_old_content(const T* old_content);

    inline void add_content(const T * content, index_type insert_position, index_type length);

    inline void init_capacity(index_type initial_capacity);

    inline void adjust_capacity(index_type new_capacity);

  };

  index_type next_higher(index_type k);

  index_type next_lower(index_type k);

  template <typename TargetBegin, typename TargetEnd, typename SourceBegin, typename SourceEnd>
  void copy(const TargetBegin& target_begin,
            const TargetEnd& target_end,
            const SourceBegin& source_begin,
            const SourceEnd& source_end);

  template <typename T>
  const index_type BaseList<T>::DEFAULT_MIN_CAPACITY(16);

  template <typename T>
  const index_type BaseList<T>::CAPACITY_DECREASE_FACTOR(4);

  template <typename T>
  BaseList<T>::BaseList(index_type initial_size, const T& element):
    m_size (initial_size),
    m_min_capacity (DEFAULT_MIN_CAPACITY),
    m_is_shrinkable (false)
  {
    init_capacity(initial_size);
    for (index_type i = 0; i < size(); ++i) {
      m_content[i] = element;
    }
  }
/*
  template <typename T>
  template <typename BeginIterator, typename EndIterator>
  BaseList<T>::BaseList(const BeginIterator& begin, const EndIterator& end):
    m_size(end - begin),
    m_min_capacity(DEFAULT_MIN_CAPACITY)
  {
    init_capacity(end - begin);
    index_type i = 0;
    for (BeginIterator it = begin; it < end; ++it) {
      m_content[i++] = *it;
    }
  }
*/
  template <typename T>
  template <typename BeginIterator, typename EndIterator>
  void BaseList<T>::push_all(const BeginIterator& begin, const EndIterator& end)
  {
    index_type i = m_size;
    prepare_size(m_size + (end - begin));
    for (BeginIterator it = begin; it != end; ++it) {
      m_content[i++] = *it;
    }
  }

  template <typename T>
  BaseList<T>::BaseList(const BaseList<T>& other):
    m_size(other.m_size),
    m_min_capacity(other.m_min_capacity)
  {
    init_capacity(other.m_size);
    add_content(other.m_content, 0, other.m_size);
  }

  template <typename T>
  BaseList<T>::~BaseList()
  {
    delete[] m_content;
  }

  template <typename T>
  BaseList<T>& BaseList<T>::operator=(const BaseList<T>& other)
  {
    if (this == &other) {
      return *this;
    }
    prepare_size(other.m_size);
    add_content(other.m_content, 0, other.m_size);
    return *this;
  }

  template <typename T>
  const T& BaseList<T>::operator[](index_type i) const
  {
    check_index(i);
    return m_content[i];
  }

  template <typename T>
  T& BaseList<T>::operator[](index_type i)
  {
    check_index(i);
    return m_content[i];
  }

  template <typename T>
  void BaseList<T>::set_min_capacity(index_type min_capacity)
  {
    m_min_capacity = min_capacity;
    if (m_capacity < m_min_capacity) {
      adjust_capacity(m_min_capacity);
    }
  }

  template <typename T>
  inline void BaseList<T>::add_content(const T * content, index_type insert_position, index_type length)
  {
    for (index_type i = 0; i < length; i++) {
      m_content[insert_position + i] = content[i];
    }
  }

  template <typename T>
  inline void BaseList<T>::prepare_size(index_type new_size)
  {
    // TODO overflow is not dealt with!
    if (new_size > m_capacity) {
      adjust_capacity(next_higher(new_size));
      // Size has to be adjusted afterwards in order to ensure that all old values are copied but not more than that.
    } else if (m_is_shrinkable && new_size < m_capacity / CAPACITY_DECREASE_FACTOR && new_size < m_size) {
      // Size has to be adjusted before because the later data is lost anyway and copying could cause a segfault because
      // there is not enough space in the new array.
      m_size = new_size;
      adjust_capacity(new_size);
    }
    m_size = new_size;
  }

  template <typename T>
  inline void BaseList<T>::init_capacity(index_type initial_capacity)
  {
    m_capacity = std::max(next_higher(initial_capacity), m_min_capacity);
    m_content = new T[m_capacity];
  }

  template <typename T>
  void BaseList<T>::adjust_capacity(index_type new_capacity)
  {
    new_capacity = std::max(next_higher(new_capacity), m_min_capacity);
    assert(new_capacity >= m_size);
    if (m_capacity != new_capacity) {
      m_capacity = new_capacity;
      T* old_content = m_content;
      m_content = new T[m_capacity];
      copy_old_content(old_content);
      delete[] old_content;
    }
  }

  template <typename T>
  void BaseList<T>::copy_old_content(const T* old_content)
  {
    add_content(old_content, 0, m_size);
  }

  template <typename TargetBegin, typename TargetEnd, typename SourceBegin, typename SourceEnd>
  void copy(const TargetBegin& target_begin,
            const TargetEnd& target_end,
            const SourceBegin& source_begin,
            const SourceEnd& source_end)
  {
    TargetBegin target_it (target_begin);
    SourceBegin source_it (source_begin);
    for (; target_it < target_end && source_it < source_end; ++target_it, ++source_it)
    {
      *target_it = *source_it;
    }
  }

}
#endif // BASELIST_H
