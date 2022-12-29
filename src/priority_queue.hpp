#ifndef LAZY_PLUS_PLUS_PRIORITY_QUEUE_H
#define LAZY_PLUS_PLUS_PRIORITY_QUEUE_H

#include <queue>
#include <vector>

namespace _ {

template <class T>
using MaxHeap = std::priority_queue<T, std::vector<T>, std::less<T>>;

template <class T>
using MinHeap = std::priority_queue<T, std::vector<T>, std::greater<T>>;

template <class T, class Comparator>
auto CreateHeap(Comparator&& comp) {
  return std::priority_queue<T, std::vector<T>, Comparator>(comp);
}

}  // namespace _

#endif
