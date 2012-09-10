#ifndef DATASTRUCTURES_ARRAYLIST_H
#define DATASTRUCTURES_ARRAYLIST_H

#include "baselist.h"
#include "listiterator.h"

namespace DataStructures {

  template <typename T>
  class ArrayList;

  template <typename T>
  inline std::ostream& operator<<(std::ostream& out, const ArrayList<T>& it);

  template <typename T>
  class ArrayList : public BaseList<T>
  {
    friend std::ostream& operator<< <> (std::ostream& out, const ArrayList<T>& it);
  public:
    typedef ListIterator<T, ArrayList<T> > iterator;

    typedef ListIterator<T const, ArrayList<T> const > const_iterator;

    typedef typename BaseList<T>::size_type size_type;

    inline ArrayList(std::initializer_list<T> list);

    inline explicit ArrayList(size_type initial_size = 0, const T& element = T());

    template <typename InputIterator>
    ArrayList(InputIterator begin, InputIterator end);

    inline const T& operator[](size_type i) const;

    inline T& operator[](size_type i);

    inline int_fast8_t compare_to(const ArrayList<T>& other) const;

    inline bool operator==(const ArrayList<T>& other) const;

    inline bool operator!=(const ArrayList<T>& other) const;

    inline bool operator<(const ArrayList<T>& other) const;

    inline bool operator<=(const ArrayList<T>& other) const;

    inline bool operator>(const ArrayList<T>& other) const;

    inline bool operator>=(const ArrayList<T>& other) const;

    template <typename InputIterator>
    inline void assign(InputIterator begin, InputIterator end);

    inline void assign(size_type number, const T& element);

    inline iterator erase(iterator position);

    inline iterator erase(iterator start, iterator end);

    inline iterator erase(size_type index);

    inline iterator erase(size_type start, size_type end);

    inline iterator insert(size_type index, const T& element);

    inline void insert(size_type index, size_type number, const T& element);

    template <typename InputIterator>
    inline void insert(size_type index, InputIterator start, InputIterator end);

    inline iterator insert(iterator position, const T& element);

    inline void insert(iterator position, size_type number, const T& element);

    template <typename InputIterator>
    inline void insert(iterator position, InputIterator start, InputIterator end);

    inline void resize(size_type new_size, const T& element = T());

    inline void push_back(const T& element);

    inline T pop_back();

    inline bool remove(const T& element);

    inline size_type remove_all(const T& element);

    inline const T& front() const;

    inline T& front();

    inline const T& back() const;

    inline T& back();

    inline iterator begin();

    inline const_iterator begin() const;

    inline iterator end();

    inline const_iterator end() const;

    inline const T* data() const;

    inline void clear();

    inline void reorganize();

  };

}

#include "arraylist.hpp"

#endif // DATASTRUCTURES_ARRAYLIST_H
