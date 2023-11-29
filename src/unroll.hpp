#ifndef LAZY_EXAMPLE_UNROLL_HPP
#define LAZY_EXAMPLE_UNROLL_HPP

#include "./force_inline.hpp"

namespace _ {
template <class A1, class A2, class A4>
FORCE_INLINE void Unroll(size_t n, A1 &&a1, A2 &&a2, A4 &&a4) {
  size_t i = n >> 2;
  for (; i > 0; --i) {
    a4();
  }
  if (n & 2) {
    a2();
  }
  if (n & 1) {
    a1();
  }
}

template <class A1>
FORCE_INLINE void Unroll(size_t n, A1 &&a1) {
  auto a2 = [&a1]() {
    a1();
    a1();
  };
  auto a4 = [&a2]() {
    a2();
    a2();
  };
  Unroll(n, a1, a2, a4);
}
}  // namespace _

#define M_Unroll4(n, a1, a2, a4) \
  {                              \
    size_t __i = size_t(n) >> 2; \
    for (; __i > 0; --__i) {     \
      a4;                        \
    }                            \
    if (n & 2) {                 \
      a2;                        \
    }                            \
    if (n & 1) {                 \
      a1;                        \
    }                            \
  }

#define M_Unroll(n, a1) \
  {                     \
    M_Unroll4(          \
        n, a1,          \
        {               \
          a1;           \
          a1;           \
        },              \
        {               \
          a1;           \
          a1;           \
          a1;           \
          a1;           \
        });             \
  }

#endif  // LAZY_EXAMPLE_UNROLL_HPP
