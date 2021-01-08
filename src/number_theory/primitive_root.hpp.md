---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: src/utils/sfinae.hpp
    title: SFINAE
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Primitive Root
    links: []
  bundledCode: "#line 1 \"src/number_theory/primitive_root.hpp\"\n/**\n * @file primitive_root.hpp\n\
    \ * @brief Primitive Root\n * @date 2020-12-28\n */\n\n#include <type_traits>\n\
    \n#line 2 \"src/utils/sfinae.hpp\"\n\n/*\n * @file sfinae.hpp\n * @brief SFINAE\n\
    \ */\n\n#include <cstdint>\n#include <iterator>\n#line 11 \"src/utils/sfinae.hpp\"\
    \n\n#ifdef __SIZEOF_INT128__\n#define __INT128_DEFINED__ 1\n#else\n#define __INT128_DEFINED__\
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
    \ workspace\n#line 10 \"src/number_theory/primitive_root.hpp\"\n\n#if __cplusplus\
    \ >= 201703L\n\n#include <optional>\n\nnamespace workspace {\n\n/**\n * @brief\
    \ Compile time primitive root.\n *\n * @tparam __mod A positive integer\n * @return\
    \ Minimum positive one if it exists. Otherwise 0.\n */\ntemplate <class Tp>\n\
    constexpr typename std::enable_if<(is_integral_ext<Tp>::value), Tp>::type\nprimitive_root(const\
    \ Tp __mod) noexcept {\n  assert(__mod > 0);\n  using int_type = typename multiplicable_uint<Tp>::type;\n\
    \n  int_type __r = __mod, __p[16] = {}, *__q = __p;\n  for (int_type __i = 2;\
    \ __i <= __r / __i; ++__i) {\n    if (__r % __i) continue;\n    *__q++ = __i;\n\
    \    while (!(__r % __i)) __r /= __i;\n  }\n  if (__r != 1) *__q++ = __r;\n\n\
    \  int_type __tot = __mod;\n  for (__q = __p; *__q; *__q++ = 0) (__tot /= *__q)\
    \ *= *__q - 1;\n  __r = __tot, __q = __p + 1, __p[0] = 1;\n  for (int_type __i\
    \ = 2; __i <= __r / __i; ++__i) {\n    if (__r % __i) continue;\n    *__q++ =\
    \ __i;\n    while (!(__r % __i)) __r /= __i;\n  }\n  if (__r != 1) *__q++ = __r;\n\
    \n  for (int_type __r = 1; __r != __mod; ++__r) {\n    auto __cnt = 0;\n    for\
    \ (__q = __p; *__q; ++__q) {\n      int_type __w = 1;\n      for (int_type __e\
    \ = __tot / *__q, __x = __r; __e;\n           __e >>= 1, (__x *= __x) %= __mod)\n\
    \        if (__e & 1) (__w *= __x) %= __mod;\n      if (__w == 1 && ++__cnt >\
    \ 1) break;\n    }\n    if (__cnt == 1) return __r;\n  }\n\n  return 0;\n};\n\n\
    }  // namespace workspace\n\n#endif\n"
  code: "/**\n * @file primitive_root.hpp\n * @brief Primitive Root\n * @date 2020-12-28\n\
    \ */\n\n#include <type_traits>\n\n#include \"src/utils/sfinae.hpp\"\n\n#if __cplusplus\
    \ >= 201703L\n\n#include <optional>\n\nnamespace workspace {\n\n/**\n * @brief\
    \ Compile time primitive root.\n *\n * @tparam __mod A positive integer\n * @return\
    \ Minimum positive one if it exists. Otherwise 0.\n */\ntemplate <class Tp>\n\
    constexpr typename std::enable_if<(is_integral_ext<Tp>::value), Tp>::type\nprimitive_root(const\
    \ Tp __mod) noexcept {\n  assert(__mod > 0);\n  using int_type = typename multiplicable_uint<Tp>::type;\n\
    \n  int_type __r = __mod, __p[16] = {}, *__q = __p;\n  for (int_type __i = 2;\
    \ __i <= __r / __i; ++__i) {\n    if (__r % __i) continue;\n    *__q++ = __i;\n\
    \    while (!(__r % __i)) __r /= __i;\n  }\n  if (__r != 1) *__q++ = __r;\n\n\
    \  int_type __tot = __mod;\n  for (__q = __p; *__q; *__q++ = 0) (__tot /= *__q)\
    \ *= *__q - 1;\n  __r = __tot, __q = __p + 1, __p[0] = 1;\n  for (int_type __i\
    \ = 2; __i <= __r / __i; ++__i) {\n    if (__r % __i) continue;\n    *__q++ =\
    \ __i;\n    while (!(__r % __i)) __r /= __i;\n  }\n  if (__r != 1) *__q++ = __r;\n\
    \n  for (int_type __r = 1; __r != __mod; ++__r) {\n    auto __cnt = 0;\n    for\
    \ (__q = __p; *__q; ++__q) {\n      int_type __w = 1;\n      for (int_type __e\
    \ = __tot / *__q, __x = __r; __e;\n           __e >>= 1, (__x *= __x) %= __mod)\n\
    \        if (__e & 1) (__w *= __x) %= __mod;\n      if (__w == 1 && ++__cnt >\
    \ 1) break;\n    }\n    if (__cnt == 1) return __r;\n  }\n\n  return 0;\n};\n\n\
    }  // namespace workspace\n\n#endif\n"
  dependsOn:
  - src/utils/sfinae.hpp
  isVerificationFile: false
  path: src/number_theory/primitive_root.hpp
  requiredBy: []
  timestamp: '2020-12-28 23:08:41+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/number_theory/primitive_root.hpp
layout: document
redirect_from:
- /library/src/number_theory/primitive_root.hpp
- /library/src/number_theory/primitive_root.hpp.html
title: Primitive Root
---