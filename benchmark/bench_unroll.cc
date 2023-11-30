#include <benchmark/benchmark.h>

#include "lazy++.hpp"

constexpr size_t n = 100000;

class Int8Unroll : public benchmark::Fixture {};
class Int32Unroll : public benchmark::Fixture {};

BENCHMARK_F(Int8Unroll, Naive)(benchmark::State& state) {
  auto src = new int8_t[n];
  auto dst = new int8_t[n];

  for (auto _ : state) {
    std::fill(src, src + n, 0xAA);
    for (int i = 0; i < n; ++i) {
      dst[i] = src[i] & int8_t(0x80);
    }
  }

  delete[] src;
  delete[] dst;
}

BENCHMARK_F(Int8Unroll, Macro4Way)(benchmark::State& state) {
  auto src = new int8_t[n];
  auto dst = new int8_t[n];

  for (auto _ : state) {
    std::fill(src, src + n, 0xAA);
    int8_t *p = src, *q = dst;
    M_Unroll4(
        n,
        {
          *q = *p & int8_t(0x80);
          p++;
          q++;
        },
        {
          *((int16_t*)(q)) = *((int16_t*)p) & int16_t(0x80 << 8 | 0x80);
          p += 2;
          q += 2;
        },
        {
          *((int32_t*)q) = *((int32_t*)p) &
                           int32_t(0x80 << 24 | 0x80 << 16 | 0x80 << 8 | 0x80);
          p += 4;
          q += 4;
        });
  }
  delete[] src;
  delete[] dst;
}

BENCHMARK_F(Int8Unroll, Template4Way)(benchmark::State& state) {
  auto src = new int8_t[n];
  auto dst = new int8_t[n];

  for (auto _ : state) {
    std::fill(src, src + n, 0xAA);
    int8_t *p = src, *q = dst;
    _::Unroll(
        n,
        [&p, &q]() {
          *q = *p & int8_t(0x80);
          p++;
          q++;
        },
        [&p, &q]() {
          *((int16_t*)(q)) = *((int16_t*)p) & int16_t(0x80 << 8 | 0x80);
          p += 2;
          q += 2;
        },
        [&p, &q]() {
          *((int32_t*)q) = *((int32_t*)p) &
                           int32_t(0x80 << 24 | 0x80 << 16 | 0x80 << 8 | 0x80);
          p += 4;
          q += 4;
        });
  }
  delete[] src;
  delete[] dst;
}

BENCHMARK_F(Int8Unroll, Template1Way)(benchmark::State& state) {
  auto src = new int8_t[n];
  auto dst = new int8_t[n];

  for (auto _ : state) {
    std::fill(src, src + n, 0xAA);
    int8_t *p = src, *q = dst;
    _::Unroll(n, [&p, &q]() {
      *q = *p & int8_t(0x80);
      p++;
      q++;
    });
  }
  delete[] src;
  delete[] dst;
}

BENCHMARK_F(Int32Unroll, Naive)(benchmark::State& state) {
  auto src = new int32_t[n];
  auto dst = new int32_t[n];

  for (auto _ : state) {
    std::fill(src, src + n, 0xAA);
    for (int i = 0; i < n; ++i) {
      dst[i] = src[i] & int32_t(0x80);
    }
  }

  delete[] src;
  delete[] dst;
}

BENCHMARK_F(Int32Unroll, Macro4Way)(benchmark::State& state) {
  auto src = new int32_t[n];
  auto dst = new int32_t[n];

  for (auto _ : state) {
    std::fill(src, src + n, 0xAA);
    int32_t *p = src, *q = dst;
    M_Unroll4(
        n,
        {
          *q = *p & int32_t(0x80);
          p++;
          q++;
        },
        {
          *q = *p & int32_t(0x80);
          p++;
          q++;
          *q = *p & int32_t(0x80);
          p++;
          q++;
        },
        {
          *q = *p & int32_t(0x80);
          p++;
          q++;
          *q = *p & int32_t(0x80);
          p++;
          q++;
          *q = *p & int32_t(0x80);
          p++;
          q++;
          *q = *p & int32_t(0x80);
          p++;
          q++;
        });
  }
  delete[] src;
  delete[] dst;
}

BENCHMARK_F(Int32Unroll, Temaplte4Way)(benchmark::State& state) {
  auto src = new int32_t[n];
  auto dst = new int32_t[n];

  for (auto _ : state) {
    std::fill(src, src + n, 0xAA);
    int32_t *p = src, *q = dst;
    _::Unroll(
        n,
        [&p, &q]() {
          *q = *p & int32_t(0x80);
          p++;
          q++;
        },
        [&p, &q]() {
          *q = *p & int32_t(0x80);
          p++;
          q++;
          *q = *p & int32_t(0x80);
          p++;
          q++;
        },
        [&p, &q]() {
          *q = *p & int32_t(0x80);
          p++;
          q++;
          *q = *p & int32_t(0x80);
          p++;
          q++;
          *q = *p & int32_t(0x80);
          p++;
          q++;
          *q = *p & int32_t(0x80);
          p++;
          q++;
        });
  }
  delete[] src;
  delete[] dst;
}

BENCHMARK_F(Int32Unroll, Template1Way)(benchmark::State& state) {
  auto src = new int32_t[n];
  auto dst = new int32_t[n];

  for (auto _ : state) {
    std::fill(src, src + n, 0xAA);
    int32_t *p = src, *q = dst;
    _::Unroll(n, [&p, &q]() {
      *q = *p & int32_t(0x80);
      p++;
      q++;
    });
  }
  delete[] src;
  delete[] dst;
}

BENCHMARK_MAIN();
