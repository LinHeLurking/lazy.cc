#include <gtest/gtest.h>

#include "lazy++.hpp"

TEST(Unroll, Way_1) {
  {
    std::vector<int> v;
    v.resize(1000);
    size_t i = 0;
    _::Unroll(v.size(), [&v, &i]() { v[i++] = -1; });
    for (int k : v) {
      EXPECT_EQ(k, -1);
    }
  }
  {
    std::vector<int> v;
    v.resize(1000);
    _::UnrollIdx(v.size(), [&v](size_t i) { v[i] = int(i) * int(i); });
    for (int i = 0; i < v.size(); ++i) {
      EXPECT_EQ(v[i], int(i) * int(i)) << "i: " << i;
    }
  }
}

TEST(Unroll, Way_4) {
  std::vector<int> v(1000, -2);
  auto a1 = [&v](size_t i) { v[i] += 1; };
  auto a2 = [&v](size_t i) {
    v[i] += 1;
    v[i + 1] += 1;
  };
  auto a4 = [&v](size_t i) {
    v[i] += 1;
    v[i + 1] += 1;
    v[i + 2] += 1;
    v[i + 3] += 1;
  };
  _::UnrollIdx(v.size(), a1, a2, a4);
  for (int i : v) {
    EXPECT_EQ(i, -1);
  }
}
