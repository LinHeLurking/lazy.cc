#include <gtest/gtest.h>

#include "lazy++.hpp"

TEST(Unroll, Way_1_Macro) {
  {
    std::vector<int> v;
    v.resize(1000);
    {
      size_t i = 0;
      M_Unroll(v.size(), {
        v[i] = -1;
        ++i;
      });
    }
    for (int k : v) {
      EXPECT_EQ(k, -1);
    }
  }
  {
    std::vector<int> v;
    v.resize(1000);
    {
      size_t i = 0;
      M_Unroll(v.size(), {
        v[i] = int(i) * int(i);
        ++i;
      });
    }
    for (int k = 0; k < v.size(); ++k) {
      EXPECT_EQ(v[k], int(k) * int(k)) << "k: " << k;
    }
  }
}

//TEST(Unroll, Way_1_Template) {
//  {
//    std::vector<int> v;
//    v.resize(1000);
//    {
//      size_t i = 0;
//      _::Unroll(v.size(), [&v, &i]() {
//        v[i] = -1;
//        i++;
//      });
//    }
//    for (int k : v) {
//      EXPECT_EQ(k, -1);
//    }
//  }
//  {
//    std::vector<int> v;
//    v.resize(1000);
//    {
//      size_t i = 0;
//      _::Unroll(v.size(), [&v, &i]() {
//        v[i] = int(i) * int(i);
//        ++i;
//      });
//    }
//    for (int k = 0; k < v.size(); ++k) {
//      EXPECT_EQ(v[k], int(k) * int(k)) << "k: " << k;
//    }
//  }
//}

TEST(Unroll, Way_4_Macro) {
  std::vector<int> v(1000, -2);
  {
    size_t i = 0;
    M_Unroll4(
        v.size(),
        {
          v[i]++;
          i++;
        },
        {
          v[i]++;
          i++;
          v[i]++;
          i++;
        },
        {
          v[i]++;
          i++;
          v[i]++;
          i++;
          v[i]++;
          i++;
          v[i]++;
          i++;
        });
  }
  for (int k : v) {
    EXPECT_EQ(k, -1);
  }
}

//TEST(Unroll, Way_4_Temaplte) {
//  std::vector<int> v(1000, -2);
//  {
//    size_t i = 0;
//    _::Unroll(
//        v.size(),
//        [&v, &i]() {
//          v[i]++;
//          i++;
//        },
//        [&v, &i]() {
//          v[i]++;
//          i++;
//          v[i]++;
//          i++;
//        },
//        [&v, &i]() {
//          v[i]++;
//          i++;
//          v[i]++;
//          i++;
//          v[i]++;
//          i++;
//          v[i]++;
//          i++;
//        });
//  }
//  for (int k : v) {
//    EXPECT_EQ(k, -1);
//  }
//}
