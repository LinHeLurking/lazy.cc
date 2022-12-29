# Lazy++

**Make STL Sweet!**

This repository contains some tricky c++ helpers for a lazy man.

## Core Lines for Copy

```cpp
#include <bits/stdc++.h>

namespace _ {

template <class Container>
void Sort(Container&& container) {
  std::sort(container.begin(), container.end());
}

template <class Container, class Comparator>
void Sort(Container&& container, Comparator comp) {
  std::sort(container.begin(), container.end(), comp);
}

template <class T>
using MaxHeap = std::priority_queue<T, std::vector<T>, std::less<T>>;

template <class T>
using MinHeap = std::priority_queue<T, std::vector<T>, std::greater<T>>;

template <class T, class Comparator>
auto CreateHeap(Comparator&& comp) {
  return std::priority_queue<T, std::vector<T>, Comparator>(comp);
}

}  // namespace _
```
