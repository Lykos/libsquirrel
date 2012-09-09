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
      destroy_part(q_start, length);
    } else {
      size_type first_segment = BaseList<T>::capacity() - q_start;
      destroy_part(q_start, first_segment);
      destroy_part(0, length - first_segment);
    }
  }

  template <typename T>
  inline void Queue<T>::move_queue_part(size_type q_insert_position, size_type q_start, size_type length)
  {
    assert(length <= BaseList<T>::capacity());
    if (q_start + length <= BaseList<T>::capacity()) {
      move_queue_continuous(q_insert_position, q_start, length);
    } else {
      size_type first_segment = BaseList<T>::capacity() - q_start;
      move_queue_continuous(q_insert_position, q_start, first_segment);
      move_queue_continuous(q_insert_position + first_segment, 0, length - first_segment);
    }
  }

  template <typename T>
  inline void Queue<T>::move_queue_continuous(size_type q_insert_position, size_type q_start, size_type length)
  {
    assert(q_start + length <= BaseList<T>::capacity());
    if (q_insert_position + length <= BaseList<T>::capacity()) {
      BaseList<T>::move_part(q_insert_position, q_start, length);
    } else {
      size_type end_segment = BaseList<T>::capacity() - q_insert_position;
      BaseList<T>::move_part(q_insert_position, q_start, end_segment);
      BaseList<T>::move_part(0, q_start + end_segment, length - end_segment);
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
    BaseList<T>::destroy_part(q_index(start), end - start);
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
    if (index < BaseList<T>::size() - index) {
      assert(BaseList<T>::capacity() >= number);
      move_queue_part(q_index(BaseList<T>::capacity() - number), q_index(0), index);
      m_begin = q_index(BaseList<T>::capacity() - number);
    } else {
      move_queue_part(q_index(index + number), q_index(index), BaseList<T>::size() - index);
    }
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
    BaseList<T>::move_part(index + (end - begin), index, old_size - index);
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
    size_type part_length = std::min(BaseList<T>::size(), BaseList<T>::capacity() - m_begin);
    BaseList<T>::destroy_part(m_begin, part_length);
    BaseList<T>::destroy_part(0, BaseList<T>::size() - part_length);
    BaseList<T>::prepare_size(0);
  }

  template <typename T>
  inline void Queue<T>::push_back(const T& element)
  {
    size_type old_size = BaseList<T>::size();
    BaseList<T>::prepare_size(BaseList<T>::size() + 1);
    BaseList<T>::create(old_size, element);
  }

  template <typename T>
  inline void Queue<T>::push_front(const T& element)
  {
    BaseList<T>::prepare_size(BaseList<T>::size() + 1);
    if (m_begin == 0) {
      m_begin = BaseList<T>::capacity();
    }
    --m_begin;
    BaseList<T>::create(m_begin, element);
  }

  template <typename T>
  inline T Queue<T>::pop_front()
  {
    PREC_EMPTY();
    T element = BaseList<T>::at(m_begin);
    BaseList<T>::destroy(m_begin);
    ++m_begin;
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
