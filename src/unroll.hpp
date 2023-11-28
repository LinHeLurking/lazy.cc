#ifndef LAZY_EXAMPLE_UNROLL_HPP
#define LAZY_EXAMPLE_UNROLL_HPP

#include "force_inline.hpp"

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

template <class A1, class A2, class A4>
FORCE_INLINE void UnrollIdx(size_t n, A1 &&a1, A2 &&a2, A4 &&a4) {
  size_t i = 0;
  for (; i < n; i += 4) {
    a4(i);
  }
  if (n & 2) {
    a2(i);
    i += 2;
  }
  if (n & 1) {
    a1(i);
  }
}

template <class A1>
FORCE_INLINE void UnrollIdx(size_t n, A1 &&a1) {
  auto a2 = [&a1](size_t i) {
    a1(i);
    a1(i + 1);
  };
  auto a4 = [&a2](size_t i) {
    a2(i);
    a2(i + 2);
  };
  UnrollIdx(n, a1, a2, a4);
}
}  // namespace _

#endif  // LAZY_EXAMPLE_UNROLL_HPP
