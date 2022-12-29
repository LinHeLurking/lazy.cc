#ifndef LAZY_PLUS_PLUS_D_OUT_H
#define LAZY_PLUS_PLUS_D_OUT_H

#include <exception>
#include <iostream>
#include <iterator>
#include <type_traits>

namespace _ {
namespace detail {
// https://stackoverflow.com/questions/13830158/check-if-a-variable-type-is-iterable
// To allow ADL with custom begin/end

using std::begin;
using std::end;

template <class T>
auto is_iterable_impl(int)
    -> decltype(begin(std::declval<T&>()) !=
                    end(std::declval<T&>()),  // begin/end and operator !=
                void(),                       // Handle evil operator ,
                ++std::declval<
                    decltype(begin(std::declval<T&>()))&>(),  // operator
                                                              // ++
                void(*begin(std::declval<T&>())),             // operator*
                std::true_type{});

template <class T>
std::false_type is_iterable_impl(...);

template <class T>
using is_iterable = decltype(detail::is_iterable_impl<T>(0));

template <class T>
inline constexpr auto is_iterable_v = is_iterable<T>::value;

template <class T>
using is_string_like = std::is_constructible<std::string, T>;

template <class T>
inline constexpr auto is_string_like_v = is_string_like<T>::value;

template <class T,
          std::enable_if_t<!is_iterable_v<T> || is_string_like_v<T>, int> = 0>
int pprint(const T& val) {
  std::cout << val;
  return 0;
}

template <class Iterable,
          std::enable_if_t<
              is_iterable_v<Iterable> && !is_string_like_v<Iterable>, int> = 0>
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
}  // namespace detail

template <class... Args>
int Print(Args&&... args) {
  auto dummy = {detail::pprint(args)...};
  return 0;
}

template <class... Args>
int PrintLine(Args&&... args) {
  Print(args...);
  std::cout << std::endl;
  return 0;
}

}  // namespace _

#endif
