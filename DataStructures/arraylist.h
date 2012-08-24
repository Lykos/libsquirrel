#ifndef DATASTRUCTURES_ARRAYLIST_H
#define DATASTRUCTURES_ARRAYLIST_H

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

    inline ArrayList();

    inline explicit ArrayList(index_type initial_size, const T& element = T());

    /*template <typename Iterator>
    ArrayList(const Iterator& begin, const Iterator& end);*/

    template <typename Iterator>
    void push_all(const Iterator& begin, const Iterator& end);

    inline ArrayList<T> operator+(const ArrayList<T>& other) const;

    inline ArrayList<T>& operator+=(const ArrayList<T>& other);

    inline ArrayList<T> operator*(index_type factor) const;

    inline ArrayList<T>& operator*=(index_type factor);

    inline bool operator==(const ArrayList<T>& other) const;

    inline bool operator!=(const ArrayList<T>& other) const { return !operator==(other); }

    inline const T& operator[](index_type i) const { list_check_index(i); return BaseList<T>::at(i); }

    inline T& operator[](index_type i) { list_check_index(i); return BaseList<T>::at(i); }

    inline void push(const T& element);

    inline T pop();

    inline bool remove(const T& element);

    inline index_type remove_all(const T& element);

    inline void remove_position(index_type position);

    inline void remove_range(index_type start, index_type end);

    inline const T& front() const { check_empty(); return BaseList<T>::at(0); }

    inline T& front() { check_empty(); return BaseList<T>::at(0); }

    inline const T& back() const { check_empty(); return BaseList<T>::at(BaseList<T>::size() - 1); }

    inline T& back() { check_empty(); return BaseList<T>::at(BaseList<T>::size() - 1); }

    inline iterator begin() { return iterator(this, 0); }

    inline const_iterator begin() const { return const_iterator(this, 0); }

    inline iterator end() { return iterator(this, BaseList<T>::size()); }

    inline const_iterator end() const { return const_iterator(this, BaseList<T>::size()); }

  };

  template <typename T>
  inline std::ostream& operator<<(std::ostream& out, const ArrayList<T>& list)
  {
    out << "ArrayList[";
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
  inline ArrayList<T>::ArrayList():
    BaseList<T>()
  {
  }

  template <typename T>
  inline ArrayList<T>::ArrayList(index_type initial_size, const T& element):
    BaseList<T>(initial_size, element)
  {
  }

  /*template <typename T>
  template <typename Iterator>
  ArrayList<T>::ArrayList(const Iterator& begin, const Iterator& end)
  {
    push_all(begin, end);
  }*/

  template <typename T>
  template <typename Iterator>
  inline void ArrayList<T>::push_all(const Iterator& begin, const Iterator& end)
  {
    if (end <= begin) {
      return;
    }
    index_type i = BaseList<T>::size();
    BaseList<T>::prepare_size(BaseList<T>::size() + (end - begin));
    for (Iterator it = begin; it != end; ++it, ++i) {
      BaseList<T>::create(i, *it);
    }
  }

  template <typename T>
  inline ArrayList<T> ArrayList<T>::operator+(const ArrayList<T>& other) const
  {
    ArrayList<T> result(BaseList<T>::size() + other.size());
    result.add_content(BaseList<T>::content(), 0, BaseList<T>::size());
    result.add_content(other.content(), BaseList<T>::size(), other.size());
    return result;
  }

  template <typename T>
  inline ArrayList<T>& ArrayList<T>::operator+=(const ArrayList<T>& other)
  {
    index_type old_size = BaseList<T>::size();
    BaseList<T>::prepare_size(BaseList<T>::size() + other.size());
    BaseList<T>::add_content(other.content(), old_size, other.size());
    return *this;
  }

  template <typename T>
  inline ArrayList<T> ArrayList<T>::operator*(index_type factor) const
  {
    ArrayList<T> result (BaseList<T>::size() * factor);
    for (index_type i = 0; i < factor; ++i) {
      result.add_content(BaseList<T>::content(), i * BaseList<T>::size(), BaseList<T>::size());
    }
    return result;
  }

  template <typename T>
  inline ArrayList<T>& ArrayList<T>::operator*=(index_type factor)
  {
    index_type old_size = BaseList<T>::size();
    BaseList<T>::prepare_size(BaseList<T>::size() * factor);
    for (index_type i = 1; i < factor; ++i) {
      BaseList<T>::add_content(BaseList<T>::content(), i * old_size, old_size);
    }
    return *this;
  }

  template <typename T>
  inline bool ArrayList<T>::operator==(const ArrayList<T>& other) const
  {
    if (this == &other) {
      return true;
    }
    if (BaseList<T>::size() != other.size()) {
      return false;
    }
    for (index_type i = 0; i < BaseList<T>::size(); ++i) {
      if (BaseList<T>::at(i) != other.at(i)) {
        return false;
      }
    }
    return true;
  }

  template <typename T>
  inline void ArrayList<T>::push(const T& element)
  {
    BaseList<T>::prepare_size(BaseList<T>::size() + 1);
    BaseList<T>::create(BaseList<T>::size() - 1, element);
  }

  template <typename T>
  inline T ArrayList<T>::pop()
  {
    check_empty();
    T element = BaseList<T>::at(BaseList<T>::size() - 1);
    BaseList<T>::destroy(BaseList<T>::size() - 1);
    BaseList<T>::prepare_size(BaseList<T>::size() - 1);
    return element;
  }

  template <typename T>
  inline bool ArrayList<T>::remove(const T& element)
  {
    for (index_type i = 0; i < BaseList<T>::size(); ++i) {
      if (BaseList<T>::at(i) == element) {
        BaseList<T>::move_part(i, i + 1, BaseList<T>::size() - (i + 1));
        BaseList<T>::destroy(BaseList<T>::size() - 1);
        BaseList<T>::prepare_size(BaseList<T>::size() - 1);
        return true;
      }
    }
    return false;
  }

  template <typename T>
  inline index_type ArrayList<T>::remove_all(const T& element)
  {
    index_type removed = 0;
    for (index_type i = 0; i < BaseList<T>::size(); ++i) {
      while (i < BaseList<T>::size() && BaseList<T>::at(i) == element) {
        ++removed;
        ++i;
      }
      index_type good_length = 0;
      while (i + good_length < BaseList<T>::size() && BaseList<T>::at(i + good_length) != element) {
        ++good_length;
      }
      BaseList<T>::move_part(i, good_length);
      i += good_length;
    }
    destroy_part(BaseList<T>::size() - removed, removed);
    BaseList<T>::prepare_size(BaseList<T>::size() - removed);
    return false;
  }

  template <typename T>
  inline void ArrayList<T>::remove_position(index_type position)
  {
    list_check_index(position);
    BaseList<T>::move_part(position, position + 1, BaseList<T>::size() - (position + 1));
    destroy(BaseList<T>::size() - 1);
    BaseList<T>::prepare_size(BaseList<T>::size() - 1);
  }

  template <typename T>
  inline void ArrayList<T>::remove_range(index_type start, index_type end)
  {
    if (start >= end) {
      return;
    }
    list_check_index(start);
    end = std::min(end, BaseList<T>::size());
    index_type length = end - start;
    index_type tail_length = std::min(length, BaseList<T>::size() - end);
    BaseList<T>::move_part(start, end, tail_length);
    BaseList<T>::destroy_part(BaseList<T>::size() - length, length);
    BaseList<T>::prepare_size(BaseList<T>::size() - length);
  }

}

#endif // DATASTRUCTURES_ARRAYLIST_H
