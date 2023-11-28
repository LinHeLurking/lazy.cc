#include <gtest/gtest.h>

#include "lazy++.hpp"

TEST(Sort, _0) {
  std::vector<int> v = {5, -4, 3, -2, 1};
  _::Sort(v);
  EXPECT_TRUE(std::is_sorted(v.begin(), v.end()));
}