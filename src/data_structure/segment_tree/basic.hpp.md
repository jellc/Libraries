---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/algebra/system/monoid.hpp
    title: src/algebra/system/monoid.hpp
  - icon: ':heavy_check_mark:'
    path: src/data_structure/segment_tree/waitings.hpp
    title: src/data_structure/segment_tree/waitings.hpp
  - icon: ':heavy_check_mark:'
    path: src/utils/sfinae.hpp
    title: SFINAE
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/DSL_2_A.test.cpp
    title: test/aizu-online-judge/DSL_2_A.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/point_set_range_composite.test.cpp
    title: test/library-checker/point_set_range_composite.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/static_range_inversions_query.test.cpp
    title: test/library-checker/static_range_inversions_query.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Segment Tree
    links: []
  bundledCode: "#line 2 \"src/data_structure/segment_tree/basic.hpp\"\n\n/*\n * @file\
    \ basic.hpp\n * @brief Segment Tree\n */\n\n#include <cassert>\n#include <queue>\n\
    #include <vector>\n\n#line 2 \"src/algebra/system/monoid.hpp\"\n#include <limits>\n\
    \nnamespace workspace {\ntemplate <class T, class E = T> struct min_monoid {\n\
    \  using value_type = T;\n  static T min, max;\n  T value;\n  min_monoid() : value(max)\
    \ {}\n  min_monoid(const T &value) : value(value) {}\n  operator T() const { return\
    \ value; }\n  min_monoid operator+(const min_monoid &rhs) const {\n    return\
    \ value < rhs.value ? *this : rhs;\n  }\n  min_monoid operator*(const E &rhs)\
    \ const;\n};\n\ntemplate <class T, class E>\nT min_monoid<T, E>::min = std::numeric_limits<T>::min()\
    \ / 2;\ntemplate <class T, class E>\nT min_monoid<T, E>::max = std::numeric_limits<T>::max()\
    \ / 2;\n\ntemplate <class T, class E = T> struct max_monoid : min_monoid<T, E>\
    \ {\n  using base = min_monoid<T, E>;\n  using base::min_monoid;\n  max_monoid()\
    \ : base(base::min) {}\n  max_monoid operator+(const max_monoid &rhs) const {\n\
    \    return !(base::value < rhs.value) ? *this : rhs;\n  }\n  max_monoid operator*(const\
    \ E &rhs) const;\n};\n}\n#line 2 \"src/utils/sfinae.hpp\"\n\n/*\n * @file sfinae.hpp\n\
    \ * @brief SFINAE\n */\n\n#include <cstdint>\n#include <iterator>\n#include <type_traits>\n\
    \nnamespace workspace {\n\ntemplate <class type, template <class> class trait>\n\
    using enable_if_trait_type = typename std::enable_if<trait<type>::value>::type;\n\
    \ntemplate <class Container>\nusing element_type = typename std::decay<decltype(\n\
    \    *std::begin(std::declval<Container&>()))>::type;\n\ntemplate <class T, class\
    \ = std::nullptr_t>\nstruct has_begin : std::false_type {};\n\ntemplate <class\
    \ T>\nstruct has_begin<T, decltype(std::begin(std::declval<T>()), nullptr)>\n\
    \    : std::true_type {};\n\ntemplate <class T, class = int> struct mapped_of\
    \ {\n  using type = element_type<T>;\n};\ntemplate <class T>\nstruct mapped_of<T,\n\
    \                 typename std::pair<int, typename T::mapped_type>::first_type>\
    \ {\n  using type = typename T::mapped_type;\n};\ntemplate <class T> using mapped_type\
    \ = typename mapped_of<T>::type;\n\ntemplate <class T, class = void> struct is_integral_ext\
    \ : std::false_type {};\ntemplate <class T>\nstruct is_integral_ext<\n    T, typename\
    \ std::enable_if<std::is_integral<T>::value>::type>\n    : std::true_type {};\n\
    \n#ifdef __SIZEOF_INT128__\ntemplate <> struct is_integral_ext<__int128_t> : std::true_type\
    \ {};\ntemplate <> struct is_integral_ext<__uint128_t> : std::true_type {};\n\
    #endif\n\n#if __cplusplus >= 201402\ntemplate <class T>\nconstexpr static bool\
    \ is_integral_ext_v = is_integral_ext<T>::value;\n#endif\n\ntemplate <typename\
    \ T, typename = void> struct multiplicable_uint {\n  using type = uint_least32_t;\n\
    };\ntemplate <typename T>\nstruct multiplicable_uint<T, typename std::enable_if<(2\
    \ < sizeof(T))>::type> {\n  using type = uint_least64_t;\n};\n\n#ifdef __SIZEOF_INT128__\n\
    template <typename T>\nstruct multiplicable_uint<T, typename std::enable_if<(4\
    \ < sizeof(T))>::type> {\n  using type = __uint128_t;\n};\n#endif\n\n}  // namespace\
    \ workspace\n#line 2 \"src/data_structure/segment_tree/waitings.hpp\"\n\n#line\
    \ 5 \"src/data_structure/segment_tree/waitings.hpp\"\n\nnamespace workspace {\n\
    \nnamespace internal {\n\nstruct waitings : std::queue<size_t> {\n  waitings(size_t\
    \ n) : in(n) {}\n\n  bool push(size_t index) {\n    assert(index < in.size());\n\
    \    if (in[index]) return false;\n    emplace(index);\n    return (in[index]\
    \ = true);\n  }\n\n  size_t pop() {\n    assert(!empty());\n    auto index = front();\n\
    \    std::queue<size_t>::pop();\n    in[index] = false;\n    return index;\n \
    \ }\n\n private:\n  std::vector<int_least8_t> in;\n};\n\n}  // namespace internal\n\
    \n}  // namespace workspace\n#line 15 \"src/data_structure/segment_tree/basic.hpp\"\
    \n\nnamespace workspace {\n\ntemplate <class Monoid, class Container = std::vector<Monoid>>\n\
    class segment_tree {\n  static_assert(std::is_same<Monoid, mapped_type<Container>>::value);\n\
    \n  static_assert(\n      std::is_same<Monoid, decltype(std::declval<const Monoid>()\
    \ +\n                                    std::declval<const Monoid>())>::value,\n\
    \      \"\\'Monoid\\' has no proper binary \\'operator+\\'.\");\n\n  size_t size_orig,\
    \ height, size_ext;\n  Container data;\n  internal::waitings wait;\n\n  void repair()\
    \ {\n    while (!wait.empty()) {\n      const size_t index = wait.pop() >> 1;\n\
    \      if (index && wait.push(index)) pull(index);\n    }\n  }\n\n  void pull(const\
    \ size_t node) {\n    data[node] = data[node << 1] + data[node << 1 | 1];\n  }\n\
    \n  template <class Pred>\n  static constexpr decltype(std::declval<Pred>()(Monoid{}))\
    \ pass_args(\n      Pred pred, Monoid const &_1, size_t _2) {\n    return pred(_1);\n\
    \  }\n\n  template <class Pred>\n  static constexpr decltype(std::declval<Pred>()(Monoid{},\
    \ size_t{})) pass_args(\n      Pred pred, Monoid const &_1, size_t _2) {\n   \
    \ return pred(_1, _2);\n  }\n\n  template <class Pred>\n  size_t left_partition_subtree(size_t\
    \ node, Monoid mono, size_t step,\n                                Pred pred)\
    \ const {\n    assert(node);\n    while (node < size_ext) {\n      const Monoid\
    \ tmp = data[(node <<= 1) | 1] + mono;\n      if (pass_args(pred, tmp, ((node\
    \ | 1) << --step) ^ size_ext))\n        mono = tmp;\n      else\n        ++node;\n\
    \    }\n    return ++node -= size_ext;\n  }\n\n  template <class Pred>\n  size_t\
    \ right_partition_subtree(size_t node, Monoid mono, size_t step,\n           \
    \                      Pred pred) const {\n    assert(node);\n    while (node\
    \ < size_ext) {\n      const Monoid tmp = mono + data[node <<= 1];\n      if (pass_args(pred,\
    \ tmp, ((node | 1) << --step) ^ size_ext))\n        ++node, mono = tmp;\n    }\n\
    \    return (node -= size_ext) < size_orig ? node : size_orig;\n  }\n\n public:\n\
    \  using value_type = Monoid;\n\n  segment_tree(const size_t n = 0)\n      : size_orig{n},\n\
    \        height(n > 1 ? 32 - __builtin_clz(n - 1) : 0),\n        size_ext{1u <<\
    \ height},\n        data(size_ext << 1),\n        wait(size_ext << 1) {}\n\n \
    \ segment_tree(const size_t n, const Monoid &init) : segment_tree(n) {\n    std::fill(std::next(std::begin(data),\
    \ size_ext), std::end(data), init);\n    for (size_t i{size_ext}; --i;) pull(i);\n\
    \  }\n\n  template <class iter_type, class value_type = typename std::iterator_traits<\n\
    \                                 iter_type>::value_type>\n  segment_tree(iter_type\
    \ first, iter_type last)\n      : size_orig(std::distance(first, last)),\n   \
    \     height(size_orig > 1 ? 32 - __builtin_clz(size_orig - 1) : 0),\n       \
    \ size_ext{1u << height},\n        data(size_ext << 1),\n        wait(size_ext\
    \ << 1) {\n    static_assert(std::is_constructible<Monoid, value_type>::value,\n\
    \                  \"Monoid(iter_type::value_type) is not constructible.\");\n\
    \    for (auto iter{std::next(std::begin(data), size_ext)};\n         iter !=\
    \ std::end(data) && first != last; ++iter, ++first)\n      *iter = Monoid{*first};\n\
    \    for (size_t i{size_ext}; --i;) pull(i);\n  }\n\n  template <class Cont, typename\
    \ = typename Cont::value_type>\n  segment_tree(const Cont &cont)\n      : segment_tree(std::begin(cont),\
    \ std::end(cont)) {}\n\n  /*\n   * @fn size\n   * @return Number of elements.\n\
    \   */\n  size_t size() const { return size_orig; }\n\n  // size_t capacity()\
    \ const { return size_ext; }\n\n  /*\n   * @fn operator[]\n   * @param index Index\
    \ of the element\n   * @return Reference to the element.\n   */\n  Monoid &operator[](size_t\
    \ index) {\n    assert(index < size_orig);\n    wait.push(index |= size_ext);\n\
    \    return data[index];\n  }\n\n  /*\n   * @fn operator[]\n   * @param index\
    \ Index of the element\n   * @return Const reference to the element.\n   */\n\
    \  const Monoid &operator[](size_t index) const {\n    assert(index < size_orig);\n\
    \    return data[index |= size_orig];\n  }\n\n  /*\n   * @fn fold\n   * @param\
    \ first Left end, inclusive\n   * @param last Right end, exclusive\n   * @return\
    \ Sum of elements in the interval.\n   */\n  Monoid fold(size_t first, size_t\
    \ last) {\n    assert(last <= size_orig);\n    repair();\n    Monoid leftval{},\
    \ rightval{};\n    first += size_ext, last += size_ext;\n    while (first < last)\
    \ {\n      if (first & 1) leftval = leftval + data[first++];\n      if (last &\
    \ 1) rightval = data[--last] + rightval;\n      first >>= 1, last >>= 1;\n   \
    \ }\n    return leftval + rightval;\n  }\n\n  /*\n   * @fn fold\n   * @return\
    \ Sum of all elements.\n   */\n  Monoid fold() { return fold(0, size_orig); }\n\
    \n  /*\n   * @fn left_partition\n   * @brief Binary search for the partition point.\n\
    \   * @param right Right fixed end of the interval, exclusive\n   * @param pred\
    \ Predicate in the form of either 'bool(Monoid)' or 'bool(Monoid,\n   * size_t)'\n\
    \   * @return Left end of the extremal interval satisfying the condition,\n  \
    \ * inclusive.\n   */\n  template <class Pred> size_t left_partition(size_t right,\
    \ Pred pred) {\n    assert(right <= size_orig);\n    repair();\n    right += size_ext;\n\
    \    Monoid mono{};\n    for (size_t left{size_ext}, step{}; left != right;\n\
    \         left >>= 1, right >>= 1, ++step) {\n      if ((left & 1) != (right &\
    \ 1)) {\n        const Monoid tmp = data[--right] + mono;\n        if (!pass_args(pred,\
    \ tmp, (right << step) ^ size_ext))\n          return left_partition_subtree(right,\
    \ mono, step, pred);\n        mono = tmp;\n      }\n    }\n    return 0;\n  }\n\
    \n  /*\n   * @fn right_partition\n   * @brief Binary search for the partition\
    \ point.\n   * @param left Left fixed end of the interval, inclusive\n   * @param\
    \ pred Predicate in the form of either 'bool(Monoid)' or 'bool(Monoid,\n   * size_t)'\n\
    \   * @return Right end of the extremal interval satisfying the condition,\n \
    \  * exclusive.\n   */\n  template <class Pred> size_t right_partition(size_t\
    \ left, Pred pred) {\n    assert(left <= size_orig);\n    repair();\n    left\
    \ += size_ext;\n    Monoid mono{};\n    for (size_t right{size_ext << 1}, step{};\
    \ left != right;\n         left >>= 1, right >>= 1, ++step) {\n      if ((left\
    \ & 1) != (right & 1)) {\n        const Monoid tmp = mono + data[left];\n    \
    \    if (!pass_args(pred, tmp, ((left + 1) << step) ^ size_ext))\n          return\
    \ right_partition_subtree(left, mono, step, pred);\n        mono = tmp;\n    \
    \    ++left;\n      }\n    }\n    return size_orig;\n  }\n};\n\n}  // namespace\
    \ workspace\n"
  code: "#pragma once\n\n/*\n * @file basic.hpp\n * @brief Segment Tree\n */\n\n#include\
    \ <cassert>\n#include <queue>\n#include <vector>\n\n#include \"src/algebra/system/monoid.hpp\"\
    \n#include \"src/utils/sfinae.hpp\"\n#include \"waitings.hpp\"\n\nnamespace workspace\
    \ {\n\ntemplate <class Monoid, class Container = std::vector<Monoid>>\nclass segment_tree\
    \ {\n  static_assert(std::is_same<Monoid, mapped_type<Container>>::value);\n\n\
    \  static_assert(\n      std::is_same<Monoid, decltype(std::declval<const Monoid>()\
    \ +\n                                    std::declval<const Monoid>())>::value,\n\
    \      \"\\'Monoid\\' has no proper binary \\'operator+\\'.\");\n\n  size_t size_orig,\
    \ height, size_ext;\n  Container data;\n  internal::waitings wait;\n\n  void repair()\
    \ {\n    while (!wait.empty()) {\n      const size_t index = wait.pop() >> 1;\n\
    \      if (index && wait.push(index)) pull(index);\n    }\n  }\n\n  void pull(const\
    \ size_t node) {\n    data[node] = data[node << 1] + data[node << 1 | 1];\n  }\n\
    \n  template <class Pred>\n  static constexpr decltype(std::declval<Pred>()(Monoid{}))\
    \ pass_args(\n      Pred pred, Monoid const &_1, size_t _2) {\n    return pred(_1);\n\
    \  }\n\n  template <class Pred>\n  static constexpr decltype(std::declval<Pred>()(Monoid{},\
    \ size_t{})) pass_args(\n      Pred pred, Monoid const &_1, size_t _2) {\n   \
    \ return pred(_1, _2);\n  }\n\n  template <class Pred>\n  size_t left_partition_subtree(size_t\
    \ node, Monoid mono, size_t step,\n                                Pred pred)\
    \ const {\n    assert(node);\n    while (node < size_ext) {\n      const Monoid\
    \ tmp = data[(node <<= 1) | 1] + mono;\n      if (pass_args(pred, tmp, ((node\
    \ | 1) << --step) ^ size_ext))\n        mono = tmp;\n      else\n        ++node;\n\
    \    }\n    return ++node -= size_ext;\n  }\n\n  template <class Pred>\n  size_t\
    \ right_partition_subtree(size_t node, Monoid mono, size_t step,\n           \
    \                      Pred pred) const {\n    assert(node);\n    while (node\
    \ < size_ext) {\n      const Monoid tmp = mono + data[node <<= 1];\n      if (pass_args(pred,\
    \ tmp, ((node | 1) << --step) ^ size_ext))\n        ++node, mono = tmp;\n    }\n\
    \    return (node -= size_ext) < size_orig ? node : size_orig;\n  }\n\n public:\n\
    \  using value_type = Monoid;\n\n  segment_tree(const size_t n = 0)\n      : size_orig{n},\n\
    \        height(n > 1 ? 32 - __builtin_clz(n - 1) : 0),\n        size_ext{1u <<\
    \ height},\n        data(size_ext << 1),\n        wait(size_ext << 1) {}\n\n \
    \ segment_tree(const size_t n, const Monoid &init) : segment_tree(n) {\n    std::fill(std::next(std::begin(data),\
    \ size_ext), std::end(data), init);\n    for (size_t i{size_ext}; --i;) pull(i);\n\
    \  }\n\n  template <class iter_type, class value_type = typename std::iterator_traits<\n\
    \                                 iter_type>::value_type>\n  segment_tree(iter_type\
    \ first, iter_type last)\n      : size_orig(std::distance(first, last)),\n   \
    \     height(size_orig > 1 ? 32 - __builtin_clz(size_orig - 1) : 0),\n       \
    \ size_ext{1u << height},\n        data(size_ext << 1),\n        wait(size_ext\
    \ << 1) {\n    static_assert(std::is_constructible<Monoid, value_type>::value,\n\
    \                  \"Monoid(iter_type::value_type) is not constructible.\");\n\
    \    for (auto iter{std::next(std::begin(data), size_ext)};\n         iter !=\
    \ std::end(data) && first != last; ++iter, ++first)\n      *iter = Monoid{*first};\n\
    \    for (size_t i{size_ext}; --i;) pull(i);\n  }\n\n  template <class Cont, typename\
    \ = typename Cont::value_type>\n  segment_tree(const Cont &cont)\n      : segment_tree(std::begin(cont),\
    \ std::end(cont)) {}\n\n  /*\n   * @fn size\n   * @return Number of elements.\n\
    \   */\n  size_t size() const { return size_orig; }\n\n  // size_t capacity()\
    \ const { return size_ext; }\n\n  /*\n   * @fn operator[]\n   * @param index Index\
    \ of the element\n   * @return Reference to the element.\n   */\n  Monoid &operator[](size_t\
    \ index) {\n    assert(index < size_orig);\n    wait.push(index |= size_ext);\n\
    \    return data[index];\n  }\n\n  /*\n   * @fn operator[]\n   * @param index\
    \ Index of the element\n   * @return Const reference to the element.\n   */\n\
    \  const Monoid &operator[](size_t index) const {\n    assert(index < size_orig);\n\
    \    return data[index |= size_orig];\n  }\n\n  /*\n   * @fn fold\n   * @param\
    \ first Left end, inclusive\n   * @param last Right end, exclusive\n   * @return\
    \ Sum of elements in the interval.\n   */\n  Monoid fold(size_t first, size_t\
    \ last) {\n    assert(last <= size_orig);\n    repair();\n    Monoid leftval{},\
    \ rightval{};\n    first += size_ext, last += size_ext;\n    while (first < last)\
    \ {\n      if (first & 1) leftval = leftval + data[first++];\n      if (last &\
    \ 1) rightval = data[--last] + rightval;\n      first >>= 1, last >>= 1;\n   \
    \ }\n    return leftval + rightval;\n  }\n\n  /*\n   * @fn fold\n   * @return\
    \ Sum of all elements.\n   */\n  Monoid fold() { return fold(0, size_orig); }\n\
    \n  /*\n   * @fn left_partition\n   * @brief Binary search for the partition point.\n\
    \   * @param right Right fixed end of the interval, exclusive\n   * @param pred\
    \ Predicate in the form of either 'bool(Monoid)' or 'bool(Monoid,\n   * size_t)'\n\
    \   * @return Left end of the extremal interval satisfying the condition,\n  \
    \ * inclusive.\n   */\n  template <class Pred> size_t left_partition(size_t right,\
    \ Pred pred) {\n    assert(right <= size_orig);\n    repair();\n    right += size_ext;\n\
    \    Monoid mono{};\n    for (size_t left{size_ext}, step{}; left != right;\n\
    \         left >>= 1, right >>= 1, ++step) {\n      if ((left & 1) != (right &\
    \ 1)) {\n        const Monoid tmp = data[--right] + mono;\n        if (!pass_args(pred,\
    \ tmp, (right << step) ^ size_ext))\n          return left_partition_subtree(right,\
    \ mono, step, pred);\n        mono = tmp;\n      }\n    }\n    return 0;\n  }\n\
    \n  /*\n   * @fn right_partition\n   * @brief Binary search for the partition\
    \ point.\n   * @param left Left fixed end of the interval, inclusive\n   * @param\
    \ pred Predicate in the form of either 'bool(Monoid)' or 'bool(Monoid,\n   * size_t)'\n\
    \   * @return Right end of the extremal interval satisfying the condition,\n \
    \  * exclusive.\n   */\n  template <class Pred> size_t right_partition(size_t\
    \ left, Pred pred) {\n    assert(left <= size_orig);\n    repair();\n    left\
    \ += size_ext;\n    Monoid mono{};\n    for (size_t right{size_ext << 1}, step{};\
    \ left != right;\n         left >>= 1, right >>= 1, ++step) {\n      if ((left\
    \ & 1) != (right & 1)) {\n        const Monoid tmp = mono + data[left];\n    \
    \    if (!pass_args(pred, tmp, ((left + 1) << step) ^ size_ext))\n          return\
    \ right_partition_subtree(left, mono, step, pred);\n        mono = tmp;\n    \
    \    ++left;\n      }\n    }\n    return size_orig;\n  }\n};\n\n}  // namespace\
    \ workspace\n"
  dependsOn:
  - src/algebra/system/monoid.hpp
  - src/utils/sfinae.hpp
  - src/data_structure/segment_tree/waitings.hpp
  isVerificationFile: false
  path: src/data_structure/segment_tree/basic.hpp
  requiredBy: []
  timestamp: '2020-12-01 16:34:20+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/library-checker/point_set_range_composite.test.cpp
  - test/library-checker/static_range_inversions_query.test.cpp
  - test/aizu-online-judge/DSL_2_A.test.cpp
documentation_of: src/data_structure/segment_tree/basic.hpp
layout: document
redirect_from:
- /library/src/data_structure/segment_tree/basic.hpp
- /library/src/data_structure/segment_tree/basic.hpp.html
title: Segment Tree
---