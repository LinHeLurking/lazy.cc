#ifndef LAZY_EXAMPLE_FORCE_INLINE_HPP
#define LAZY_EXAMPLE_FORCE_INLINE_HPP

#ifdef _MSC_VER
#define FORCE_INLINE __forceinline
#elif defined(__GNUC__)
#define FORCE_INLINE inline __attribute__((__always_inline__))
#elif defined(__CLANG__)
#if __has_attribute(__always_inline__)
#define FORCE_INLINE inline __attribute__((__always_inline__))
#else
#define FORCE_INLINE inline
#endif
#else
#define FORCE_INLINE inline
#endif
#else
#define FORCE_INLINE inline

#endif  // LAZY_EXAMPLE_FORCE_INLINE_HPP
