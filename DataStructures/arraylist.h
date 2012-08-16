#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include "baselist.h"
#include "listiterator.h"
#include "listconstiterator.h"
#include <cassert>

namespace DataStructures {

  template <typename T>
  inline std::ostream& operator<<(std::ostream& out, const ArrayList<T>& it);

  template <typename T>
  class DATASTRUCTURESSHARED_EXPORT ArrayList : public BaseList<T>
  {
    friend std::ostream& operator<< <> (std::ostream& out, const ArrayList<T>& it);
  public:
    typedef ListIterator<T, ArrayList<T> > iterator;

    typedef ListConstIterator<T, ArrayList<T> > const_iterator;

    typedef typename BaseList<T>::empty_list_error empty_list_error;

    inline explicit ArrayList(index_type initial_size = 0, const T& element = T());

    inline ArrayList(const ArrayList<T>& other);
/*
    template <typename Begin, typename End>
    ArrayList(const Begin& begin, const End& end);*/

    template <typename BeginIterator, typename EndIterator>
    void push_all(const BeginIterator& begin, const EndIterator& end);

    inline ArrayList<T> operator+(const ArrayList<T>& other) const;

    inline ArrayList<T>& operator+=(const ArrayList<T>& other);

    inline ArrayList<T> operator*(index_type factor) const;

    inline ArrayList<T>& operator*=(index_type factor);

    inline bool operator==(const ArrayList<T> other) const;

    inline bool operator!=(const ArrayList<T> other) const { return !operator==(other); }

    inline const T& operator[](index_type i) const { check_index(i); return BaseList<T>::m_content[i]; }

    inline T& operator[](index_type i) { check_index(i); return BaseList<T>::m_content[i]; }

    inline void push(const T& element);

    inline T pop();

    inline const T& front() const { check_empty(); return BaseList<T>::m_content[0]; }

    inline T& front() { check_empty(); return BaseList<T>::m_content[0]; }

    inline const T& back() const { check_empty(); return BaseList<T>::m_content[BaseList<T>::m_size - 1]; }

    inline T& back() { check_empty(); return BaseList<T>::m_content[BaseList<T>::m_size - 1]; }

    inline iterator begin() { return iterator(this, 0); }

    inline const_iterator begin() const { return const_iterator(this, 0); }

    inline iterator end() { return iterator(this, BaseList<T>::m_size); }

    inline const_iterator end() const { return const_iterator(this, BaseList<T>::m_size); }

  };

  template <typename T>
  inline std::ostream& operator<<(std::ostream& out, const ArrayList<T>& list)
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
  inline ArrayList<T>::ArrayList(index_type initial_size, const T& element):
    BaseList<T>(initial_size, element)
  {
  }

/*
  template <typename T>
  template <typename Begin, typename End>
  ArrayList<T>::ArrayList(const Begin& begin, const End& end):
    m_size(end - begin),
    m_min_capacity(DEFAULT_MIN_CAPACITY)
  {
    init_capacity(end - begin);
    index_type i = 0;
    for (Begin it = begin; it < end; ++it) {
      m_content[i++] = *it;
    }
  }
*/

  template <typename T>
  template <typename BeginIterator, typename EndIterator>
  inline void ArrayList<T>::push_all(const BeginIterator& begin, const EndIterator& end)
  {
    if (end <= begin) {
      return;
    }
    index_type i = BaseList<T>::m_size;
    BaseList<T>::prepare_size(BaseList<T>::m_size + (end - begin));
    for (BeginIterator it = begin; it != end; ++it) {
      BaseList<T>::m_content[i++] = *it;
    }
  }

  template <typename T>
  inline ArrayList<T>::ArrayList(const ArrayList<T>& other):
    BaseList<T>(other)
  {
  }

  template <typename T>
  inline ArrayList<T> ArrayList<T>::operator+(const ArrayList<T>& other) const
  {
    ArrayList<T> result(BaseList<T>::m_size + other.m_size);
    result.add_content(BaseList<T>::m_content, 0, BaseList<T>::m_size);
    result.add_content(other.m_content, BaseList<T>::m_size, other.m_size);
    return result;
  }

  template <typename T>
  inline ArrayList<T>& ArrayList<T>::operator+=(const ArrayList<T>& other)
  {
    index_type old_size = BaseList<T>::m_size;
    BaseList<T>::prepare_size(BaseList<T>::m_size + other.m_size);
    BaseList<T>::add_content(other.m_content, old_size, other.m_size);
    return *this;
  }

  template <typename T>
  inline ArrayList<T> ArrayList<T>::operator*(index_type factor) const
  {
    ArrayList<T> result (BaseList<T>::m_size * factor);
    for (index_type i = 0; i < factor; ++i) {
      result.add_content(BaseList<T>::m_content, i * BaseList<T>::m_size, BaseList<T>::m_size);
    }
    return result;
  }

  template <typename T>
  inline ArrayList<T>& ArrayList<T>::operator*=(index_type factor)
  {
    index_type old_size = BaseList<T>::m_size;
    BaseList<T>::prepare_size(BaseList<T>::m_size * factor);
    for (index_type i = 1; i < factor; ++i) {
      BaseList<T>::add_content(BaseList<T>::m_content, i * old_size, old_size);
    }
    return *this;
  }

  template <typename T>
  inline bool ArrayList<T>::operator==(const ArrayList<T> other) const
  {
    if (BaseList<T>::size() != other.size()) {
      return false;
    }
    for (index_type i = 0; i < BaseList<T>::m_size; ++i) {
      if (BaseList<T>::m_content[i] != other[i]) {
        return false;
      }
    }
    return true;
  }

  template <typename T>
  inline void ArrayList<T>::push(const T& element)
  {
    BaseList<T>::prepare_size(BaseList<T>::m_size + 1);
    BaseList<T>::m_content[BaseList<T>::m_size - 1] = element;
  }

  template <typename T>
  inline T ArrayList<T>::pop()
  {
    check_empty();
    T element = BaseList<T>::m_content[BaseList<T>::m_size - 1];
    BaseList<T>::destroy(BaseList<T>::m_size - 1);
    BaseList<T>::prepare_size(BaseList<T>::m_size - 1);
    return element;
  }

}

#endif // ARRAYLIST_H
