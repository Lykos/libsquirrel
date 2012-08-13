#ifndef DATASTRUCTURES_QUEUE_H
#define DATASTRUCTURES_QUEUE_H

namespace DataStructures {
  
  template <typename T>
  class Queue<T> : private DataStructures::ArrayList<T>
  {
  public:
    Queue();
  };
  
} // namespace DataStructures

#endif // DATASTRUCTURES_QUEUE_H
