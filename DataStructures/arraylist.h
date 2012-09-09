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

    inline ArrayList();

    inline explicit ArrayList(size_type initial_size, const T& element = T());

    template <typename Iterator>
    ArrayList(Iterator begin, Iterator end);

    inline const T& operator[](size_type i) const;

    inline T& operator[](size_type i);

    inline int_fast8_t compare_to(const ArrayList<T>& other) const;

    inline bool operator==(const ArrayList<T>& other) const;

    inline bool operator!=(const ArrayList<T>& other) const;

    inline bool operator<(const ArrayList<T>& other) const;

    inline bool operator<=(const ArrayList<T>& other) const;

    inline bool operator>(const ArrayList<T>& other) const;

    inline bool operator>=(const ArrayList<T>& other) const;

    template <typename Iterator>
    inline void assign(Iterator begin, Iterator end);

    inline void assign(size_type number, const T& element);

    inline void erase(iterator position);

    inline void erase(iterator start, iterator end);

    inline void erase(size_type index);

    inline void erase(size_type start, size_type end);

    iterator insert(size_type index, const T& element);

    void insert(size_type index, size_type number, const T& element);

    template <typename Iterator>
    void insert(size_type index, Iterator start, Iterator end);

    iterator insert(iterator position, const T& element);

    void insert(iterator position, size_type number, const T& element);

    template <typename Iterator>
    void insert(iterator position, Iterator start, Iterator end);

    void resize(size_type new_size, const T& element = T());

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
