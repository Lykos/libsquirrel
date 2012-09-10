#ifndef DATASTRUCTURES_ARRAYLIST_HPP
#define DATASTRUCTURES_ARRAYLIST_HPP

#include "baselist.h"
#include "arraylist.h"
#include "listiterator.h"

namespace DataStructures {

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
  inline ArrayList<T>::ArrayList()
  {}

  template <typename T>
  inline ArrayList<T>::ArrayList(std::initializer_list<T> list):
    ArrayList<T>(list.begin(), list.end())
  {}

  template <typename T>
  inline ArrayList<T>::ArrayList(size_type initial_size, const T& element):
    BaseList<T>(initial_size, element)
  {}

  template <typename T>
  template <typename InputIterator>
  ArrayList<T>::ArrayList(InputIterator begin, InputIterator end)
  {
    insert(0, begin, end);
  }

  template <typename T>
  inline int_fast8_t ArrayList<T>::compare_to(const ArrayList<T>& other) const
  {
    if (this == &other) {
      return 0;
    }
    for (size_type i = 0; i < BaseList<T>::size() && i < other.size(); ++i) {
      if (BaseList<T>::at(i) < other.at(i)) {
        return -1;
      } else if (other.at(i) < BaseList<T>::at(i)) {
        return 1;
      }
    }
    if (BaseList<T>::size() < other.size()) {
      return -1;
    } else if (other.size() < BaseList<T>::size()) {
      return 1;
    }
    return 0;
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
    return compare_to(other) == 0;
  }

  template <typename T>
  inline bool ArrayList<T>::operator!=(const ArrayList<T>& other) const
  {
    return !operator==(other);
  }

  template <typename T>
  inline bool ArrayList<T>::operator<(const ArrayList<T>& other) const
  {
    return compare_to(other) == -1;
  }

  template <typename T>
  inline bool ArrayList<T>::operator<=(const ArrayList<T>& other) const
  {
    return compare_to(other) != 1;
  }

  template <typename T>
  inline bool ArrayList<T>::operator>(const ArrayList<T>& other) const
  {
    return compare_to(other) == 1;
  }

  template <typename T>
  inline bool ArrayList<T>::operator>=(const ArrayList<T>& other) const
  {
    return compare_to(other) != -1;
  }

  template <typename T>
  template <typename InputIterator>
  inline void ArrayList<T>::assign(InputIterator begin, InputIterator end)
  {
    clear();
    insert(0, begin, end);
  }

  template <typename T>
  inline void ArrayList<T>::assign(size_type number, const T& element)
  {
    clear();
    insert(0, number, element);
  }

  template <typename T>
  inline typename ArrayList<T>::iterator ArrayList<T>::erase(iterator position)
  {
    return erase(position - begin());
  }

  template <typename T>
  inline typename ArrayList<T>::iterator ArrayList<T>::erase(iterator start, iterator end)
  {
    return erase(start - begin(), end - begin());
  }

  template <typename T>
  inline typename ArrayList<T>::iterator ArrayList<T>::erase(size_type index)
  {
    return erase(index, index + 1);
  }

  template <typename T>
  inline typename ArrayList<T>::iterator ArrayList<T>::erase(size_type start, size_type end)
  {
    PREC_INDEX_INSERT_LIST(start);
    PREC_INDEX_INSERT_LIST(end);
    PREC(InvalidRange, start <= end);
    BaseList<T>::destroy_part(start, end - start);
    BaseList<T>::move_part(start, end, BaseList<T>::size() - end);
    BaseList<T>::prepare_size(BaseList<T>::size() - (end - start));
    return iterator(this, start);
  }

  template <typename T>
  inline typename ArrayList<T>::iterator ArrayList<T>::insert(size_type index, const T& element)
  {
    insert(index, size_type(1), element);
    return iterator(this, index);
  }

  template <typename T>
  inline void ArrayList<T>::insert(size_type index, size_type number, const T& element)
  {
    PREC_INDEX_INSERT_LIST(index);
    size_type old_size = BaseList<T>::size();
    BaseList<T>::prepare_size(old_size + number);
    BaseList<T>::move_part(index + number, index, old_size - index);
    for (size_type i = index; i < index + number; ++i) {
      BaseList<T>::create(i, element);
    }
  }

  template <typename T>
  template <typename InputIterator>
  inline void ArrayList<T>::insert(size_type index, InputIterator start, InputIterator end)
  {
    PREC_INDEX_INSERT_LIST(index);
    size_type old_size = BaseList<T>::size();
    BaseList<T>::prepare_size(old_size + (end - start));
    BaseList<T>::move_part(index + (end - start), index, old_size - index);
    for (; start != end; ++start, ++index) {
      BaseList<T>::create(index, *start);
    }
  }

  template <typename T>
  inline typename ArrayList<T>::iterator ArrayList<T>::insert(iterator position, const T& element)
  {
    return insert(position - begin(), element);
  }

  template <typename T>
  inline void ArrayList<T>::insert(iterator position, size_type number, const T& element)
  {
    insert(position - begin(), number, element);
  }

  template <typename T>
  template <typename InputIterator>
  inline void ArrayList<T>::insert(iterator position, InputIterator start, InputIterator end)
  {
    insert(position - begin(), start, end);
  }

  template <typename T>
  inline void ArrayList<T>::resize(size_type new_size, const T& element)
  {
    if (new_size < BaseList<T>::size()) {
      erase(new_size, BaseList<T>::size());
    } else if (new_size > BaseList<T>::size()) {
      insert(BaseList<T>::size(), new_size - BaseList<T>::size(), element);
    }
  }

  template <typename T>
  inline const T& ArrayList<T>::operator[](size_type i) const
  {
    PREC_INDEX_LIST(i);
    return BaseList<T>::at(i);
  }

  template <typename T>
  inline T& ArrayList<T>::operator[](size_type i)
  {
    PREC_INDEX_LIST(i);
    return BaseList<T>::at(i);
  }

  template <typename T>
  inline void ArrayList<T>::push_back(const T& element)
  {
    BaseList<T>::prepare_size(BaseList<T>::size() + 1);
    BaseList<T>::create(BaseList<T>::size() - 1, element);
  }

  template <typename T>
  inline T ArrayList<T>::pop_back()
  {
    PREC_EMPTY();
    T element = BaseList<T>::at(BaseList<T>::size() - 1);
    BaseList<T>::destroy(BaseList<T>::size() - 1);
    BaseList<T>::prepare_size(BaseList<T>::size() - 1);
    return element;
  }

  template <typename T>
  inline bool ArrayList<T>::remove(const T& element)
  {
    for (size_type i = 0; i < BaseList<T>::size(); ++i) {
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
  inline typename ArrayList<T>::size_type ArrayList<T>::remove_all(const T& element)
  {
    size_type removed = 0;
    for (size_type i = 0; i < BaseList<T>::size(); ++i) {
      while (i < BaseList<T>::size() && BaseList<T>::at(i) == element) {
        ++removed;
        ++i;
      }
      size_type good_length = 0;
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
  inline const T& ArrayList<T>::front() const
  {
    PREC_EMPTY();
    return BaseList<T>::at(0);
  }

  template <typename T>
  inline T& ArrayList<T>::front()
  {
    PREC_EMPTY();
    return BaseList<T>::at(0);
  }

  template <typename T>
  inline const T& ArrayList<T>::back() const
  {
    PREC_EMPTY();
    return BaseList<T>::at(BaseList<T>::size() - 1);
  }

  template <typename T>
  inline T& ArrayList<T>::back()
  {
    PREC_EMPTY();
    return BaseList<T>::at(BaseList<T>::size() - 1);
  }

  template <typename T>
  inline typename ArrayList<T>::iterator ArrayList<T>::begin()
  {
    return iterator(this, 0);
  }

  template <typename T>
  inline typename ArrayList<T>::const_iterator ArrayList<T>::begin() const
  {
    return const_iterator(this, 0);
  }

  template <typename T>
  inline typename ArrayList<T>::iterator ArrayList<T>::end()
  {
    return iterator(this, BaseList<T>::size());
  }

  template <typename T>
  inline typename ArrayList<T>::const_iterator ArrayList<T>::end() const {
    return const_iterator(this, BaseList<T>::size());
  }

  template <typename T>
  inline const T* ArrayList<T>::data() const
  {
    return BaseList<T>::data();
  }

  template <typename T>
  inline void ArrayList<T>::clear()
  {
    erase(0, BaseList<T>::size());
  }

  template <typename T>
  inline void ArrayList<T>::reorganize()
  {}

}

#endif // DATASTRUCTURES_ARRAYLIST_HPP
