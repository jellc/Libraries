---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/utils/iterator/category.hpp
    title: Iterator Category
  - icon: ':heavy_check_mark:'
    path: src/utils/iterator/reverse.hpp
    title: Reverse Iterator
  - icon: ':warning:'
    path: src/utils/py-like/range.hpp
    title: Range
  - icon: ':warning:'
    path: src/utils/py-like/reversed.hpp
    title: Reversed
  - icon: ':heavy_check_mark:'
    path: src/utils/py-like/zip.hpp
    title: Zip
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Enumerate
    links: []
  bundledCode: "#line 2 \"src/utils/py-like/enumerate.hpp\"\n\n/*\n * @file enumerate.hpp\n\
    \ * @brief Enumerate\n */\n\n#line 2 \"src/utils/py-like/range.hpp\"\n\n/**\n\
    \ * @file range.hpp\n * @brief Range\n */\n\n#include <iterator>\n\n#line 2 \"\
    src/utils/iterator/reverse.hpp\"\n\n/*\n * @file reverse_iterator.hpp\n * @brief\
    \ Reverse Iterator\n */\n\n#if __cplusplus >= 201703L\n\n#line 11 \"src/utils/iterator/reverse.hpp\"\
    \n#include <optional>\n\nnamespace workspace {\n\n/*\n * @class reverse_iterator\n\
    \ * @brief Wrapper class for `std::reverse_iterator`.\n * @see http://gcc.gnu.org/PR51823\n\
    \ */\ntemplate <class Iterator>\nclass reverse_iterator : public std::reverse_iterator<Iterator>\
    \ {\n  using base_std = std::reverse_iterator<Iterator>;\n  std::optional<typename\
    \ base_std::value_type> deref;\n\n public:\n  using base_std::reverse_iterator;\n\
    \n  constexpr typename base_std::reference operator*() noexcept {\n    if (!deref)\
    \ {\n      Iterator tmp = base_std::current;\n      deref = *--tmp;\n    }\n \
    \   return deref.value();\n  }\n\n  constexpr reverse_iterator &operator++() noexcept\
    \ {\n    base_std::operator++();\n    deref.reset();\n    return *this;\n  }\n\
    \  constexpr reverse_iterator &operator--() noexcept {\n    base_std::operator++();\n\
    \    deref.reset();\n    return *this;\n  }\n  constexpr reverse_iterator operator++(int)\
    \ noexcept {\n    base_std::operator++();\n    deref.reset();\n    return *this;\n\
    \  }\n  constexpr reverse_iterator operator--(int) noexcept {\n    base_std::operator++();\n\
    \    deref.reset();\n    return *this;\n  }\n};\n\n}  // namespace workspace\n\
    \n#endif\n#line 2 \"src/utils/py-like/reversed.hpp\"\n\n/**\n * @file reversed.hpp\n\
    \ * @brief Reversed\n */\n\n#include <initializer_list>\n#line 10 \"src/utils/py-like/reversed.hpp\"\
    \n\nnamespace workspace {\n\nnamespace internal {\n\ntemplate <class Container>\
    \ class reversed {\n  Container cont;\n\n public:\n  constexpr reversed(Container\
    \ &&cont) : cont(cont) {}\n\n  constexpr auto begin() { return std::rbegin(cont);\
    \ }\n  constexpr auto end() { return std::rend(cont); }\n};\n\n}  // namespace\
    \ internal\n\ntemplate <class Container> constexpr auto reversed(Container &&cont)\
    \ noexcept {\n  return internal::reversed<Container>{std::forward<Container>(cont)};\n\
    }\n\ntemplate <class Tp>\nconstexpr auto reversed(std::initializer_list<Tp> &&cont)\
    \ noexcept {\n  return internal::reversed<std::initializer_list<Tp>>{\n      std::forward<std::initializer_list<Tp>>(cont)};\n\
    }\n\n}  // namespace workspace\n#line 12 \"src/utils/py-like/range.hpp\"\n\n#if\
    \ __cplusplus >= 201703L\n\nnamespace workspace {\n\ntemplate <class Index> class\
    \ range {\n  Index first, last;\n\n public:\n  class iterator {\n    Index current;\n\
    \n   public:\n    using difference_type = std::ptrdiff_t;\n    using value_type\
    \ = Index;\n    using reference = typename std::add_const<Index>::type &;\n  \
    \  using pointer = iterator;\n    using iterator_category = std::bidirectional_iterator_tag;\n\
    \n    constexpr iterator(Index const &__i = Index()) noexcept : current(__i) {}\n\
    \n    constexpr bool operator==(iterator const &rhs) const noexcept {\n      return\
    \ current == rhs.current;\n    }\n    constexpr bool operator!=(iterator const\
    \ &rhs) const noexcept {\n      return current != rhs.current;\n    }\n\n    constexpr\
    \ iterator &operator++() noexcept {\n      ++current;\n      return *this;\n \
    \   }\n    constexpr iterator &operator--() noexcept {\n      --current;\n   \
    \   return *this;\n    }\n\n    constexpr reference operator*() const noexcept\
    \ { return current; }\n  };\n\n  constexpr range(Index first, Index last) noexcept\n\
    \      : first(first), last(last) {}\n  constexpr range(Index last) noexcept :\
    \ first(), last(last) {}\n\n  constexpr iterator begin() const noexcept { return\
    \ iterator{first}; }\n  constexpr iterator end() const noexcept { return iterator{last};\
    \ }\n\n  constexpr reverse_iterator<iterator> rbegin() const noexcept {\n    return\
    \ reverse_iterator<iterator>(end());\n  }\n  constexpr reverse_iterator<iterator>\
    \ rend() const noexcept {\n    return reverse_iterator<iterator>(begin());\n \
    \ }\n};\n\ntemplate <class... Args> constexpr auto rrange(Args &&... args) noexcept\
    \ {\n  return internal::reversed(range(std::forward<Args>(args)...));\n}\n\n}\
    \  // namespace workspace\n\n#endif\n#line 2 \"src/utils/py-like/zip.hpp\"\n\n\
    /**\n * @file zip.hpp\n * @brief Zip\n */\n\n#include <cstddef>\n#include <tuple>\n\
    #include <vector>\n\n#line 2 \"src/utils/iterator/category.hpp\"\n\n/*\n * @file\
    \ category.hpp\n * @brief Iterator Category\n */\n\n#line 10 \"src/utils/iterator/category.hpp\"\
    \n\nnamespace workspace {\n\n/*\n * @tparam Tuple Tuple of iterator types\n */\n\
    template <class Tuple, size_t N = std::tuple_size<Tuple>::value - 1>\nstruct common_iterator_category\
    \ {\n  using type = typename std::common_type<\n      typename common_iterator_category<Tuple,\
    \ N - 1>::type,\n      typename std::iterator_traits<typename std::tuple_element<\n\
    \          N, Tuple>::type>::iterator_category>::type;\n};\n\ntemplate <class\
    \ Tuple> struct common_iterator_category<Tuple, 0> {\n  using type = typename\
    \ std::iterator_traits<\n      typename std::tuple_element<0, Tuple>::type>::iterator_category;\n\
    };\n\n}  // namespace workspace\n#line 14 \"src/utils/py-like/zip.hpp\"\n\n#if\
    \ __cplusplus >= 201703L\n\nnamespace workspace {\n\nnamespace internal {\n\n\
    template <class> struct zipped_iterator;\n\ntemplate <class...> struct zipped_iterator_tuple;\n\
    \ntemplate <class... Args> class zipped {\n  using ref_tuple = std::tuple<Args...>;\n\
    \  ref_tuple args;\n\n  template <size_t N = 0> constexpr auto begin_cat() const\
    \ noexcept {\n    if constexpr (N != std::tuple_size<ref_tuple>::value) {\n  \
    \    return std::tuple_cat(std::tuple(std::begin(std::get<N>(args))),\n      \
    \                      begin_cat<N + 1>());\n    } else\n      return std::tuple<>();\n\
    \  }\n\n  template <size_t N = 0> constexpr auto end_cat() const noexcept {\n\
    \    if constexpr (N != std::tuple_size<ref_tuple>::value) {\n      return std::tuple_cat(std::tuple(std::end(std::get<N>(args))),\n\
    \                            end_cat<N + 1>());\n    } else\n      return std::tuple<>();\n\
    \  }\n\n public:\n  constexpr zipped(Args &&... args) noexcept : args(args...)\
    \ {}\n\n  class iterator {\n    using base_tuple = typename zipped_iterator_tuple<Args...>::type;\n\
    \n   public:\n    using iterator_category =\n        typename common_iterator_category<base_tuple>::type;\n\
    \    using difference_type = std::ptrdiff_t;\n    using value_type = zipped_iterator<base_tuple>;\n\
    \    using reference = zipped_iterator<base_tuple> &;\n    using pointer = iterator;\n\
    \n   protected:\n    value_type current;\n\n    template <size_t N = 0>\n    constexpr\
    \ bool equal(const iterator &rhs) const noexcept {\n      if constexpr (N != std::tuple_size<base_tuple>::value)\
    \ {\n        return std::get<N>(current) == std::get<N>(rhs.current) ||\n    \
    \           equal<N + 1>(rhs);\n      } else\n        return false;\n    }\n\n\
    \    template <size_t N = 0> constexpr void increment() noexcept {\n      if constexpr\
    \ (N != std::tuple_size<base_tuple>::value) {\n        ++std::get<N>(current);\n\
    \        increment<N + 1>();\n      }\n    }\n\n    template <size_t N = 0> constexpr\
    \ void decrement() noexcept {\n      if constexpr (N != std::tuple_size<base_tuple>::value)\
    \ {\n        --std::get<N>(current);\n        decrement<N + 1>();\n      }\n \
    \   }\n\n    template <size_t N = 0>\n    constexpr void advance(difference_type\
    \ __d) noexcept {\n      if constexpr (N != std::tuple_size<base_tuple>::value)\
    \ {\n        std::get<N>(current) += __d;\n        advance<N + 1>(__d);\n    \
    \  }\n    }\n\n   public:\n    constexpr iterator() noexcept = default;\n    constexpr\
    \ iterator(base_tuple const &current) noexcept : current(current) {}\n\n    constexpr\
    \ bool operator==(const iterator &rhs) const noexcept {\n      return equal(rhs);\n\
    \    }\n    constexpr bool operator!=(const iterator &rhs) const noexcept {\n\
    \      return !equal(rhs);\n    }\n\n    constexpr iterator &operator++() noexcept\
    \ {\n      increment();\n      return *this;\n    }\n    constexpr iterator &operator--()\
    \ noexcept {\n      decrement();\n      return *this;\n    }\n\n    constexpr\
    \ bool operator<(const iterator &rhs) const noexcept {\n      return std::get<0>(current)\
    \ < std::get<0>(rhs.current);\n    }\n\n    constexpr bool operator<=(const iterator\
    \ &rhs) const noexcept {\n      return std::get<0>(current) <= std::get<0>(rhs.current);\n\
    \    }\n\n    constexpr iterator &operator+=(difference_type __d) noexcept {\n\
    \      advance(__d);\n      return *this;\n    }\n\n    constexpr iterator &operator-=(difference_type\
    \ __d) noexcept {\n      advance(-__d);\n      return *this;\n    }\n\n    constexpr\
    \ iterator operator+(difference_type __d) const noexcept {\n      return iterator{*this}\
    \ += __d;\n    }\n\n    constexpr iterator operator-(difference_type __d) const\
    \ noexcept {\n      return iterator{*this} -= __d;\n    }\n\n    constexpr difference_type\
    \ operator-(const iterator &rhs) const noexcept {\n      return std::get<0>(current)\
    \ - std::get<0>(rhs.current);\n    }\n\n    constexpr reference operator*() noexcept\
    \ { return current; }\n  };\n\n  constexpr iterator begin() const noexcept { return\
    \ iterator{begin_cat()}; }\n  constexpr iterator end() const noexcept { return\
    \ iterator{end_cat()}; }\n\n  constexpr reverse_iterator<iterator> rbegin() const\
    \ noexcept {\n    return reverse_iterator<iterator>{end()};\n  }\n  constexpr\
    \ reverse_iterator<iterator> rend() const noexcept {\n    return reverse_iterator<iterator>{begin()};\n\
    \  }\n};\n\ntemplate <class Tp, class... Args> struct zipped_iterator_tuple<Tp,\
    \ Args...> {\n  using type = decltype(std::tuple_cat(\n      std::declval<std::tuple<decltype(std::begin(std::declval<Tp>()))>>(),\n\
    \      std::declval<typename zipped_iterator_tuple<Args...>::type>()));\n};\n\n\
    template <> struct zipped_iterator_tuple<> { using type = std::tuple<>; };\n\n\
    template <class Iter_tuple> struct zipped_iterator : Iter_tuple {\n  constexpr\
    \ zipped_iterator(Iter_tuple const &__t) noexcept\n      : Iter_tuple::tuple(__t)\
    \ {}\n\n  constexpr zipped_iterator(zipped_iterator const &__t) = default;\n\n\
    \  constexpr zipped_iterator &operator=(zipped_iterator const &__t) = default;\n\
    \n  // Avoid move initialization.\n  constexpr zipped_iterator(zipped_iterator\
    \ &&__t)\n      : zipped_iterator(static_cast<zipped_iterator const &>(__t)) {}\n\
    \n  // Avoid move assignment.\n  zipped_iterator &operator=(zipped_iterator &&__t)\
    \ {\n    return operator=(static_cast<zipped_iterator const &>(__t));\n  }\n\n\
    \  template <size_t N>\n  friend constexpr auto &get(zipped_iterator<Iter_tuple>\
    \ const &__z) noexcept {\n    return *std::get<N>(__z);\n  }\n\n  template <size_t\
    \ N>\n  friend constexpr auto get(zipped_iterator<Iter_tuple> &&__z) noexcept\
    \ {\n    return *std::get<N>(__z);\n  }\n};\n\n}  // namespace internal\n\n} \
    \ // namespace workspace\n\nnamespace std {\n\ntemplate <size_t N, class Iter_tuple>\n\
    struct tuple_element<N, workspace::internal::zipped_iterator<Iter_tuple>> {\n\
    \  using type = typename remove_reference<typename iterator_traits<\n      typename\
    \ tuple_element<N, Iter_tuple>::type>::reference>::type;\n};\n\ntemplate <class\
    \ Iter_tuple>\nstruct tuple_size<workspace::internal::zipped_iterator<Iter_tuple>>\n\
    \    : tuple_size<Iter_tuple> {};\n\n}  // namespace std\n\nnamespace workspace\
    \ {\n\ntemplate <class... Args> constexpr auto zip(Args &&... args) noexcept {\n\
    \  return internal::zipped<Args...>(std::forward<Args>(args)...);\n}\n\ntemplate\
    \ <class... Args>\nconstexpr auto zip(std::initializer_list<Args> const &... args)\
    \ noexcept {\n  return internal::zipped<const std::initializer_list<Args>...>(args...);\n\
    }\n\n}  // namespace workspace\n\n#endif\n#line 10 \"src/utils/py-like/enumerate.hpp\"\
    \n\n#if __cplusplus >= 201703L\n\nnamespace workspace {\n\nconstexpr size_t min_size()\
    \ noexcept { return SIZE_MAX; }\n\ntemplate <class Container, class... Args>\n\
    constexpr size_t min_size(Container const &cont, Args &&... args) noexcept {\n\
    \  return std::min(std::size(cont), min_size(std::forward<Args>(args)...));\n\
    }\n\ntemplate <class... Args> constexpr auto enumerate(Args &&... args) noexcept\
    \ {\n  return zip(range(min_size(args...)), std::forward<Args>(args)...);\n}\n\
    \ntemplate <class... Args>\nconstexpr auto enumerate(std::initializer_list<Args>\
    \ const &... args) noexcept {\n  return zip(range(min_size(args...)), std::vector(args)...);\n\
    }\n\n}  // namespace workspace\n\n#endif\n"
  code: "#pragma once\n\n/*\n * @file enumerate.hpp\n * @brief Enumerate\n */\n\n\
    #include \"range.hpp\"\n#include \"zip.hpp\"\n\n#if __cplusplus >= 201703L\n\n\
    namespace workspace {\n\nconstexpr size_t min_size() noexcept { return SIZE_MAX;\
    \ }\n\ntemplate <class Container, class... Args>\nconstexpr size_t min_size(Container\
    \ const &cont, Args &&... args) noexcept {\n  return std::min(std::size(cont),\
    \ min_size(std::forward<Args>(args)...));\n}\n\ntemplate <class... Args> constexpr\
    \ auto enumerate(Args &&... args) noexcept {\n  return zip(range(min_size(args...)),\
    \ std::forward<Args>(args)...);\n}\n\ntemplate <class... Args>\nconstexpr auto\
    \ enumerate(std::initializer_list<Args> const &... args) noexcept {\n  return\
    \ zip(range(min_size(args...)), std::vector(args)...);\n}\n\n}  // namespace workspace\n\
    \n#endif\n"
  dependsOn:
  - src/utils/py-like/range.hpp
  - src/utils/iterator/reverse.hpp
  - src/utils/py-like/reversed.hpp
  - src/utils/py-like/zip.hpp
  - src/utils/iterator/category.hpp
  isVerificationFile: false
  path: src/utils/py-like/enumerate.hpp
  requiredBy: []
  timestamp: '2021-01-08 15:34:42+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/utils/py-like/enumerate.hpp
layout: document
redirect_from:
- /library/src/utils/py-like/enumerate.hpp
- /library/src/utils/py-like/enumerate.hpp.html
title: Enumerate
---