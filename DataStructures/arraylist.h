#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include "DataStructures_global.h"
#include <climits>
#include <algorithm>
#include <iterator>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <cassert>

#include "basetypes.h"
#include "arraylistiterator.h"
#include "arraylistconstiterator.h"

namespace DataStructures {

  template <typename T>
  std::ostream& operator<<(std::ostream& out, const ArrayList<T>& it);

  template <typename T>
  class DATASTRUCTURESSHARED_EXPORT ArrayList
  {
    friend std::ostream& operator<< <> (std::ostream& out, const ArrayList<T>& it);
  public:
    static const index_type DEFAULT_MIN_CAPACITY;
    typedef ArrayListIterator<T> iterator;
    typedef ArrayListConstIterator<T> const_iterator;
    typedef std::logic_error empty_list_error;
    typedef std::out_of_range range_error;
    explicit ArrayList(index_type initial_size = 0, const T& element = T(), index_type min_capacity = DEFAULT_MIN_CAPACITY);
    ArrayList(const ArrayList<T>& other);
    ArrayList(const ArrayList<T>::const_iterator& begin, const ArrayList<T>::const_iterator& end);
    virtual ~ArrayList();
    ArrayList<T>& operator=(const ArrayList<T>& other);
    ArrayList<T> operator+(const ArrayList<T>& other) const;
    ArrayList<T>& operator+=(const ArrayList<T>& other);
    ArrayList<T> operator*(index_type factor) const;
    ArrayList<T>& operator*=(index_type factor);
    bool operator==(const ArrayList<T> other) const;
    bool operator<(const ArrayList<T> other) const;
    index_type size() const;
    bool is_empty() const;
    const T& operator[](index_type i) const;
    T& operator[](index_type i);
    void push(const T& element);
    T pop();
    T top() const;
    void clear();
    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;
    index_type get_min_capacity() const;
    void set_min_capacity(index_type min_capacity);
    index_type get_capacity() const;
    void prepare_size(index_type new_size);
  private:
    static const index_type CAPACITY_DECREASE_FACTOR;
    T* m_content;
    index_type m_size;
    index_type m_capacity;
    index_type m_min_capacity;
    void add_content(const T * const content, index_type insert_position, index_type length);
    void init_capacity(index_type initial_capacity);
    void adjust_capacity(index_type new_capacity);
    void inline check_index(index_type index) const;
  };

  index_type next_higher(index_type k);

  index_type next_lower(index_type k);

  template <typename T>
  void copy(ArrayListIterator<T> target_begin,
            ArrayListIterator<T> target_end,
            ArrayListConstIterator<T> source_begin,
            ArrayListConstIterator<T> source_end);

  template <typename T>
  const index_type ArrayList<T>::DEFAULT_MIN_CAPACITY(16);

  template <typename T>
  const index_type ArrayList<T>::CAPACITY_DECREASE_FACTOR(4);

  template <typename T>
  std::ostream& operator<<(std::ostream& out, const ArrayList<T>& list)
  {
    out << "[";
    for (typename ArrayList<T>::const_iterator it = list.begin(); it != list.end(); it++) {
      out << *it;
      if (it + 1 != list.end()) {
        out << ", ";
      }
    }
    out << "]";
    return out;
  }

  template <typename T>
  ArrayList<T>::ArrayList(index_type initial_size, const T& element, index_type min_capacity):
    m_size(initial_size),
    m_min_capacity(min_capacity)
  {
    init_capacity(initial_size);
    for (index_type i = 0; i < size(); ++i) {
      m_content[i] = element;
    }
  }

  template <typename T>
  ArrayList<T>::ArrayList(const ArrayList<T>::const_iterator& begin, const ArrayList<T>::const_iterator& end):
    m_size(end - begin),
    m_min_capacity(DEFAULT_MIN_CAPACITY)
  {
    init_capacity(end - begin);
    index_type i = 0;
    for (ArrayList<T>::const_iterator it = begin; it < end; ++it) {
      m_content[i++] = *it;
    }
  }

  template <typename T>
  ArrayList<T>::ArrayList(const ArrayList<T>& other):
    m_size(other.m_size),
    m_min_capacity(other.m_min_capacity)
  {
    init_capacity(other.m_size);
    add_content(other.m_content, 0, other.m_size);
  }

  template <typename T>
  ArrayList<T>::~ArrayList()
  {
    delete[] m_content;
  }

  template <typename T>
  ArrayList<T>& ArrayList<T>::operator=(const ArrayList<T>& other)
  {
    if (this == &other) {
      return *this;
    }
    prepare_size(other.m_size);
    add_content(other.m_content, 0, other.m_size);
    return *this;
  }

  template <typename T>
  ArrayList<T> ArrayList<T>::operator+(const ArrayList<T>& other) const
  {
    ArrayList<T> result(m_size + other.m_size);
    result.add_content(m_content, 0, m_size);
    result.add_content(other.m_content, m_size, other.m_size);
    return result;
  }

  template <typename T>
  ArrayList<T>& ArrayList<T>::operator+=(const ArrayList<T>& other)
  {
    index_type old_size = m_size;
    prepare_size(m_size + other.m_size);
    add_content(other.m_content, old_size, other.m_size);
    return *this;
  }

  template <typename T>
  ArrayList<T> ArrayList<T>::operator*(index_type factor) const
  {
    ArrayList<T> result (m_size * factor);
    for (index_type i = 0; i < factor; ++i) {
      result.add_content(m_content, i * m_size, m_size);
    }
    return result;
  }

  template <typename T>
  ArrayList<T>& ArrayList<T>::operator*=(index_type factor)
  {
    index_type old_size = m_size;
    prepare_size(m_size * factor);
    for (index_type i = 1; i < factor; ++i) {
      add_content(m_content, i * old_size, old_size);
    }
    return *this;
  }

  template <typename T>
  bool ArrayList<T>::operator==(const ArrayList<T> other) const
  {
    if (size() != other.size()) {
      return false;
    }
    for (index_type i = 0; i < size(); ++i) {
      if (m_content[i] != other[i]) {
        return false;
      }
    }
    return true;
  }

  template <typename T>
  index_type ArrayList<T>::size() const
  {
    return m_size;
  }

  template <typename T>
  bool ArrayList<T>::is_empty() const
  {
    return m_size == 0;
  }

  template <typename T>
  typename ArrayList<T>::iterator ArrayList<T>::begin()
  {
    return iterator(this, 0);
  }

  template <typename T>
  typename ArrayList<T>::const_iterator ArrayList<T>::begin() const
  {
    return const_iterator(this, 0);
  }

  template <typename T>
  typename ArrayList<T>::iterator ArrayList<T>::end()
  {
    return iterator(this, m_size);
  }

  template <typename T>
  typename ArrayList<T>::const_iterator ArrayList<T>::end() const
  {
    return const_iterator(this, m_size);
  }

  template <typename T>
  const T& ArrayList<T>::operator[](index_type i) const
  {
    check_index(i);
    return m_content[i];
  }

  template <typename T>
  T& ArrayList<T>::operator[](index_type i)
  {
    check_index(i);
    return m_content[i];
  }

  template <typename T>
  void ArrayList<T>::push(const T& element)
  {
    prepare_size(m_size + 1);
    m_content[m_size - 1] = element;
  }

  template <typename T>
  T ArrayList<T>::pop()
  {
    if (is_empty()) {
      throw empty_list_error("Cannot pop from an empty ArrayList.");
    }
    T element = m_content[m_size - 1];
    prepare_size(m_size - 1);
    return element;
  }

  template <typename T>
  T ArrayList<T>::top() const
  {
    if (is_empty()) {
      throw empty_list_error("Cannot take the top from an empty ArrayList.");
    }
    return m_content[m_size - 1];
  }

  template <typename T>
  void ArrayList<T>::clear()
  {
    prepare_size(0);
  }

  template <typename T>
  index_type ArrayList<T>::get_min_capacity() const
  {
    return m_min_capacity;
  }

  template <typename T>
  void ArrayList<T>::set_min_capacity(index_type min_capacity)
  {
    m_min_capacity = min_capacity;
    if (m_capacity < m_min_capacity) {
      adjust_capacity(m_min_capacity);
    }
  }

  template <typename T>
  index_type ArrayList<T>::get_capacity() const
  {
    return m_capacity;
  }

  template <typename T>
  void ArrayList<T>::add_content(const T * const content, index_type insert_position, index_type length)
  {
    for (index_type i = 0; i < length; i++) {
      m_content[insert_position + i] = content[i];
    }
  }

  template <typename T>
  void ArrayList<T>::prepare_size(index_type new_size)
  {
    // TODO overflow is not dealt with!
    if (new_size > m_capacity) {
      adjust_capacity(next_higher(new_size));
      // Size has to be adjusted afterwards in order to ensure that all old values are copied but not more than that.
    } else if (new_size < m_capacity / CAPACITY_DECREASE_FACTOR && new_size < m_size) {
      // Size has to be adjusted before because the later data is lost anyway and copying could cause a segfault because
      // there is not enough space in the new array.
      m_size = new_size;
      adjust_capacity(new_size);
    }
    m_size = new_size;
  }

  template <typename T>
  void ArrayList<T>::init_capacity(index_type initial_capacity)
  {
    m_capacity = std::max(next_higher(initial_capacity), m_min_capacity);
    m_content = new T[m_capacity];
  }

  template <typename T>
  void ArrayList<T>::adjust_capacity(index_type new_capacity)
  {
    new_capacity = std::max(next_higher(new_capacity), m_min_capacity);
    assert(new_capacity >= m_size);
    if (m_capacity != new_capacity) {
      m_capacity = new_capacity;
      T* old_content = m_content;
      m_content = new T[m_capacity];
      add_content(old_content, 0, m_size);
      delete[] old_content;
    }
  }

  template <typename T>
  void inline ArrayList<T>::check_index(index_type index) const
  {
    if (index >= m_size) {
      std::ostringstream oss;
      oss << "Invalid index " << index << " for array list of size " << m_size << ".";
      throw range_error(oss.str());
    }
  }

  template <typename T>
  void copy(ArrayListIterator<T> target_begin,
            ArrayListIterator<T> target_end,
            ArrayListConstIterator<T> source_begin,
            ArrayListConstIterator<T> source_end)
  {
    for (; target_begin < target_end && source_begin < source_end; ++target_begin, ++source_begin)
    {
      *target_begin = *source_begin;
    }
  }

}
#endif // ARRAYLIST_H
