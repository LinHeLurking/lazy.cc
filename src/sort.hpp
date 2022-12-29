#ifndef LAZY_PLUG_PLUS_SORT_H
#define LAZY_PLUG_PLUS_SORT_H

#include <algorithm>

namespace _ {

template <class Container>
void Sort(Container &container) {
  std::sort(container.begin(), container.end());
}

template <class Container, class Comparator>
void Sort(Container &container, Comparator comp) {
  std::sort(container.begin(), container.end(), comp);
}

template <class Container>
void StableSort(Container &container) {
  std::stable_sort(container.begin(), container.end());
}

template <class Container, class Comparator>
void StableSort(Container &container, Comparator comp) {
  std::stable_sort(container.begin(), container.end(), comp);
}

}  // namespace _

#endif
