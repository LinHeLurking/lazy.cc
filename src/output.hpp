#ifndef LAZY_PLUS_PLUS_D_OUT_H
#define LAZY_PLUS_PLUS_D_OUT_H

#include <iostream>
#include <iterator>
#include <type_traits>

namespace _ {
#define debug(x) \
  std::cout << "[Line " << __LINE__ << "] " << #x << ": " << (x) << std::endl;

namespace detail {
// https://stackoverflow.com/questions/13830158/check-if-a-variable-type-is-iterable
// To allow ADL with custom begin/end

using std::begin;
using std::end;

template <typename T>
auto is_iterable_impl(int)
    -> decltype(begin(std::declval<T&>()) !=
                    end(std::declval<T&>()),  // begin/end and operator !=
                void(),                       // Handle evil operator ,
                ++std::declval<
                    decltype(begin(std::declval<T&>()))&>(),  // operator
                                                              // ++
                void(*begin(std::declval<T&>())),             // operator*
                std::true_type{});

template <typename T>
std::false_type is_iterable_impl(...);

template <typename T>
using is_iterable = decltype(detail::is_iterable_impl<T>(0));

template <typename T,
          typename std::enable_if_t<!is_iterable<T>::value, int> dummy = 0>
int pprint(const T& val) {
  std::cout << val;
  return 0;
}

template <class Iterable,
          typename std::enable_if_t<
              is_iterable<Iterable>::value &&
                  !std::is_constructible<std::string, Iterable>::value,
              int>
              dummy = 0>
int pprint(const Iterable& iterable) {
  std::cout << "{";
  for (auto it = std::begin(iterable); it != std::end(iterable); ++it) {
    std::cout << *it;
    if (it != std::prev(std::end(iterable))) {
      std::cout << ", ";
    }
  }
  std::cout << "}";
  return 0;
}

template <class Iterable,
          typename std::enable_if_t<
              is_iterable<Iterable>::value &&
                  std::is_constructible<std::string, Iterable>::value,
              int>
              dummy = 0>
int pprint(const Iterable& iterable) {
  std::cout << iterable;
  return 0;
}
}  // namespace detail

template <class... Args>
int PrintLine(Args&&... args) {
  auto dummy = {detail::pprint(args)...};
  std::cout << std::endl;
  return 0;
}

template <class... Args>
int Print(Args&&... args) {
  auto dummy = {detail::pprint(args)...};
  return 0;
}

}  // namespace _

#endif
