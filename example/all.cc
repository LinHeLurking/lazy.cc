#include <vector>

#include "../src/lazy++.hpp"

void SortExample() {
  std::vector<int> v = {3, 1, -8, 7, 10};
  _::PrintLine("Before sort: ", v);
  _::Sort(v);
  _::PrintLine("After sort: ", v);
}

void SimpleHeapExample() {
  _::MinHeap<int> hp_min;
  _::MaxHeap<int> hp_max;
  for (int x : {3, 5, 8, 1, -1, -100, 2}) {
    hp_min.push(x);
    hp_max.push(x);
  }

  _::Print("Min heap: ");
  while (!hp_min.empty()) {
    _::Print(hp_min.top(), " ");
    hp_min.pop();
  }
  std::cout << std::endl;

  _::Print("Max heap: ");
  while (!hp_max.empty()) {
    _::Print(hp_max.top(), " ");
    hp_max.pop();
  }
  std::cout << std::endl;
}

void CustomHeapExample() {
  auto q = _::CreateHeap<std::vector<int>>([](const auto &l, const auto &r) {
    return l[0] != r[0] ? l[0] < r[0] : l[1] > r[1];
  });
  q.push({1, 2});
  q.push({-1, 0});
  q.push({-1, 2});
  q.push({2, 2});
  q.push({2, 3});
  q.push({0, 0});
  _::Print("Custom Heap: ");
  while (!q.empty()) {
    _::Print(q.top(), " ");
    q.pop();
  }
  std::cout << std::endl;
}

int main() {
  SortExample();
  SimpleHeapExample();
  CustomHeapExample();
  return 0;
}
