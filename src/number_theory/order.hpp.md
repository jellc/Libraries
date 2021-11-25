---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/number_theory/ext_gcd.hpp
    title: Extended Euclidean Algorithm
  - icon: ':heavy_check_mark:'
    path: src/utils/sfinae.hpp
    title: SFINAE
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Order
    links: []
  bundledCode: "#line 1 \"src/number_theory/order.hpp\"\n/**\n * @file order.hpp\n\
    \ * @brief Order\n * @date 2021-01-15\n *\n *\n */\n\n#include <unordered_map>\n\
    \n#line 2 \"src/number_theory/ext_gcd.hpp\"\n\n/**\n * @file ext_gcd.hpp\n * @brief\
    \ Extended Euclidean Algorithm\n */\n\n#include <tuple>\n\n#line 2 \"src/utils/sfinae.hpp\"\
    \n\n/**\n * @file sfinae.hpp\n * @brief SFINAE\n */\n\n#include <cstdint>\n#include\
    \ <iterator>\n#include <type_traits>\n\n#ifndef __INT128_DEFINED__\n\n#ifdef __SIZEOF_INT128__\n\
    #define __INT128_DEFINED__ 1\n#else\n#define __INT128_DEFINED__ 0\n#endif\n\n\
    #endif\n\nnamespace std {\n\n#if __INT128_DEFINED__\n\ntemplate <> struct make_signed<__uint128_t>\
    \ { using type = __int128_t; };\ntemplate <> struct make_signed<__int128_t> {\
    \ using type = __int128_t; };\n\ntemplate <> struct make_unsigned<__uint128_t>\
    \ { using type = __uint128_t; };\ntemplate <> struct make_unsigned<__int128_t>\
    \ { using type = __uint128_t; };\n\ntemplate <> struct is_signed<__uint128_t>\
    \ : std::false_type {};\ntemplate <> struct is_signed<__int128_t> : std::true_type\
    \ {};\n\ntemplate <> struct is_unsigned<__uint128_t> : std::true_type {};\ntemplate\
    \ <> struct is_unsigned<__int128_t> : std::false_type {};\n\n#endif\n\n}  // namespace\
    \ std\n\nnamespace workspace {\n\ntemplate <class Tp, class... Args> struct variadic_front\
    \ { using type = Tp; };\n\ntemplate <class... Args> struct variadic_back;\n\n\
    template <class Tp> struct variadic_back<Tp> { using type = Tp; };\n\ntemplate\
    \ <class Tp, class... Args> struct variadic_back<Tp, Args...> {\n  using type\
    \ = typename variadic_back<Args...>::type;\n};\n\ntemplate <class type, template\
    \ <class> class trait>\nusing enable_if_trait_type = typename std::enable_if<trait<type>::value>::type;\n\
    \n/**\n * @brief Return type of subscripting ( @c [] ) access.\n */\ntemplate\
    \ <class _Tp>\nusing subscripted_type =\n    typename std::decay<decltype(std::declval<_Tp&>()[0])>::type;\n\
    \ntemplate <class Container>\nusing element_type = typename std::decay<decltype(\n\
    \    *std::begin(std::declval<Container&>()))>::type;\n\ntemplate <class _Tp,\
    \ class = std::nullptr_t>\nstruct has_begin : std::false_type {};\n\ntemplate\
    \ <class _Tp>\nstruct has_begin<_Tp, decltype(std::begin(std::declval<_Tp>()),\
    \ nullptr)>\n    : std::true_type {};\n\ntemplate <class _Tp, class = void> struct\
    \ has_mod : std::false_type {};\n\ntemplate <class _Tp>\nstruct has_mod<_Tp, std::__void_t<decltype(_Tp::mod)>>\
    \ : std::true_type {};\n\ntemplate <class _Tp, class = void> struct is_integral_ext\
    \ : std::false_type {};\ntemplate <class _Tp>\nstruct is_integral_ext<\n    _Tp,\
    \ typename std::enable_if<std::is_integral<_Tp>::value>::type>\n    : std::true_type\
    \ {};\n\n#if __INT128_DEFINED__\n\ntemplate <> struct is_integral_ext<__int128_t>\
    \ : std::true_type {};\ntemplate <> struct is_integral_ext<__uint128_t> : std::true_type\
    \ {};\n\n#endif\n\n#if __cplusplus >= 201402\n\ntemplate <class _Tp>\nconstexpr\
    \ static bool is_integral_ext_v = is_integral_ext<_Tp>::value;\n\n#endif\n\ntemplate\
    \ <typename _Tp, typename = void> struct multiplicable_uint {\n  using type =\
    \ uint_least32_t;\n};\ntemplate <typename _Tp>\nstruct multiplicable_uint<\n \
    \   _Tp,\n    typename std::enable_if<(2 < sizeof(_Tp)) &&\n                 \
    \           (!__INT128_DEFINED__ || sizeof(_Tp) <= 4)>::type> {\n  using type\
    \ = uint_least64_t;\n};\n\n#if __INT128_DEFINED__\n\ntemplate <typename _Tp>\n\
    struct multiplicable_uint<_Tp,\n                          typename std::enable_if<(4\
    \ < sizeof(_Tp))>::type> {\n  using type = __uint128_t;\n};\n\n#endif\n\ntemplate\
    \ <typename _Tp> struct multiplicable_int {\n  using type =\n      typename std::make_signed<typename\
    \ multiplicable_uint<_Tp>::type>::type;\n};\n\ntemplate <typename _Tp> struct\
    \ multiplicable {\n  using type = std::conditional_t<\n      is_integral_ext<_Tp>::value,\n\
    \      std::conditional_t<std::is_signed<_Tp>::value,\n                      \
    \   typename multiplicable_int<_Tp>::type,\n                         typename\
    \ multiplicable_uint<_Tp>::type>,\n      _Tp>;\n};\n\ntemplate <class> struct\
    \ first_arg { using type = void; };\n\ntemplate <class _R, class _Tp, class...\
    \ _Args>\nstruct first_arg<_R(_Tp, _Args...)> {\n  using type = _Tp;\n};\n\ntemplate\
    \ <class _R, class _Tp, class... _Args>\nstruct first_arg<_R (*)(_Tp, _Args...)>\
    \ {\n  using type = _Tp;\n};\n\ntemplate <class _G, class _R, class _Tp, class...\
    \ _Args>\nstruct first_arg<_R (_G::*)(_Tp, _Args...)> {\n  using type = _Tp;\n\
    };\n\ntemplate <class _G, class _R, class _Tp, class... _Args>\nstruct first_arg<_R\
    \ (_G::*)(_Tp, _Args...) const> {\n  using type = _Tp;\n};\n\ntemplate <class\
    \ _Tp, class = void> struct parse_compare : first_arg<_Tp> {};\n\ntemplate <class\
    \ _Tp>\nstruct parse_compare<_Tp, std::__void_t<decltype(&_Tp::operator())>>\n\
    \    : first_arg<decltype(&_Tp::operator())> {};\n\n}  // namespace workspace\n\
    #line 11 \"src/number_theory/ext_gcd.hpp\"\n\nnamespace workspace {\n\n/**\n *\
    \ @param __a Integer\n * @param __b Integer\n * @return Pair of integers (x, y)\
    \ s.t. ax + by = g = gcd(a, b) and (b = 0 or 0\n * <= x < |b/g|) and (a = 0 or\
    \ -|a/g| < y <= 0). Return (0, 0) if (a, b) = (0,\n * 0).\n */\ntemplate <typename\
    \ _T1, typename _T2>\nconstexpr auto ext_gcd(_T1 __a, _T2 __b) noexcept {\n  static_assert(is_integral_ext<_T1>::value);\n\
    \  static_assert(is_integral_ext<_T2>::value);\n\n  using value_type = typename\
    \ std::make_signed<\n      typename std::common_type<_T1, _T2>::type>::type;\n\
    \  using result_type = std::pair<value_type, value_type>;\n\n  value_type a{__a},\
    \ b{__b}, p{1}, q{}, r{}, s{1};\n\n  while (b != value_type(0)) {\n    auto t\
    \ = a / b;\n    r ^= p ^= r ^= p -= t * r;\n    s ^= q ^= s ^= q -= t * s;\n \
    \   b ^= a ^= b ^= a -= t * b;\n  }\n\n  if (a < 0) p = -p, q = -q, a = -a;\n\n\
    \  if (p < 0) {\n    __a /= a, __b /= a;\n\n    if (__b > 0)\n      p += __b,\
    \ q -= __a;\n    else\n      p -= __b, q += __a;\n  }\n\n  return result_type{p,\
    \ q};\n}\n\n/**\n * @param __a Integer\n * @param __b Integer\n * @param __c Integer\n\
    \ * @return Pair of integers (x, y) s.t. ax + by = c and (b = 0 or 0 <= x <\n\
    \ * |b/g|). Return (0, 0) if there is no solution.\n */\ntemplate <typename _T1,\
    \ typename _T2, typename _T3>\nconstexpr auto ext_gcd(_T1 __a, _T2 __b, _T3 __c)\
    \ noexcept {\n  static_assert(is_integral_ext<_T1>::value);\n  static_assert(is_integral_ext<_T2>::value);\n\
    \  static_assert(is_integral_ext<_T3>::value);\n\n  using value_type = typename\
    \ std::make_signed<\n      typename std::common_type<_T1, _T2, _T3>::type>::type;\n\
    \  using result_type = std::pair<value_type, value_type>;\n\n  value_type a{__a},\
    \ b{__b}, p{1}, q{}, r{}, s{1};\n\n  while (b != value_type(0)) {\n    auto t\
    \ = a / b;\n    r ^= p ^= r ^= p -= t * r;\n    s ^= q ^= s ^= q -= t * s;\n \
    \   b ^= a ^= b ^= a -= t * b;\n  }\n\n  if (__c % a) return result_type{};\n\n\
    \  __a /= a, __b /= a, __c /= a;\n  p *= __c, q *= __c;\n\n  if (__b != value_type(0))\
    \ {\n    auto t = p / __b;\n    p -= __b * t;\n    q += __a * t;\n\n    if (p\
    \ < 0) {\n      if (__b > 0)\n        p += __b, q -= __a;\n      else\n      \
    \  p -= __b, q += __a;\n    }\n  }\n\n  return result_type{p, q};\n}\n\n}  //\
    \ namespace workspace\n#line 12 \"src/number_theory/order.hpp\"\n\nnamespace workspace\
    \ {\n\n/**\n * @brief\n *\n * @param __x Integer\n * @param __mod Modulus\n *\
    \ @return The order of @p __x modulo @p __mod.\n */\ntemplate <class Tp>\nconstexpr\
    \ typename std::enable_if<(is_integral_ext<Tp>::value), Tp>::type order(\n   \
    \ Tp __x, const Tp __mod) noexcept {\n  assert(__mod > 0);\n  using int_type =\
    \ typename multiplicable_int<Tp>::type;\n\n  __x %= __mod;\n  if (__x < 0) __x\
    \ += __mod;\n  std::unordered_map<Tp, Tp> __ls;\n  int_type __p;\n  Tp __i;\n\
    \  for (__i = 1, __p = __x; __i * __i < __mod; ++__i, (__p *= __x) %= __mod)\n\
    \    __ls.emplace(__p, __i);\n\n  for (int_type __q{1}, __v{1}, __j{0};;\n   \
    \    __v = ext_gcd((__q *= __p) %= __mod, __mod).first, __j += __i,\n       __ls[1]\
    \ = 0)\n    if (auto __f = __ls.find(__v < 0 ? __v += __mod : __v); __f != __ls.end())\n\
    \      return __j + __f->second;\n};\n\n}  // namespace workspace\n"
  code: "/**\n * @file order.hpp\n * @brief Order\n * @date 2021-01-15\n *\n *\n */\n\
    \n#include <unordered_map>\n\n#include \"ext_gcd.hpp\"\n\nnamespace workspace\
    \ {\n\n/**\n * @brief\n *\n * @param __x Integer\n * @param __mod Modulus\n *\
    \ @return The order of @p __x modulo @p __mod.\n */\ntemplate <class Tp>\nconstexpr\
    \ typename std::enable_if<(is_integral_ext<Tp>::value), Tp>::type order(\n   \
    \ Tp __x, const Tp __mod) noexcept {\n  assert(__mod > 0);\n  using int_type =\
    \ typename multiplicable_int<Tp>::type;\n\n  __x %= __mod;\n  if (__x < 0) __x\
    \ += __mod;\n  std::unordered_map<Tp, Tp> __ls;\n  int_type __p;\n  Tp __i;\n\
    \  for (__i = 1, __p = __x; __i * __i < __mod; ++__i, (__p *= __x) %= __mod)\n\
    \    __ls.emplace(__p, __i);\n\n  for (int_type __q{1}, __v{1}, __j{0};;\n   \
    \    __v = ext_gcd((__q *= __p) %= __mod, __mod).first, __j += __i,\n       __ls[1]\
    \ = 0)\n    if (auto __f = __ls.find(__v < 0 ? __v += __mod : __v); __f != __ls.end())\n\
    \      return __j + __f->second;\n};\n\n}  // namespace workspace\n"
  dependsOn:
  - src/number_theory/ext_gcd.hpp
  - src/utils/sfinae.hpp
  isVerificationFile: false
  path: src/number_theory/order.hpp
  requiredBy: []
  timestamp: '2021-07-16 03:07:50+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/number_theory/order.hpp
layout: document
redirect_from:
- /library/src/number_theory/order.hpp
- /library/src/number_theory/order.hpp.html
title: Order
---