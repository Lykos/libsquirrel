#ifndef DATASTRUCTURES_QUEUE_HPP
#define DATASTRUCTURES_QUEUE_HPP

#include "queue.h"
#include "baselist.h"
#include "listiterator.h"

namespace DataStructures {

  template <typename T>
  inline std::ostream& operator<<(std::ostream& out, const Queue<T>& list)
  {
    out << "Queue[";
    for (typename Queue<T>::const_iterator it = list.begin(); it != list.end(); it++) {
      out << *it;
      if (it + 1 != list.end()) {
        out << ", ";
      }
    }
    out << "]";
    return out;
  }

  template <typename T>
  inline Queue<T>::Queue(size_type initial_size, const T& element):
    BaseList<T>(initial_size, element)
  {
  }

  template <typename T>
  inline Queue<T>::Queue(const Queue<T> &other):
    BaseList<T>(other),
    m_begin (other.m_begin)
  {
  }

  template <typename T>
  template <typename Iterator>
  inline Queue<T>::Queue(const Iterator& begin, const Iterator& end)
  {
    insert(m_begin, begin, end);
  }

  template <typename T>
  inline typename Queue<T>::size_type Queue<T>::q_index(size_type index) const
  {
    return (index + m_begin) % BaseList<T>::capacity();
  }

  template <typename T>
  inline void Queue<T>::destroy_queue_part(size_type q_start, size_type length)
  {
    assert(length <= BaseList<T>::capacity());
    if (q_start + length <= BaseList<T>::capacity()) {
      BaseList<T>::destroy_part(q_start, length);
    } else {
      size_type first_segment = BaseList<T>::capacity() - q_start;
      BaseList<T>::destroy_part(q_start, first_segment);
      BaseList<T>::destroy_part(0, length - first_segment);
    }
  }

  template <typename T>
  inline void Queue<T>::move_queue_part(size_type q_insert_position, size_type q_start, size_type length)
  {
    assert(length <= BaseList<T>::capacity());
    T *tmp = static_cast<T*>(malloc(sizeof(T) * length));
    for (size_type i = 0; i < length; ++i) {
      tmp[i] = BaseList<T>::at((q_start + i) % BaseList<T>::capacity());
    }
    for (size_type i = 0; i < length; ++i) {
      BaseList<T>::at((q_insert_position + i) % BaseList<T>::capacity()) = tmp[i];
    }
    free(tmp);
  }

  template <typename T>
  inline void Queue<T>::make_room(size_type index, size_type old_size, size_type length)
  {
    assert(BaseList<T>::capacity() >= length + old_size);
    if (index < old_size - index) {
      // Move part before entry
      move_queue_part(q_index(BaseList<T>::capacity() - length), q_index(0), index);
      m_begin = q_index(BaseList<T>::capacity() - length);
    } else {
      // Move part after entry
      move_queue_part(q_index(index + length), q_index(index), old_size - index);
    }
  }

  template <typename T>
  inline const T& Queue<T>::operator[](size_type i) const
  {
    PREC_INDEX_LIST(i);
    return BaseList<T>::at(q_index(i));
  }

  template <typename T>
  inline T& Queue<T>::operator[](size_type i)
  {
    PREC_INDEX_LIST(i);
    return BaseList<T>::at(q_index(i));
  }

  template <typename T>
  inline const T& Queue<T>::front() const
  {
    PREC_EMPTY();
    return BaseList<T>::at(m_begin);
  }

  template <typename T>
  inline T& Queue<T>::front()
  {
    PREC_EMPTY();
    return BaseList<T>::at(m_begin);
  }

  template <typename T>
  inline const T& Queue<T>::back() const
  {
    PREC_EMPTY();
    return operator[](BaseList<T>::size() - 1);
  }

  template <typename T>
  inline T& Queue<T>::back()
  {
    PREC_EMPTY();
    return operator[](BaseList<T>::size() - 1);
  }

  template <typename T>
  inline typename Queue<T>::iterator Queue<T>::begin()
  {
    return iterator(this, 0);
  }

  template <typename T>
  inline typename Queue<T>::const_iterator Queue<T>::begin() const
  {
    return const_iterator(this, 0);
  }

  template <typename T>
  inline typename Queue<T>::iterator Queue<T>::end()
  {
    return iterator(this, BaseList<T>::size());
  }

  template <typename T>
  inline typename Queue<T>::const_iterator Queue<T>::end() const
  {
    return const_iterator(this, BaseList<T>::size());
  }

  template <typename T>
  inline int_fast8_t Queue<T>::compare_to(const Queue<T>& other) const
  {
    if (this == &other) {
      return 0;
    }
    for (size_type i = 0; i < BaseList<T>::size() && i < other.size(); ++i) {
      if (BaseList<T>::at(q_index(i)) < other.at(other.q_index(i))) {
        return -1;
      } else if (other.at(other.q_index(i)) < BaseList<T>::at(q_index(i))) {
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
  inline bool Queue<T>::operator==(const Queue<T>& other) const
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
  inline bool Queue<T>::operator!=(const Queue<T>& other) const
  {
    return !operator==(other);
  }

  template <typename T>
  inline bool Queue<T>::operator<(const Queue<T>& other) const
  {
    return compare_to(other) == -1;
  }

  template <typename T>
  inline bool Queue<T>::operator<=(const Queue<T>& other) const
  {
    return compare_to(other) != 1;
  }

  template <typename T>
  inline bool Queue<T>::operator>(const Queue<T>& other) const
  {
    return compare_to(other) == 1;
  }

  template <typename T>
  inline bool Queue<T>::operator>=(const Queue<T>& other) const
  {
    return compare_to(other) != -1;
  }

  template <typename T>
  template <typename Iterator>
  inline void Queue<T>::assign(Iterator begin, Iterator end)
  {
    clear();
    insert(0, begin, end);
  }

  template <typename T>
  inline void Queue<T>::assign(size_type number, const T& element)
  {
    clear();
    insert(0, number, element);
  }

  template <typename T>
  inline typename Queue<T>::iterator Queue<T>::erase(iterator position)
  {
    return erase(position - begin());
  }

  template <typename T>
  inline typename Queue<T>::iterator Queue<T>::erase(iterator start, iterator end)
  {
    return erase(start - begin(), end - begin());
  }

  template <typename T>
  inline typename Queue<T>::iterator Queue<T>::erase(size_type index)
  {
    return erase(index, index + 1);
  }

  template <typename T>
  inline typename Queue<T>::iterator Queue<T>::erase(size_type start, size_type end)
  {
    PREC_INDEX_INSERT_LIST(start);
    PREC_INDEX_INSERT_LIST(end);
    PREC(InvalidRange, start <= end);
    destroy_queue_part(q_index(start), end - start);
    if (start < BaseList<T>::size() - end) {
      move_queue_part(q_index(end - start), q_index(0), start);
      m_begin = q_index(end - start);
    } else {
      move_queue_part(q_index(start), q_index(end), BaseList<T>::size() - end);
    }
    BaseList<T>::prepare_size(BaseList<T>::size() - (end - start));
    return iterator(this, start);
  }

  template <typename T>
  inline typename Queue<T>::iterator Queue<T>::insert(size_type index, const T& element)
  {
    insert(index, size_type(1), element);
    return iterator(this, index);
  }

  template <typename T>
  inline void Queue<T>::insert(size_type index, size_type number, const T& element)
  {
    PREC_INDEX_INSERT_LIST(index);
    size_type old_size = BaseList<T>::size();
    BaseList<T>::prepare_size(old_size + number);
    make_room(index, old_size, number);
    for (size_type i = index; i < index + number; ++i) {
      BaseList<T>::create(q_index(i), element);
    }
  }

  template <typename T>
  template <typename Iterator>
  inline void Queue<T>::insert(size_type index, Iterator begin, Iterator end)
  {
    PREC_INDEX_INSERT_LIST(index);
    size_type old_size = BaseList<T>::size();
    BaseList<T>::prepare_size(old_size + (end - begin));
    make_room(index, old_size, end - begin);
    for (; begin != end; ++begin, ++index) {
      BaseList<T>::create(q_index(index), *begin);
    }
  }

  template <typename T>
  inline typename Queue<T>::iterator Queue<T>::insert(iterator position, const T& element)
  {
    return insert(position - begin(), element);
  }

  template <typename T>
  inline void Queue<T>::insert(iterator position, size_type number, const T& element)
  {
    insert(position - begin(), number, element);
  }

  template <typename T>
  template <typename Iterator>
  inline void Queue<T>::insert(iterator position, Iterator start, Iterator end)
  {
    insert(position - begin(), start, end);
  }

  template <typename T>
  inline void Queue<T>::resize(size_type new_size, const T& element)
  {
    if (new_size < BaseList<T>::size()) {
      erase(new_size, BaseList<T>::size());
    } else if (new_size > BaseList<T>::size()) {
      insert(BaseList<T>::size(), new_size - BaseList<T>::size(), element);
    }
  }

  template <typename T>
  inline void Queue<T>::clear()
  {
    destroy_queue_part(0, BaseList<T>::size());
    BaseList<T>::prepare_size(0);
  }

  template <typename T>
  inline void Queue<T>::push_back(const T& element)
  {
    size_type old_size = BaseList<T>::size();
    BaseList<T>::prepare_size(BaseList<T>::size() + 1);
    BaseList<T>::create(q_index(old_size), element);
  }

  template <typename T>
  inline void Queue<T>::push_front(const T& element)
  {
    BaseList<T>::prepare_size(BaseList<T>::size() + 1);
    if (m_begin == 0) {
      m_begin = BaseList<T>::capacity();
    }
    m_begin = (BaseList<T>::capacity() + m_begin - 1) % BaseList<T>::capacity();
    BaseList<T>::create(m_begin, element);
  }

  template <typename T>
  inline T Queue<T>::pop_front()
  {
    PREC_EMPTY();
    T element = BaseList<T>::at(m_begin);
    BaseList<T>::destroy(m_begin);
    m_begin = (m_begin + 1) % BaseList<T>::capacity();
    BaseList<T>::prepare_size(BaseList<T>::size() - 1);
    return element;
  }

  template <typename T>
  inline T Queue<T>::pop_back()
  {
    PREC_EMPTY();
    size_type q_end = q_index(BaseList<T>::size() - 1);
    T element = BaseList<T>::at(q_end);
    BaseList<T>::destroy(q_end);
    BaseList<T>::prepare_size(BaseList<T>::size() - 1);
    return element;
  }

  template <typename T>
  inline void Queue<T>::reorganize()
  {
    move_queue_part(0, m_begin, BaseList<T>::size());
    m_begin = 0;
  }

}

#endif // DATASTRUCTURES_QUEUE_HPP
