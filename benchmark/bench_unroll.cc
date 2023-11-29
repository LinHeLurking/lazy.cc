#include <benchmark/benchmark.h>

#include "lazy++.hpp"

constexpr size_t n = 100000;

static void BM_NaiveLoop(benchmark::State& state) {
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
BENCHMARK(BM_NaiveLoop);

static void BM_UnrollLoop_Macro(benchmark::State& state) {
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
BENCHMARK(BM_UnrollLoop_Macro);

static void BM_UnrollLoop_Template(benchmark::State& state) {
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
BENCHMARK(BM_UnrollLoop_Template);

BENCHMARK_MAIN();
