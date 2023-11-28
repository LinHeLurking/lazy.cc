#include <gtest/gtest.h>

#include "lazy++.hpp"

TEST(Heap, Min) {
  auto min_heap = _::MinHeap<int>();
  min_heap.push(1);
  EXPECT_EQ(min_heap.top(), 1);
  min_heap.push(-2);
  EXPECT_EQ(min_heap.top(), -2);
  min_heap.push(3);
  min_heap.pop();
  min_heap.pop();
  EXPECT_EQ(min_heap.top(), 3);
}

TEST(Heap, Max) {
  auto max_heap = _::MaxHeap<int>();
  max_heap.push(1);
  EXPECT_EQ(max_heap.top(), 1);
  max_heap.push(2);
  EXPECT_EQ(max_heap.top(), 2);
  max_heap.push(4);
  EXPECT_EQ(max_heap.top(), 4);
  max_heap.push(3);
  max_heap.pop();
  EXPECT_EQ(max_heap.top(), 3);
}