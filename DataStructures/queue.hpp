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
  inline Queue<T>::Queue():
    BaseList<T>(),
    m_begin(0)
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
    push_all(begin, end);
  }

  template <typename T>
  template <typename Iterator>
  inline void Queue<T>::push_all(const Iterator& begin, const Iterator& end)
  {
    if (end <= begin) {
      return;
    }
    size_type i = BaseList<T>::size();
    BaseList<T>::prepare_size(BaseList<T>::size() + (end - begin));
    for (Iterator it = begin; it != end; ++it, ++i) {
      BaseList<T>::create(index_of(i), *it);
    }
  }

  template <typename T>
  inline bool Queue<T>::operator!=(const Queue<T>& other) const
  {
    return !operator==(other);
  }

  template <typename T>
  inline typename Queue<T>::size_type Queue<T>::index_of(size_type index) const
  {
    return (index + m_begin) % BaseList<T>::capacity();
  }

  template <typename T>
  inline const T& Queue<T>::operator[](size_type i) const
  {
    PREC_INDEX_LIST(i);
    return BaseList<T>::at(index_of(i));
  }

  template <typename T>
  inline T& Queue<T>::operator[](size_type i)
  {
    PREC_INDEX_LIST(i);
    return BaseList<T>::at(index_of(i));
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
  inline bool Queue<T>::operator==(const Queue<T>& other) const
  {
    if (BaseList<T>::size() != other.size()) {
      return false;
    }
    for (size_type i = 0; i < BaseList<T>::size(); ++i) {
      if (operator[](i) != other.operator[](i)) {
        return false;
      }
    }
    return true;
  }

  template <typename T>
  inline void Queue<T>::clear()
  {
    size_type part_length = std::min(BaseList<T>::size(), BaseList<T>::capacity() - m_begin);
    BaseList<T>::destroy_part(m_begin, part_length);
    BaseList<T>::destroy_part(0, BaseList<T>::size() - part_length);
    BaseList<T>::prepare_size(0);
  }

  template <typename T>
  inline void Queue<T>::push(const T& element)
  {
    size_type old_size = BaseList<T>::size();
    BaseList<T>::prepare_size(BaseList<T>::size() + 1);
    BaseList<T>::create(old_size, element);
  }

  template <typename T>
  inline T Queue<T>::pop()
  {
    PREC_EMPTY();
    T element = BaseList<T>::at(m_begin);
    BaseList<T>::destroy(m_begin);
    ++m_begin;
    BaseList<T>::prepare_size(BaseList<T>::size() - 1);
    return element;
  }

  template <typename T>
  inline void Queue<T>::reorganize()
  {
    const size_type capacity = BaseList<T>::capacity();
    size_type part_start = 0;
    size_type begin = m_begin;
    size_type size = BaseList<T>::size();
    size_type end = (begin + size) % capacity;
    while (part_start != capacity) {
      // invariants
      assert(part_start < capacity);
      assert(size <= BaseList<T>::size());
      assert(part_start <= begin && begin <= capacity);
      assert(part_start <= end && begin <= capacity);
      assert(begin <= end || (capacity - begin) + (end - part_start) == size);
      assert(begin >= end || end - begin == size);
      assert(begin != end || size == 0 || part_start + size == capacity);
      if (begin == end || begin == capacity || begin == part_start) {
        // #||# -> ## ||
        // 12|##| -> 12## ||
        // |12|## -> 12## ||
        break;
        /* Unecessary, but would be correct:
        part_start = capacity;
        begin = capacity;
        end = capacity;
        size = 0;*/
      } else if (end == part_start) {
        end = capacity;
      } else if (begin < end) {
        // ##|1234|# -> 1234### ||
        BaseList<T>::move_part(part_start, begin, size);
        part_start = capacity;
        /* Unnecessary, but would be correct:
        begin = capacity;
        end = capacity;
        size = 0;*/
      } else {
        size_type end_size = end - part_start;
        size_type begin_size = capacity - begin;
        assert(begin_size + end_size == size);
        if (end_size >= begin_size) {
          // 345|#|12 -> 12 5|#|34
          BaseList<T>::swap_parts(part_start, begin, begin_size);
          assert(begin_size > 0); // Necessary for progress
          part_start += begin_size;
          size = end_size;
          // begin, end remain unchanged
        } else if (begin - part_start <= begin_size) {
          size_type size_moved = begin - part_start;
          assert(size_moved >= end_size); // else the next step would be more efficient
          // 56|#|1234 -> 123 56|#|4
          BaseList<T>::swap_parts(part_start, begin, end_size);
          BaseList<T>::move_part(end, begin + end_size, begin - end);
          assert(end_size + (begin - end) == size_moved);
          size -= size_moved;
          part_start = begin;
          begin += size_moved;
          end += size_moved;
        } else if (end_size <= begin_size) {
          // 45|##|123 -> 123 #|45|#
          BaseList<T>::swap_parts(part_start, begin, end_size);
          BaseList<T>::move_part(end, begin + end_size, begin_size - end_size);
          part_start += begin_size;
          size = end_size;
          end += begin_size;
          // begin remains unchanged
        } else {
          assert(false);
        }
      }
    }
    m_begin = 0;
  }

}

#endif // DATASTRUCTURES_QUEUE_HPP
