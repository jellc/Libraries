---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/algebra/system/monoid.hpp
    title: src/algebra/system/monoid.hpp
  - icon: ':heavy_check_mark:'
    path: src/data_structure/segment_tree/waitings.hpp
    title: src/data_structure/segment_tree/waitings.hpp
  - icon: ':question:'
    path: src/utils/sfinae.hpp
    title: SFINAE
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/2450.test.cpp
    title: test/aizu-online-judge/2450.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/range_affine_range_sum.test.cpp
    title: test/library-checker/range_affine_range_sum.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Lazy Segment Tree
    links: []
  bundledCode: "#line 2 \"src/data_structure/segment_tree/lazy.hpp\"\n\n/*\n * @file\
    \ lazy.hpp\n * @brief Lazy Segment Tree\n */\n\n#include <cassert>\n#include <queue>\n\
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
    \n#ifdef __SIZEOF_INT128__\n#define __INT128_DEFINED__ 1\n#else\n#define __INT128_DEFINED__\
    \ 0\n#endif\n\nnamespace std {\n\n#if __INT128_DEFINED__\n\ntemplate <> struct\
    \ make_signed<__uint128_t> { using type = __int128_t; };\ntemplate <> struct make_signed<__int128_t>\
    \ { using type = __int128_t; };\n\ntemplate <> struct make_unsigned<__uint128_t>\
    \ { using type = __uint128_t; };\ntemplate <> struct make_unsigned<__int128_t>\
    \ { using type = __uint128_t; };\n\n#endif\n\n}  // namespace std\n\nnamespace\
    \ workspace {\n\ntemplate <class type, template <class> class trait>\nusing enable_if_trait_type\
    \ = typename std::enable_if<trait<type>::value>::type;\n\ntemplate <class Container>\n\
    using element_type = typename std::decay<decltype(\n    *std::begin(std::declval<Container&>()))>::type;\n\
    \ntemplate <class T, class = std::nullptr_t>\nstruct has_begin : std::false_type\
    \ {};\n\ntemplate <class T>\nstruct has_begin<T, decltype(std::begin(std::declval<T>()),\
    \ nullptr)>\n    : std::true_type {};\n\ntemplate <class T, class = int> struct\
    \ mapped_of {\n  using type = element_type<T>;\n};\ntemplate <class T>\nstruct\
    \ mapped_of<T,\n                 typename std::pair<int, typename T::mapped_type>::first_type>\
    \ {\n  using type = typename T::mapped_type;\n};\ntemplate <class T> using mapped_type\
    \ = typename mapped_of<T>::type;\n\ntemplate <class T, class = void> struct is_integral_ext\
    \ : std::false_type {};\ntemplate <class T>\nstruct is_integral_ext<\n    T, typename\
    \ std::enable_if<std::is_integral<T>::value>::type>\n    : std::true_type {};\n\
    \n#if __INT128_DEFINED__\n\ntemplate <> struct is_integral_ext<__int128_t> : std::true_type\
    \ {};\ntemplate <> struct is_integral_ext<__uint128_t> : std::true_type {};\n\n\
    #endif\n\n#if __cplusplus >= 201402\n\ntemplate <class T>\nconstexpr static bool\
    \ is_integral_ext_v = is_integral_ext<T>::value;\n\n#endif\n\ntemplate <typename\
    \ T, typename = void> struct multiplicable_uint {\n  using type = uint_least32_t;\n\
    };\ntemplate <typename T>\nstruct multiplicable_uint<\n    T, typename std::enable_if<(2\
    \ < sizeof(T)) &&\n                               (!__INT128_DEFINED__ || sizeof(T)\
    \ <= 4)>::type> {\n  using type = uint_least64_t;\n};\n\n#if __INT128_DEFINED__\n\
    \ntemplate <typename T>\nstruct multiplicable_uint<T, typename std::enable_if<(4\
    \ < sizeof(T))>::type> {\n  using type = __uint128_t;\n};\n\n#endif\n\n}  // namespace\
    \ workspace\n#line 2 \"src/data_structure/segment_tree/waitings.hpp\"\n\n#line\
    \ 5 \"src/data_structure/segment_tree/waitings.hpp\"\n\nnamespace workspace {\n\
    \nnamespace internal {\n\nstruct waitings : std::queue<size_t> {\n  waitings(size_t\
    \ n) : in(n) {}\n\n  bool push(size_t index) {\n    // assert(index < in.size());\n\
    \    if (in[index]) return false;\n    emplace(index);\n    return (in[index]\
    \ = true);\n  }\n\n  size_t pop() {\n    // assert(!empty());\n    auto index\
    \ = front();\n    std::queue<size_t>::pop();\n    in[index] = false;\n    return\
    \ index;\n  }\n\n private:\n  std::vector<int_least8_t> in;\n};\n\n}  // namespace\
    \ internal\n\n}  // namespace workspace\n#line 15 \"src/data_structure/segment_tree/lazy.hpp\"\
    \n\nnamespace workspace {\n\ntemplate <class Monoid, class Endomorphism,\n   \
    \       class Monoid_container = std::vector<Monoid>,\n          class Endomorphism_container\
    \ = std::vector<Endomorphism>>\nclass lazy_segment_tree {\n  static_assert(std::is_same<Monoid,\
    \ mapped_type<Monoid_container>>::value);\n\n  static_assert(\n      std::is_same<Endomorphism,\
    \ mapped_type<Endomorphism_container>>::value);\n\n  static_assert(std::is_same<Monoid,\
    \ decltype(std::declval<Monoid>() +\n                                        \
    \      std::declval<Monoid>())>::value,\n                \"\\'Monoid\\' has no\
    \ proper binary \\'operator+\\'.\");\n\n  static_assert(\n      std::is_same<Endomorphism,\
    \ decltype(std::declval<Endomorphism>() *\n                                  \
    \        std::declval<Endomorphism>())>::value,\n      \"\\'Endomorphism\\' has\
    \ no proper binary operator*.\");\n\n  static_assert(\n      std::is_same<Monoid,\
    \ decltype(std::declval<Monoid>() *\n                                    std::declval<Endomorphism>())>::value,\n\
    \      \"\\'Endomorphism\\' is not applicable to \\'Monoid\\'.\");\n\n  size_t\
    \ size_orig, height, size_ext;\n  Monoid_container data;\n  Endomorphism_container\
    \ lazy;\n  internal::waitings wait;\n\n  void repair() {\n    while (!wait.empty())\
    \ {\n      const size_t index = wait.pop() >> 1;\n      if (index && wait.push(index))\
    \ pull(index);\n    }\n  }\n\n  void apply(size_t node, const Endomorphism &endo)\
    \ {\n    data[node] = data[node] * endo;\n    if (node < size_ext) lazy[node]\
    \ = lazy[node] * endo;\n  }\n\n  void push(size_t node) {\n    apply(node << 1,\
    \ lazy[node]);\n    apply(node << 1 | 1, lazy[node]);\n    lazy[node] = Endomorphism{};\n\
    \  }\n\n  void pull(size_t node) { data[node] = data[node << 1] + data[node <<\
    \ 1 | 1]; }\n\n  template <class Pred>\n  static constexpr decltype(std::declval<Pred>()(Monoid{}))\
    \ pass_args(\n      Pred pred, Monoid const &_1, [[maybe_unused]] size_t _2) {\n\
    \    return pred(_1);\n  }\n\n  template <class Pred>\n  static constexpr decltype(std::declval<Pred>()(Monoid{},\
    \ size_t{})) pass_args(\n      Pred pred, Monoid const &_1, size_t _2) {\n   \
    \ return pred(_1, _2);\n  }\n\n  template <class Pred>\n  size_t left_partition_subtree(size_t\
    \ node, Monoid mono, size_t step,\n                                Pred pred)\
    \ {\n    assert(node);\n    while (node < size_ext) {\n      push(node);\n   \
    \   const Monoid tmp = data[(node <<= 1) | 1] + mono;\n      if (pass_args(pred,\
    \ tmp, ((node | 1) << --step) ^ size_ext))\n        mono = tmp;\n      else\n\
    \        ++node;\n    }\n    return ++node -= size_ext;\n  }\n\n  template <class\
    \ Pred>\n  size_t right_partition_subtree(size_t node, Monoid mono, size_t step,\n\
    \                                 Pred pred) {\n    assert(node);\n    while (node\
    \ < size_ext) {\n      push(node);\n      const Monoid tmp = mono + data[node\
    \ <<= 1];\n      if (pass_args(pred, tmp, ((node | 1) << --step) ^ size_ext))\n\
    \        ++node, mono = tmp;\n    }\n    return (node -= size_ext) < size_orig\
    \ ? node : size_orig;\n  }\n\n public:\n  class iterator {\n    lazy_segment_tree\
    \ *__p;\n    size_t __i;\n\n   public:\n    using difference_type = typename std::make_signed<size_t>::type;\n\
    \    using value_type = Monoid;\n    using reference = Monoid &;\n    using pointer\
    \ = iterator;\n    using iterator_category = std::random_access_iterator_tag;\n\
    \n    /**\n     * @brief Construct a new iterator object\n     *\n     */\n  \
    \  iterator() = default;\n\n    /**\n     * @brief Construct a new iterator object\n\
    \     *\n     * @param __p Pointer to a segment tree object\n     * @param __i\
    \ Index\n     */\n    iterator(lazy_segment_tree *__p, size_t __i) : __p(__p),\
    \ __i(__i) {}\n\n    bool operator==(iterator const &rhs) const {\n      return\
    \ __p == rhs.__p && __i == rhs.__i;\n    }\n    bool operator!=(iterator const\
    \ &rhs) const { return !operator==(rhs); }\n\n    bool operator<(iterator const\
    \ &rhs) const { return __i < rhs.__i; }\n    bool operator>(iterator const &rhs)\
    \ const { return __i > rhs.__i; }\n    bool operator<=(iterator const &rhs) const\
    \ { return __i <= rhs.__i; }\n    bool operator>=(iterator const &rhs) const {\
    \ return __i >= rhs.__i; }\n\n    iterator &operator++() { return ++__i, *this;\
    \ }\n    iterator &operator--() { return --__i, *this; }\n\n    difference_type\
    \ operator-(iterator const &rhs) const {\n      return __i - rhs.__i;\n    }\n\
    \n    /**\n     * @brief\n     *\n     * @return reference\n     */\n    reference\
    \ operator*() const { return __p->operator[](__i); }\n  };\n\n  using value_type\
    \ = typename iterator::value_type;\n  using reference = typename iterator::reference;\n\
    \n  iterator begin() { return {this, 0}; }\n  iterator end() { return {this, size_orig};\
    \ }\n\n  auto rbegin() { return std::make_reverse_iterator(end()); }\n  auto rend()\
    \ { return std::make_reverse_iterator(begin()); }\n\n  lazy_segment_tree(size_t\
    \ n = 0)\n      : size_orig{n},\n        height(n > 1 ? 32 - __builtin_clz(n -\
    \ 1) : 0),\n        size_ext{1u << height},\n        data(size_ext << 1),\n  \
    \      lazy(size_ext),\n        wait(size_ext << 1) {}\n\n  lazy_segment_tree(size_t\
    \ n, const Monoid &init) : lazy_segment_tree(n) {\n    std::fill(std::next(std::begin(data),\
    \ size_ext), std::end(data), init);\n    for (size_t i{size_ext}; --i;) pull(i);\n\
    \  }\n\n  template <class iter_type, class value_type = typename std::iterator_traits<\n\
    \                                 iter_type>::value_type>\n  lazy_segment_tree(iter_type\
    \ first, iter_type last)\n      : size_orig(std::distance(first, last)),\n   \
    \     height(size_orig > 1 ? 32 - __builtin_clz(size_orig - 1) : 0),\n       \
    \ size_ext{1u << height},\n        data(size_ext << 1),\n        lazy(size_ext),\n\
    \        wait(size_ext << 1) {\n    static_assert(std::is_constructible<Monoid,\
    \ value_type>::value,\n                  \"Monoid(iter_type::value_type) is not\
    \ constructible.\");\n    for (auto iter{std::next(std::begin(data), size_ext)};\n\
    \         iter != std::end(data) && first != last; ++iter, ++first)\n      *iter\
    \ = Monoid(*first);\n    for (size_t i{size_ext}; --i;) pull(i);\n  }\n\n  template\
    \ <class Container, typename = element_type<Container>>\n  lazy_segment_tree(const\
    \ Container &cont)\n      : lazy_segment_tree(std::begin(cont), std::end(cont))\
    \ {}\n\n  /**\n   * @return Number of elements.\n   */\n  size_t size() const\
    \ { return size_orig; }\n\n  /**\n   * @param index Index of the element\n   *\
    \ @return Reference to the element.\n   */\n  Monoid &operator[](size_t index)\
    \ {\n    assert(index < size_orig);\n    index |= size_ext;\n    wait.push(index);\n\
    \    for (size_t i = height; i; --i) push(index >> i);\n    return data[index];\n\
    \  }\n\n  void update(const Endomorphism &endo) { update(0, size_orig, endo);\
    \ }\n\n  void update(size_t index, const Endomorphism &endo) {\n    update(index,\
    \ index + 1, endo);\n  }\n\n  void update(size_t first, size_t last, const Endomorphism\
    \ &endo) {\n    assert(last <= size_orig);\n    repair();\n    if (first >= last)\
    \ return;\n    first += size_ext, last += size_ext;\n    --last;\n    for (size_t\
    \ i = height; i; --i) push(first >> i), push(last >> i);\n    ++last;\n    for\
    \ (size_t l = first, r = last; l != r; l >>= 1, r >>= 1) {\n      if (l & 1) apply(l++,\
    \ endo);\n      if (r & 1) apply(--r, endo);\n    }\n    for (first >>= __builtin_ffs(first);\
    \ first; first >>= 1) pull(first);\n    for (last >>= __builtin_ffs(last); last;\
    \ last >>= 1) pull(last);\n  }\n\n  /**\n   * @param first Left end, inclusive\n\
    \   * @param last Right end, exclusive\n   * @return Sum of elements in the interval.\n\
    \   */\n  Monoid fold(size_t first, size_t last) {\n    assert(last <= size_orig);\n\
    \    repair();\n    if (first >= last) return Monoid{};\n    first += size_ext,\
    \ last += size_ext - 1;\n    Monoid left_val{}, right_val{};\n    for (size_t\
    \ l = first, r = last + 1; l != r; l >>= 1, r >>= 1) {\n      if (l & 1) left_val\
    \ = left_val + data[l++];\n      if (r & 1) right_val = data[--r] + right_val;\n\
    \      left_val = left_val * lazy[first >>= 1];\n      right_val = right_val *\
    \ lazy[last >>= 1];\n    }\n    while (first >>= 1, last >>= 1) {\n      left_val\
    \ = left_val * lazy[first];\n      right_val = right_val * lazy[last];\n    }\n\
    \    return left_val + right_val;\n  }\n\n  /**\n   * @return Sum of all elements.\n\
    \   */\n  Monoid fold() { return fold(0, size_orig); }\n\n  /**\n   * @brief Binary\
    \ search for the partition point.\n   * @param right Right fixed end of the interval,\
    \ exclusive\n   * @param pred Predicate in the form of either 'bool(Monoid)' or\
    \ 'bool(Monoid,\n   * size_t)'\n   * @return Left end of the extremal interval\
    \ satisfying the condition,\n   * inclusive.\n   */\n  template <class Pred> size_t\
    \ left_partition(size_t right, Pred pred) {\n    assert(right <= size_orig);\n\
    \    repair();\n    right += size_ext - 1;\n    for (size_t i{height}; i; --i)\
    \ push(right >> i);\n    ++right;\n    Monoid mono{};\n    for (size_t left{size_ext},\
    \ step{}; left != right;\n         left >>= 1, right >>= 1, ++step) {\n      if\
    \ ((left & 1) != (right & 1)) {\n        const Monoid tmp = data[--right] + mono;\n\
    \        if (!pass_args(pred, tmp, (right << step) ^ size_ext))\n          return\
    \ left_partition_subtree(right, mono, step, pred);\n        mono = tmp;\n    \
    \  }\n    }\n    return 0;\n  }\n\n  /**\n   * @brief Binary search for the partition\
    \ point.\n   * @param left Left fixed end of the interval, inclusive\n   * @param\
    \ pred Predicate in the form of either 'bool(Monoid)' or 'bool(Monoid,\n   * size_t)'\n\
    \   * @return Right end of the extremal interval satisfying the condition,\n \
    \  * exclusive.\n   */\n  template <class Pred> size_t right_partition(size_t\
    \ left, Pred pred) {\n    assert(left <= size_orig);\n    repair();\n    left\
    \ += size_ext;\n    for (size_t i{height}; i; --i) push(left >> i);\n    Monoid\
    \ mono{};\n    for (size_t right{size_ext << 1}, step{}; left != right;\n    \
    \     left >>= 1, right >>= 1, ++step) {\n      if ((left & 1) != (right & 1))\
    \ {\n        const Monoid tmp = mono + data[left];\n        if (!pass_args(pred,\
    \ tmp, ((left + 1) << step) ^ size_ext))\n          return right_partition_subtree(left,\
    \ mono, step, pred);\n        mono = tmp;\n        ++left;\n      }\n    }\n \
    \   return size_orig;\n  }\n};\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/*\n * @file lazy.hpp\n * @brief Lazy Segment Tree\n */\n\
    \n#include <cassert>\n#include <queue>\n#include <vector>\n\n#include \"src/algebra/system/monoid.hpp\"\
    \n#include \"src/utils/sfinae.hpp\"\n#include \"waitings.hpp\"\n\nnamespace workspace\
    \ {\n\ntemplate <class Monoid, class Endomorphism,\n          class Monoid_container\
    \ = std::vector<Monoid>,\n          class Endomorphism_container = std::vector<Endomorphism>>\n\
    class lazy_segment_tree {\n  static_assert(std::is_same<Monoid, mapped_type<Monoid_container>>::value);\n\
    \n  static_assert(\n      std::is_same<Endomorphism, mapped_type<Endomorphism_container>>::value);\n\
    \n  static_assert(std::is_same<Monoid, decltype(std::declval<Monoid>() +\n   \
    \                                           std::declval<Monoid>())>::value,\n\
    \                \"\\'Monoid\\' has no proper binary \\'operator+\\'.\");\n\n\
    \  static_assert(\n      std::is_same<Endomorphism, decltype(std::declval<Endomorphism>()\
    \ *\n                                          std::declval<Endomorphism>())>::value,\n\
    \      \"\\'Endomorphism\\' has no proper binary operator*.\");\n\n  static_assert(\n\
    \      std::is_same<Monoid, decltype(std::declval<Monoid>() *\n              \
    \                      std::declval<Endomorphism>())>::value,\n      \"\\'Endomorphism\\\
    ' is not applicable to \\'Monoid\\'.\");\n\n  size_t size_orig, height, size_ext;\n\
    \  Monoid_container data;\n  Endomorphism_container lazy;\n  internal::waitings\
    \ wait;\n\n  void repair() {\n    while (!wait.empty()) {\n      const size_t\
    \ index = wait.pop() >> 1;\n      if (index && wait.push(index)) pull(index);\n\
    \    }\n  }\n\n  void apply(size_t node, const Endomorphism &endo) {\n    data[node]\
    \ = data[node] * endo;\n    if (node < size_ext) lazy[node] = lazy[node] * endo;\n\
    \  }\n\n  void push(size_t node) {\n    apply(node << 1, lazy[node]);\n    apply(node\
    \ << 1 | 1, lazy[node]);\n    lazy[node] = Endomorphism{};\n  }\n\n  void pull(size_t\
    \ node) { data[node] = data[node << 1] + data[node << 1 | 1]; }\n\n  template\
    \ <class Pred>\n  static constexpr decltype(std::declval<Pred>()(Monoid{})) pass_args(\n\
    \      Pred pred, Monoid const &_1, [[maybe_unused]] size_t _2) {\n    return\
    \ pred(_1);\n  }\n\n  template <class Pred>\n  static constexpr decltype(std::declval<Pred>()(Monoid{},\
    \ size_t{})) pass_args(\n      Pred pred, Monoid const &_1, size_t _2) {\n   \
    \ return pred(_1, _2);\n  }\n\n  template <class Pred>\n  size_t left_partition_subtree(size_t\
    \ node, Monoid mono, size_t step,\n                                Pred pred)\
    \ {\n    assert(node);\n    while (node < size_ext) {\n      push(node);\n   \
    \   const Monoid tmp = data[(node <<= 1) | 1] + mono;\n      if (pass_args(pred,\
    \ tmp, ((node | 1) << --step) ^ size_ext))\n        mono = tmp;\n      else\n\
    \        ++node;\n    }\n    return ++node -= size_ext;\n  }\n\n  template <class\
    \ Pred>\n  size_t right_partition_subtree(size_t node, Monoid mono, size_t step,\n\
    \                                 Pred pred) {\n    assert(node);\n    while (node\
    \ < size_ext) {\n      push(node);\n      const Monoid tmp = mono + data[node\
    \ <<= 1];\n      if (pass_args(pred, tmp, ((node | 1) << --step) ^ size_ext))\n\
    \        ++node, mono = tmp;\n    }\n    return (node -= size_ext) < size_orig\
    \ ? node : size_orig;\n  }\n\n public:\n  class iterator {\n    lazy_segment_tree\
    \ *__p;\n    size_t __i;\n\n   public:\n    using difference_type = typename std::make_signed<size_t>::type;\n\
    \    using value_type = Monoid;\n    using reference = Monoid &;\n    using pointer\
    \ = iterator;\n    using iterator_category = std::random_access_iterator_tag;\n\
    \n    /**\n     * @brief Construct a new iterator object\n     *\n     */\n  \
    \  iterator() = default;\n\n    /**\n     * @brief Construct a new iterator object\n\
    \     *\n     * @param __p Pointer to a segment tree object\n     * @param __i\
    \ Index\n     */\n    iterator(lazy_segment_tree *__p, size_t __i) : __p(__p),\
    \ __i(__i) {}\n\n    bool operator==(iterator const &rhs) const {\n      return\
    \ __p == rhs.__p && __i == rhs.__i;\n    }\n    bool operator!=(iterator const\
    \ &rhs) const { return !operator==(rhs); }\n\n    bool operator<(iterator const\
    \ &rhs) const { return __i < rhs.__i; }\n    bool operator>(iterator const &rhs)\
    \ const { return __i > rhs.__i; }\n    bool operator<=(iterator const &rhs) const\
    \ { return __i <= rhs.__i; }\n    bool operator>=(iterator const &rhs) const {\
    \ return __i >= rhs.__i; }\n\n    iterator &operator++() { return ++__i, *this;\
    \ }\n    iterator &operator--() { return --__i, *this; }\n\n    difference_type\
    \ operator-(iterator const &rhs) const {\n      return __i - rhs.__i;\n    }\n\
    \n    /**\n     * @brief\n     *\n     * @return reference\n     */\n    reference\
    \ operator*() const { return __p->operator[](__i); }\n  };\n\n  using value_type\
    \ = typename iterator::value_type;\n  using reference = typename iterator::reference;\n\
    \n  iterator begin() { return {this, 0}; }\n  iterator end() { return {this, size_orig};\
    \ }\n\n  auto rbegin() { return std::make_reverse_iterator(end()); }\n  auto rend()\
    \ { return std::make_reverse_iterator(begin()); }\n\n  lazy_segment_tree(size_t\
    \ n = 0)\n      : size_orig{n},\n        height(n > 1 ? 32 - __builtin_clz(n -\
    \ 1) : 0),\n        size_ext{1u << height},\n        data(size_ext << 1),\n  \
    \      lazy(size_ext),\n        wait(size_ext << 1) {}\n\n  lazy_segment_tree(size_t\
    \ n, const Monoid &init) : lazy_segment_tree(n) {\n    std::fill(std::next(std::begin(data),\
    \ size_ext), std::end(data), init);\n    for (size_t i{size_ext}; --i;) pull(i);\n\
    \  }\n\n  template <class iter_type, class value_type = typename std::iterator_traits<\n\
    \                                 iter_type>::value_type>\n  lazy_segment_tree(iter_type\
    \ first, iter_type last)\n      : size_orig(std::distance(first, last)),\n   \
    \     height(size_orig > 1 ? 32 - __builtin_clz(size_orig - 1) : 0),\n       \
    \ size_ext{1u << height},\n        data(size_ext << 1),\n        lazy(size_ext),\n\
    \        wait(size_ext << 1) {\n    static_assert(std::is_constructible<Monoid,\
    \ value_type>::value,\n                  \"Monoid(iter_type::value_type) is not\
    \ constructible.\");\n    for (auto iter{std::next(std::begin(data), size_ext)};\n\
    \         iter != std::end(data) && first != last; ++iter, ++first)\n      *iter\
    \ = Monoid(*first);\n    for (size_t i{size_ext}; --i;) pull(i);\n  }\n\n  template\
    \ <class Container, typename = element_type<Container>>\n  lazy_segment_tree(const\
    \ Container &cont)\n      : lazy_segment_tree(std::begin(cont), std::end(cont))\
    \ {}\n\n  /**\n   * @return Number of elements.\n   */\n  size_t size() const\
    \ { return size_orig; }\n\n  /**\n   * @param index Index of the element\n   *\
    \ @return Reference to the element.\n   */\n  Monoid &operator[](size_t index)\
    \ {\n    assert(index < size_orig);\n    index |= size_ext;\n    wait.push(index);\n\
    \    for (size_t i = height; i; --i) push(index >> i);\n    return data[index];\n\
    \  }\n\n  void update(const Endomorphism &endo) { update(0, size_orig, endo);\
    \ }\n\n  void update(size_t index, const Endomorphism &endo) {\n    update(index,\
    \ index + 1, endo);\n  }\n\n  void update(size_t first, size_t last, const Endomorphism\
    \ &endo) {\n    assert(last <= size_orig);\n    repair();\n    if (first >= last)\
    \ return;\n    first += size_ext, last += size_ext;\n    --last;\n    for (size_t\
    \ i = height; i; --i) push(first >> i), push(last >> i);\n    ++last;\n    for\
    \ (size_t l = first, r = last; l != r; l >>= 1, r >>= 1) {\n      if (l & 1) apply(l++,\
    \ endo);\n      if (r & 1) apply(--r, endo);\n    }\n    for (first >>= __builtin_ffs(first);\
    \ first; first >>= 1) pull(first);\n    for (last >>= __builtin_ffs(last); last;\
    \ last >>= 1) pull(last);\n  }\n\n  /**\n   * @param first Left end, inclusive\n\
    \   * @param last Right end, exclusive\n   * @return Sum of elements in the interval.\n\
    \   */\n  Monoid fold(size_t first, size_t last) {\n    assert(last <= size_orig);\n\
    \    repair();\n    if (first >= last) return Monoid{};\n    first += size_ext,\
    \ last += size_ext - 1;\n    Monoid left_val{}, right_val{};\n    for (size_t\
    \ l = first, r = last + 1; l != r; l >>= 1, r >>= 1) {\n      if (l & 1) left_val\
    \ = left_val + data[l++];\n      if (r & 1) right_val = data[--r] + right_val;\n\
    \      left_val = left_val * lazy[first >>= 1];\n      right_val = right_val *\
    \ lazy[last >>= 1];\n    }\n    while (first >>= 1, last >>= 1) {\n      left_val\
    \ = left_val * lazy[first];\n      right_val = right_val * lazy[last];\n    }\n\
    \    return left_val + right_val;\n  }\n\n  /**\n   * @return Sum of all elements.\n\
    \   */\n  Monoid fold() { return fold(0, size_orig); }\n\n  /**\n   * @brief Binary\
    \ search for the partition point.\n   * @param right Right fixed end of the interval,\
    \ exclusive\n   * @param pred Predicate in the form of either 'bool(Monoid)' or\
    \ 'bool(Monoid,\n   * size_t)'\n   * @return Left end of the extremal interval\
    \ satisfying the condition,\n   * inclusive.\n   */\n  template <class Pred> size_t\
    \ left_partition(size_t right, Pred pred) {\n    assert(right <= size_orig);\n\
    \    repair();\n    right += size_ext - 1;\n    for (size_t i{height}; i; --i)\
    \ push(right >> i);\n    ++right;\n    Monoid mono{};\n    for (size_t left{size_ext},\
    \ step{}; left != right;\n         left >>= 1, right >>= 1, ++step) {\n      if\
    \ ((left & 1) != (right & 1)) {\n        const Monoid tmp = data[--right] + mono;\n\
    \        if (!pass_args(pred, tmp, (right << step) ^ size_ext))\n          return\
    \ left_partition_subtree(right, mono, step, pred);\n        mono = tmp;\n    \
    \  }\n    }\n    return 0;\n  }\n\n  /**\n   * @brief Binary search for the partition\
    \ point.\n   * @param left Left fixed end of the interval, inclusive\n   * @param\
    \ pred Predicate in the form of either 'bool(Monoid)' or 'bool(Monoid,\n   * size_t)'\n\
    \   * @return Right end of the extremal interval satisfying the condition,\n \
    \  * exclusive.\n   */\n  template <class Pred> size_t right_partition(size_t\
    \ left, Pred pred) {\n    assert(left <= size_orig);\n    repair();\n    left\
    \ += size_ext;\n    for (size_t i{height}; i; --i) push(left >> i);\n    Monoid\
    \ mono{};\n    for (size_t right{size_ext << 1}, step{}; left != right;\n    \
    \     left >>= 1, right >>= 1, ++step) {\n      if ((left & 1) != (right & 1))\
    \ {\n        const Monoid tmp = mono + data[left];\n        if (!pass_args(pred,\
    \ tmp, ((left + 1) << step) ^ size_ext))\n          return right_partition_subtree(left,\
    \ mono, step, pred);\n        mono = tmp;\n        ++left;\n      }\n    }\n \
    \   return size_orig;\n  }\n};\n\n}  // namespace workspace\n"
  dependsOn:
  - src/algebra/system/monoid.hpp
  - src/utils/sfinae.hpp
  - src/data_structure/segment_tree/waitings.hpp
  isVerificationFile: false
  path: src/data_structure/segment_tree/lazy.hpp
  requiredBy: []
  timestamp: '2020-12-25 02:27:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/library-checker/range_affine_range_sum.test.cpp
  - test/aizu-online-judge/2450.test.cpp
documentation_of: src/data_structure/segment_tree/lazy.hpp
layout: document
redirect_from:
- /library/src/data_structure/segment_tree/lazy.hpp
- /library/src/data_structure/segment_tree/lazy.hpp.html
title: Lazy Segment Tree
---