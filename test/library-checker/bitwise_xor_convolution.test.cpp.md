---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/algebra/convolution/bitxor.hpp
    title: Bitwise Xor Convolution
  - icon: ':question:'
    path: src/modular/modint.hpp
    title: Modular Arithmetic
  - icon: ':question:'
    path: src/utils/io/istream.hpp
    title: Input Stream
  - icon: ':heavy_check_mark:'
    path: src/utils/io/ostream.hpp
    title: Output Stream
  - icon: ':question:'
    path: src/utils/sfinae.hpp
    title: SFINAE
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/bitwise_xor_convolution
    links:
    - https://judge.yosupo.jp/problem/bitwise_xor_convolution
  bundledCode: "#line 1 \"test/library-checker/bitwise_xor_convolution.test.cpp\"\n\
    #define PROBLEM \"https://judge.yosupo.jp/problem/bitwise_xor_convolution\"\n\n\
    #include <vector>\n\n#line 2 \"src/algebra/convolution/bitxor.hpp\"\n\n/**\n *\
    \ @file bitxor.hpp\n * @brief Bitwise Xor Convolution\n * @date 2021-01-08\n */\n\
    \n#include <iterator>\n\n#line 2 \"lib/bit\"\n\n#if __cplusplus > 201703L\n\n\
    #include <bit>\n\n#else\n\n#ifndef _GLIBCXX_BIT\n#define _GLIBCXX_BIT 1\n\n#include\
    \ <limits>\n#include <type_traits>\n\nnamespace std {\n\ntemplate <typename _Tp>\
    \ constexpr _Tp __rotl(_Tp __x, int __s) noexcept {\n  constexpr auto _Nd = numeric_limits<_Tp>::digits;\n\
    \  const int __r = __s % _Nd;\n  if (__r == 0)\n    return __x;\n  else if (__r\
    \ > 0)\n    return (__x << __r) | (__x >> ((_Nd - __r) % _Nd));\n  else\n    return\
    \ (__x >> -__r) | (__x << ((_Nd + __r) % _Nd));  // rotr(x, -r)\n}\n\ntemplate\
    \ <typename _Tp> constexpr _Tp __rotr(_Tp __x, int __s) noexcept {\n  constexpr\
    \ auto _Nd = numeric_limits<_Tp>::digits;\n  const int __r = __s % _Nd;\n  if\
    \ (__r == 0)\n    return __x;\n  else if (__r > 0)\n    return (__x >> __r) |\
    \ (__x << ((_Nd - __r) % _Nd));\n  else\n    return (__x << -__r) | (__x >> ((_Nd\
    \ + __r) % _Nd));  // rotl(x, -r)\n}\n\ntemplate <typename _Tp> constexpr int\
    \ __countl_zero(_Tp __x) noexcept {\n  constexpr auto _Nd = numeric_limits<_Tp>::digits;\n\
    \n  if (__x == 0) return _Nd;\n\n  constexpr auto _Nd_ull = numeric_limits<unsigned\
    \ long long>::digits;\n  constexpr auto _Nd_ul = numeric_limits<unsigned long>::digits;\n\
    \  constexpr auto _Nd_u = numeric_limits<unsigned>::digits;\n\n  if _GLIBCXX17_CONSTEXPR\
    \ (_Nd <= _Nd_u) {\n    constexpr int __diff = _Nd_u - _Nd;\n    return __builtin_clz(__x)\
    \ - __diff;\n  } else if _GLIBCXX17_CONSTEXPR (_Nd <= _Nd_ul) {\n    constexpr\
    \ int __diff = _Nd_ul - _Nd;\n    return __builtin_clzl(__x) - __diff;\n  } else\
    \ if _GLIBCXX17_CONSTEXPR (_Nd <= _Nd_ull) {\n    constexpr int __diff = _Nd_ull\
    \ - _Nd;\n    return __builtin_clzll(__x) - __diff;\n  } else  // (_Nd > _Nd_ull)\n\
    \  {\n    static_assert(_Nd <= (2 * _Nd_ull),\n                  \"Maximum supported\
    \ integer size is 128-bit\");\n\n    unsigned long long __high = __x >> _Nd_ull;\n\
    \    if (__high != 0) {\n      constexpr int __diff = (2 * _Nd_ull) - _Nd;\n \
    \     return __builtin_clzll(__high) - __diff;\n    }\n    constexpr auto __max_ull\
    \ = numeric_limits<unsigned long long>::max();\n    unsigned long long __low =\
    \ __x & __max_ull;\n    return (_Nd - _Nd_ull) + __builtin_clzll(__low);\n  }\n\
    }\n\ntemplate <typename _Tp> constexpr int __countl_one(_Tp __x) noexcept {\n\
    \  if (__x == numeric_limits<_Tp>::max()) return numeric_limits<_Tp>::digits;\n\
    \  return __countl_zero<_Tp>((_Tp)~__x);\n}\n\ntemplate <typename _Tp> constexpr\
    \ int __countr_zero(_Tp __x) noexcept {\n  constexpr auto _Nd = numeric_limits<_Tp>::digits;\n\
    \n  if (__x == 0) return _Nd;\n\n  constexpr auto _Nd_ull = numeric_limits<unsigned\
    \ long long>::digits;\n  constexpr auto _Nd_ul = numeric_limits<unsigned long>::digits;\n\
    \  constexpr auto _Nd_u = numeric_limits<unsigned>::digits;\n\n  if _GLIBCXX17_CONSTEXPR\
    \ (_Nd <= _Nd_u)\n    return __builtin_ctz(__x);\n  else if _GLIBCXX17_CONSTEXPR\
    \ (_Nd <= _Nd_ul)\n    return __builtin_ctzl(__x);\n  else if _GLIBCXX17_CONSTEXPR\
    \ (_Nd <= _Nd_ull)\n    return __builtin_ctzll(__x);\n  else  // (_Nd > _Nd_ull)\n\
    \  {\n    static_assert(_Nd <= (2 * _Nd_ull),\n                  \"Maximum supported\
    \ integer size is 128-bit\");\n\n    constexpr auto __max_ull = numeric_limits<unsigned\
    \ long long>::max();\n    unsigned long long __low = __x & __max_ull;\n    if\
    \ (__low != 0) return __builtin_ctzll(__low);\n    unsigned long long __high =\
    \ __x >> _Nd_ull;\n    return __builtin_ctzll(__high) + _Nd_ull;\n  }\n}\n\ntemplate\
    \ <typename _Tp> constexpr int __countr_one(_Tp __x) noexcept {\n  if (__x ==\
    \ numeric_limits<_Tp>::max()) return numeric_limits<_Tp>::digits;\n  return __countr_zero((_Tp)~__x);\n\
    }\n\ntemplate <typename _Tp> constexpr int __popcount(_Tp __x) noexcept {\n  constexpr\
    \ auto _Nd = numeric_limits<_Tp>::digits;\n\n  if (__x == 0) return 0;\n\n  constexpr\
    \ auto _Nd_ull = numeric_limits<unsigned long long>::digits;\n  constexpr auto\
    \ _Nd_ul = numeric_limits<unsigned long>::digits;\n  constexpr auto _Nd_u = numeric_limits<unsigned>::digits;\n\
    \n  if _GLIBCXX17_CONSTEXPR (_Nd <= _Nd_u)\n    return __builtin_popcount(__x);\n\
    \  else if _GLIBCXX17_CONSTEXPR (_Nd <= _Nd_ul)\n    return __builtin_popcountl(__x);\n\
    \  else if _GLIBCXX17_CONSTEXPR (_Nd <= _Nd_ull)\n    return __builtin_popcountll(__x);\n\
    \  else  // (_Nd > _Nd_ull)\n  {\n    static_assert(_Nd <= (2 * _Nd_ull),\n  \
    \                \"Maximum supported integer size is 128-bit\");\n\n    constexpr\
    \ auto __max_ull = numeric_limits<unsigned long long>::max();\n    unsigned long\
    \ long __low = __x & __max_ull;\n    unsigned long long __high = __x >> _Nd_ull;\n\
    \    return __builtin_popcountll(__low) + __builtin_popcountll(__high);\n  }\n\
    }\n\ntemplate <typename _Tp> constexpr bool __has_single_bit(_Tp __x) noexcept\
    \ {\n  return __popcount(__x) == 1;\n}\n\ntemplate <typename _Tp> constexpr _Tp\
    \ __bit_ceil(_Tp __x) noexcept {\n  constexpr auto _Nd = numeric_limits<_Tp>::digits;\n\
    \  if (__x == 0 || __x == 1) return 1;\n  auto __shift_exponent = _Nd - __countl_zero((_Tp)(__x\
    \ - 1u));\n#ifdef _GLIBCXX_HAVE_BUILTIN_IS_CONSTANT_EVALUATED\n  if (!__builtin_is_constant_evaluated())\
    \ {\n    __glibcxx_assert(__shift_exponent != numeric_limits<_Tp>::digits);\n\
    \  }\n#endif\n  using __promoted_type = decltype(__x << 1);\n  if _GLIBCXX17_CONSTEXPR\
    \ (!is_same<__promoted_type, _Tp>::value) {\n    const int __extra_exp = sizeof(__promoted_type)\
    \ / sizeof(_Tp) / 2;\n    __shift_exponent |= (__shift_exponent & _Nd) << __extra_exp;\n\
    \  }\n  return (_Tp)1u << __shift_exponent;\n}\n\ntemplate <typename _Tp> constexpr\
    \ _Tp __bit_floor(_Tp __x) noexcept {\n  constexpr auto _Nd = numeric_limits<_Tp>::digits;\n\
    \  if (__x == 0) return 0;\n  return (_Tp)1u << (_Nd - __countl_zero((_Tp)(__x\
    \ >> 1)));\n}\n\ntemplate <typename _Tp> constexpr _Tp __bit_width(_Tp __x) noexcept\
    \ {\n  constexpr auto _Nd = numeric_limits<_Tp>::digits;\n  return _Nd - __countl_zero(__x);\n\
    }\n\n}  // namespace std\n\n#endif\n\n#endif\n#line 12 \"src/algebra/convolution/bitxor.hpp\"\
    \n\nnamespace workspace {\n\ntemplate <class A> A bitwise_fft(A f) {\n  size_t\
    \ len = std::__bit_floor(std::size(f));\n  for (size_t p = 1; p < len; p <<= 1)\
    \ {\n    for (size_t i = 0; i < len; i += p << 1) {\n      for (size_t j = 0;\
    \ j < p; ++j) {\n        auto t = f[i + j + p];\n        f[i + j + p] = f[i +\
    \ j] - t;\n        f[i + j] += t;\n      }\n    }\n  }\n  return f;\n}\n\ntemplate\
    \ <class A> A bitwise_ifft(A f) {\n  size_t len = std::__bit_floor(std::size(f));\n\
    \  for (size_t p = len; p != 1; p >>= 1) {\n    for (size_t i = 0; i < len; i\
    \ += p) {\n      for (size_t j = 0; j << 1 < p; ++j) {\n        auto t = f[i +\
    \ j + (p >> 1)];\n        f[i + j + (p >> 1)] = (f[i + j] - t) / 2;\n        (f[i\
    \ + j] += t) /= 2;\n      }\n    }\n  }\n  return f;\n}\n\ntemplate <class A>\
    \ A bitxor_conv(A f, A g) {\n  f = bitwise_fft(f);\n  g = bitwise_fft(g);\n  for\
    \ (size_t i = 0; i != std::size(f); ++i) f[i] *= g[i];\n  f = bitwise_ifft(f);\n\
    \  return f;\n}\n\n}  // namespace workspace\n#line 2 \"src/modular/modint.hpp\"\
    \n\n/**\n * @file modint.hpp\n *\n * @brief Modular Arithmetic\n */\n\n#include\
    \ <cassert>\n#include <iostream>\n#line 12 \"src/modular/modint.hpp\"\n\n#line\
    \ 2 \"src/utils/sfinae.hpp\"\n\n/**\n * @file sfinae.hpp\n * @brief SFINAE\n */\n\
    \n#include <cstdint>\n#line 10 \"src/utils/sfinae.hpp\"\n#include <type_traits>\n\
    \n#ifndef __INT128_DEFINED__\n\n#ifdef __SIZEOF_INT128__\n#define __INT128_DEFINED__\
    \ 1\n#else\n#define __INT128_DEFINED__ 0\n#endif\n\n#endif\n\nnamespace std {\n\
    \n#if __INT128_DEFINED__\n\ntemplate <> struct make_signed<__uint128_t> { using\
    \ type = __int128_t; };\ntemplate <> struct make_signed<__int128_t> { using type\
    \ = __int128_t; };\n\ntemplate <> struct make_unsigned<__uint128_t> { using type\
    \ = __uint128_t; };\ntemplate <> struct make_unsigned<__int128_t> { using type\
    \ = __uint128_t; };\n\ntemplate <> struct is_signed<__uint128_t> : std::false_type\
    \ {};\ntemplate <> struct is_signed<__int128_t> : std::true_type {};\n\ntemplate\
    \ <> struct is_unsigned<__uint128_t> : std::true_type {};\ntemplate <> struct\
    \ is_unsigned<__int128_t> : std::false_type {};\n\n#endif\n\n}  // namespace std\n\
    \nnamespace workspace {\n\ntemplate <class Tp, class... Args> struct variadic_front\
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
    \ nullptr)>\n    : std::true_type {};\n\ntemplate <class _Tp, class = std::nullptr_t>\n\
    struct has_mod : std::false_type {};\n\ntemplate <class _Tp>\nstruct has_mod<_Tp,\
    \ decltype(_Tp::mod, nullptr)> : std::true_type {};\n\ntemplate <class _Tp, class\
    \ = void> struct is_integral_ext : std::false_type {};\ntemplate <class _Tp>\n\
    struct is_integral_ext<\n    _Tp, typename std::enable_if<std::is_integral<_Tp>::value>::type>\n\
    \    : std::true_type {};\n\n#if __INT128_DEFINED__\n\ntemplate <> struct is_integral_ext<__int128_t>\
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
    \ multiplicable_uint<_Tp>::type>,\n      _Tp>;\n};\n\n}  // namespace workspace\n\
    #line 14 \"src/modular/modint.hpp\"\n\nnamespace workspace {\n\nnamespace _modint_impl\
    \ {\n\n/**\n * @brief Modular arithmetic.\n *\n * @tparam Mod identifier, which\
    \ represents modulus if positive\n * @tparam Storage Reserved size for inverse\
    \ calculation\n */\ntemplate <auto Mod, unsigned Storage> struct modint {\n  static_assert(is_integral_ext<decltype(Mod)>::value,\n\
    \                \"Mod must be integral type.\");\n\n  using mod_type = typename\
    \ std::make_signed<typename std::conditional<\n      0 < Mod, typename std::add_const<decltype(Mod)>::type,\n\
    \      decltype(Mod)>::type>::type;\n\n  using value_type = typename std::decay<mod_type>::type;\n\
    \n  using mul_type = typename multiplicable_uint<value_type>::type;\n\n  // Modulus\n\
    \  static mod_type mod;\n\n  static unsigned storage;\n\n  constexpr static void\
    \ reserve(unsigned __n) noexcept { storage = __n; }\n\n private:\n  value_type\
    \ value = 0;\n\n  struct direct_ctor_t {};\n  constexpr static direct_ctor_t direct_ctor_tag{};\n\
    \n  // Direct constructor\n  template <class _Tp> constexpr modint(_Tp __n, direct_ctor_t)\
    \ : value(__n) {}\n\n public:\n  constexpr modint() noexcept = default;\n\n  template\
    \ <class _Tp, typename std::enable_if<\n                           is_integral_ext<_Tp>::value>::type\
    \ * = nullptr>\n  constexpr modint(_Tp __n) noexcept\n      : value((__n %= mod)\
    \ < 0 ? __n += mod : __n) {}\n\n  constexpr modint(bool __n) noexcept : value(__n)\
    \ {}\n\n  constexpr operator value_type() const noexcept { return value; }\n\n\
    \  constexpr static modint one() noexcept { return 1; }\n\n  // unary operators\
    \ {{\n  constexpr modint operator++(int) noexcept {\n    modint __t{*this};\n\
    \    operator++();\n    return __t;\n  }\n\n  constexpr modint operator--(int)\
    \ noexcept {\n    modint __t{*this};\n    operator--();\n    return __t;\n  }\n\
    \n  constexpr modint &operator++() noexcept {\n    if (++value == mod) value =\
    \ 0;\n    return *this;\n  }\n\n  constexpr modint &operator--() noexcept {\n\
    \    if (!value)\n      value = mod - 1;\n    else\n      --value;\n    return\
    \ *this;\n  }\n\n  constexpr modint operator+() const noexcept { return *this;\
    \ }\n\n  constexpr modint operator-() const noexcept {\n    return {value ? mod\
    \ - value : 0, direct_ctor_tag};\n  }\n\n  // }} unary operators\n\n  // operator+=\
    \ {{\n\n  constexpr modint &operator+=(const modint &__x) noexcept {\n    if ((value\
    \ += __x.value) >= mod) value -= mod;\n    return *this;\n  }\n\n  template <class\
    \ _Tp>\n  constexpr typename std::enable_if<is_integral_ext<_Tp>::value, modint>::type\
    \ &\n  operator+=(_Tp const &__x) noexcept {\n    if (((value += __x) %= mod)\
    \ < 0) value += mod;\n    return *this;\n  }\n\n  // }} operator+=\n\n  // operator+\
    \ {{\n\n  template <class _Tp>\n  constexpr typename std::enable_if<is_integral_ext<_Tp>::value,\
    \ modint>::type\n  operator+(_Tp const &__x) const noexcept {\n    return modint{*this}\
    \ += __x;\n  }\n\n  constexpr modint operator+(modint __x) const noexcept { return\
    \ __x += *this; }\n\n  template <class _Tp>\n  constexpr friend\n      typename\
    \ std::enable_if<is_integral_ext<_Tp>::value, modint>::type\n      operator+(_Tp\
    \ const &__x, modint __y) noexcept {\n    return __y += __x;\n  }\n\n  // }} operator+\n\
    \n  // operator-= {{\n\n  constexpr modint &operator-=(const modint &__x) noexcept\
    \ {\n    if ((value -= __x.value) < 0) value += mod;\n    return *this;\n  }\n\
    \n  template <class _Tp>\n  constexpr typename std::enable_if<is_integral_ext<_Tp>::value,\
    \ modint>::type &\n  operator-=(_Tp __x) noexcept {\n    if (((value -= __x) %=\
    \ mod) < 0) value += mod;\n    return *this;\n  }\n\n  // }} operator-=\n\n  //\
    \ operator- {{\n\n  template <class _Tp>\n  constexpr typename std::enable_if<is_integral_ext<_Tp>::value,\
    \ modint>::type\n  operator-(_Tp const &__x) const noexcept {\n    return modint{*this}\
    \ -= __x;\n  }\n\n  constexpr modint operator-(const modint &__x) const noexcept\
    \ {\n    return modint{*this} -= __x;\n  }\n\n  template <class _Tp>\n  constexpr\
    \ friend\n      typename std::enable_if<is_integral_ext<_Tp>::value, modint>::type\n\
    \      operator-(_Tp __x, const modint &__y) noexcept {\n    if (((__x -= __y.value)\
    \ %= mod) < 0) __x += mod;\n    return {__x, direct_ctor_tag};\n  }\n\n  // }}\
    \ operator-\n\n  // operator*= {{\n\n  constexpr modint &operator*=(const modint\
    \ &__x) noexcept {\n    value =\n        static_cast<value_type>(value * static_cast<mul_type>(__x.value)\
    \ % mod);\n    return *this;\n  }\n\n  template <class _Tp>\n  constexpr typename\
    \ std::enable_if<is_integral_ext<_Tp>::value, modint>::type &\n  operator*=(_Tp\
    \ __x) noexcept {\n    value = static_cast<value_type>(\n        value * mul_type((__x\
    \ %= mod) < 0 ? __x + mod : __x) % mod);\n    return *this;\n  }\n\n  // }} operator*=\n\
    \n  // operator* {{\n\n  constexpr modint operator*(const modint &__x) const noexcept\
    \ {\n    return {static_cast<mul_type>(value) * __x.value % mod, direct_ctor_tag};\n\
    \  }\n\n  template <class _Tp>\n  constexpr typename std::enable_if<is_integral_ext<_Tp>::value,\
    \ modint>::type\n  operator*(_Tp __x) const noexcept {\n    __x %= mod;\n    if\
    \ (__x < 0) __x += mod;\n    return {static_cast<mul_type>(value) * __x % mod,\
    \ direct_ctor_tag};\n  }\n\n  template <class _Tp>\n  constexpr friend\n     \
    \ typename std::enable_if<is_integral_ext<_Tp>::value, modint>::type\n      operator*(_Tp\
    \ __x, const modint &__y) noexcept {\n    __x %= mod;\n    if (__x < 0) __x +=\
    \ mod;\n    return {static_cast<mul_type>(__x) * __y.value % mod, direct_ctor_tag};\n\
    \  }\n\n  // }} operator*\n\n protected:\n  static value_type _mem(value_type\
    \ __x) {\n    static std::vector<value_type> __m{0, 1};\n    static value_type\
    \ __i = (__m.reserve(Storage), 1);\n    while (__i < __x) {\n      ++__i;\n  \
    \    __m.emplace_back(mod - mul_type(mod / __i) * __m[mod % __i] % mod);\n   \
    \ }\n    return __m[__x];\n  }\n\n  template <class _Tp>\n  constexpr static\n\
    \      typename std::enable_if<is_integral_ext<_Tp>::value, value_type>::type\n\
    \      _div(mul_type __r, _Tp __x) noexcept {\n    assert(__x != _Tp(0));\n  \
    \  if (!__r) return 0;\n\n    std::make_signed_t<_Tp> __v{};\n    bool __neg =\
    \ __x < 0 ? __x = -__x, true : false;\n\n    if (static_cast<decltype(storage)>(__x)\
    \ < storage)\n      __v = _mem(__x);\n    else {\n      decltype(__v) __y{mod},\
    \ __u{1}, __t;\n\n      while (__x)\n        __t = __y / __x, __y ^= __x ^= (__y\
    \ -= __t * __x) ^= __x,\n        __v ^= __u ^= (__v -= __t * __u) ^= __u;\n\n\
    \      if (__y < 0) __neg ^= 1;\n    }\n\n    if (__neg)\n      __v = 0 < __v\
    \ ? mod - __v : -__v;\n    else if (__v < 0)\n      __v += mod;\n\n    return\
    \ __r == mul_type(1) ? static_cast<value_type>(__v)\n                        \
    \      : static_cast<value_type>(__r * __v % mod);\n  }\n\n public:\n  // operator/=\
    \ {{\n\n  constexpr modint &operator/=(const modint &__x) noexcept {\n    if (value)\
    \ value = _div(value, __x.value);\n    return *this;\n  }\n\n  template <class\
    \ _Tp>\n  constexpr typename std::enable_if<is_integral_ext<_Tp>::value, modint>::type\
    \ &\n  operator/=(_Tp __x) noexcept {\n    if (value) value = _div(value, __x\
    \ %= mod);\n    return *this;\n  }\n\n  // }} operator/=\n\n  // operator/ {{\n\
    \n  constexpr modint operator/(const modint &__x) const noexcept {\n    if (!value)\
    \ return {};\n    return {_div(value, __x.value), direct_ctor_tag};\n  }\n\n \
    \ template <class _Tp>\n  constexpr typename std::enable_if<is_integral_ext<_Tp>::value,\
    \ modint>::type\n  operator/(_Tp __x) const noexcept {\n    if (!value) return\
    \ {};\n    return {_div(value, __x %= mod), direct_ctor_tag};\n  }\n\n  template\
    \ <class _Tp>\n  constexpr friend\n      typename std::enable_if<is_integral_ext<_Tp>::value,\
    \ modint>::type\n      operator/(_Tp __x, const modint &__y) noexcept {\n    if\
    \ (!__x) return {};\n    if ((__x %= mod) < 0) __x += mod;\n    return {_div(__x,\
    \ __y.value), direct_ctor_tag};\n  }\n\n  // }} operator/\n\n  constexpr modint\
    \ inv() const noexcept { return _div(1, value); }\n\n  template <class _Tp>\n\
    \  friend constexpr\n      typename std::enable_if<is_integral_ext<_Tp>::value,\
    \ modint>::type\n      pow(modint __b, _Tp __e) noexcept {\n    if (__e < 0) {\n\
    \      __e = -__e;\n      __b.value = _div(1, __b.value);\n    }\n\n    modint\
    \ __r{1, direct_ctor_tag};\n\n    for (; __e; __e >>= 1, __b *= __b)\n      if\
    \ (__e & 1) __r *= __b;\n\n    return __r;\n  }\n\n  template <class _Tp>\n  constexpr\
    \ typename std::enable_if<is_integral_ext<_Tp>::value, modint>::type\n  pow(_Tp\
    \ __e) const noexcept {\n    modint __r{1, direct_ctor_tag};\n\n    for (modint\
    \ __b{__e < 0 ? __e = -__e, _div(1, value) : value,\n                        \
    \      direct_ctor_tag};\n         __e; __e >>= 1, __b *= __b)\n      if (__e\
    \ & 1) __r *= __b;\n\n    return __r;\n  }\n\n  template <class _Os>\n  friend\
    \ _Os &operator<<(_Os &__os, const modint &__x) noexcept {\n    return __os <<\
    \ __x.value;\n  }\n\n  friend std::istream &operator>>(std::istream &__is, modint\
    \ &__x) noexcept {\n    std::string __s;\n    __is >> __s;\n    bool __neg = false;\n\
    \    if (__s.front() == '-') {\n      __neg = true;\n      __s.erase(__s.begin());\n\
    \    }\n    __x = 0;\n    for (char __c : __s) __x = __x * 10 + (__c - '0');\n\
    \    if (__neg) __x = -__x;\n    return __is;\n  }\n};\n\ntemplate <auto Mod,\
    \ unsigned Storage>\ntypename modint<Mod, Storage>::mod_type modint<Mod, Storage>::mod\
    \ =\n    Mod > 0 ? Mod : 0;\n\ntemplate <auto Mod, unsigned Storage>\nunsigned\
    \ modint<Mod, Storage>::storage = Storage;\n\n}  // namespace _modint_impl\n\n\
    /**\n * @brief Modular arithmetic.\n *\n * @tparam Mod modulus\n * @tparam Storage\
    \ Reserved size for inverse calculation\n */\ntemplate <auto Mod, unsigned Storage\
    \ = 0,\n          typename std::enable_if<(Mod > 0)>::type * = nullptr>\nusing\
    \ modint = _modint_impl::modint<Mod, Storage>;\n\n/**\n * @brief Runtime modular\
    \ arithmetic.\n *\n * @tparam type_id uniquely assigned\n * @tparam Storage Reserved\
    \ size for inverse calculation\n */\ntemplate <unsigned type_id = 0, unsigned\
    \ Storage = 0>\nusing modint_runtime = _modint_impl::modint<-(signed)type_id,\
    \ Storage>;\n\n// #define modint_newtype modint_runtime<__COUNTER__>\n\n}  //\
    \ namespace workspace\n#line 2 \"src/utils/io/istream.hpp\"\n\n/**\n * @file istream.hpp\n\
    \ * @brief Input Stream\n */\n\n#include <cxxabi.h>\n\n#line 12 \"src/utils/io/istream.hpp\"\
    \n#include <tuple>\n\n#line 15 \"src/utils/io/istream.hpp\"\n\nnamespace workspace\
    \ {\n\nnamespace _istream_impl {\n\ntemplate <class _Tp, typename = std::nullptr_t>\
    \ struct istream_helper {\n  istream_helper(std::istream &__is, _Tp &__x) {\n\
    \    if constexpr (has_begin<_Tp>::value)\n      for (auto &&__e : __x)\n    \
    \    istream_helper<std::decay_t<decltype(__e)>>(__is, __e);\n    else\n     \
    \ static_assert(has_begin<_Tp>::value, \"istream unsupported type.\");\n  }\n\
    };\n\ntemplate <class _Tp>\nstruct istream_helper<\n    _Tp,\n    decltype(std::declval<std::decay_t<decltype(\n\
    \                 std::declval<std::istream &>() >> std::declval<_Tp &>())>>(),\n\
    \             nullptr)> {\n  istream_helper(std::istream &__is, _Tp &__x) { __is\
    \ >> __x; }\n};\n\n#ifdef __SIZEOF_INT128__\n\ntemplate <> struct istream_helper<__uint128_t,\
    \ std::nullptr_t> {\n  istream_helper(std::istream &__is, __uint128_t &__x) {\n\
    \    std::string __s;\n    __is >> __s;\n    bool __neg = false;\n    if (__s.front()\
    \ == '-') __neg = true, __s.erase(__s.begin());\n    __x = 0;\n    for (char __d\
    \ : __s) {\n      __x *= 10;\n      __d -= '0';\n      if (__neg)\n        __x\
    \ -= __d;\n      else\n        __x += __d;\n    }\n  }\n};\n\ntemplate <> struct\
    \ istream_helper<__int128_t, std::nullptr_t> {\n  istream_helper(std::istream\
    \ &__is, __int128_t &__x) {\n    std::string __s;\n    __is >> __s;\n    bool\
    \ __neg = false;\n    if (__s.front() == '-') __neg = true, __s.erase(__s.begin());\n\
    \    __x = 0;\n    for (char __d : __s) {\n      __x *= 10;\n      __d -= '0';\n\
    \      if (__neg)\n        __x -= __d;\n      else\n        __x += __d;\n    }\n\
    \  }\n};\n\n#endif  // INT128\n\ntemplate <class T1, class T2> struct istream_helper<std::pair<T1,\
    \ T2>> {\n  istream_helper(std::istream &__is, std::pair<T1, T2> &__x) {\n   \
    \ istream_helper<T1>(__is, __x.first), istream_helper<T2>(__is, __x.second);\n\
    \  }\n};\n\ntemplate <class... Tps> struct istream_helper<std::tuple<Tps...>>\
    \ {\n  istream_helper(std::istream &__is, std::tuple<Tps...> &__x) {\n    iterate(__is,\
    \ __x);\n  }\n\n private:\n  template <class _Tp, size_t N = 0>\n  void iterate(std::istream\
    \ &__is, _Tp &__x) {\n    if constexpr (N == std::tuple_size<_Tp>::value)\n  \
    \    return;\n    else\n      istream_helper<typename std::tuple_element<N, _Tp>::type>(\n\
    \          __is, std::get<N>(__x)),\n          iterate<_Tp, N + 1>(__is, __x);\n\
    \  }\n};\n\n}  // namespace _istream_impl\n\n/**\n * @brief A wrapper class for\
    \ std::istream.\n */\nclass istream : public std::istream {\n public:\n  /**\n\
    \   * @brief Wrapped operator.\n   */\n  template <typename _Tp> istream &operator>>(_Tp\
    \ &__x) {\n    _istream_impl::istream_helper<_Tp>(*this, __x);\n    if (std::istream::fail())\
    \ {\n      static auto once = atexit([] {\n        std::cerr << \"\\n\\033[43m\\\
    033[30mwarning: failed to read \\'\"\n                  << abi::__cxa_demangle(typeid(_Tp).name(),\
    \ 0, 0, 0)\n                  << \"\\'.\\033[0m\\n\\n\";\n      });\n      assert(!once);\n\
    \    }\n    return *this;\n  }\n};\n\ndecltype(auto) cin = static_cast<istream\
    \ &>(std::cin);\n\n}  // namespace workspace\n#line 2 \"src/utils/io/ostream.hpp\"\
    \n\n/**\n * @file ostream.hpp\n * @brief Output Stream\n */\n\n#line 9 \"src/utils/io/ostream.hpp\"\
    \n\nnamespace workspace {\n\ntemplate <class _Os> struct is_ostream {\n  template\
    \ <typename... _Args>\n  static std::true_type __test(std::basic_ostream<_Args...>\
    \ *);\n\n  static std::false_type __test(void *);\n\n  constexpr static bool value\
    \ = decltype(__test(std::declval<_Os *>()))::value;\n};\n\ntemplate <class _Os>\n\
    using ostream_ref =\n    typename std::enable_if<is_ostream<_Os>::value, _Os &>::type;\n\
    \n/**\n * @brief Stream insertion operator for C-style array.\n *\n * @param __os\
    \ Output stream\n * @param __a Array\n * @return Reference to __os.\n */\ntemplate\
    \ <class _Os, class _Tp, size_t _Nm>\ntypename std::enable_if<bool(sizeof(_Tp)\
    \ > 2), ostream_ref<_Os>>::type\noperator<<(_Os &__os, const _Tp (&__a)[_Nm])\
    \ {\n  if constexpr (_Nm) {\n    __os << *__a;\n    for (auto __i = __a + 1, __e\
    \ = __a + _Nm; __i != __e; ++__i)\n      __os << ' ' << *__i;\n  }\n  return __os;\n\
    }\n\n/**\n * @brief Stream insertion operator for std::array.\n *\n * @param __os\
    \ Output stream\n * @param __a Array\n * @return Reference to __os.\n */\ntemplate\
    \ <class _Os, class _Tp, size_t _Nm>\nostream_ref<_Os> operator<<(_Os &__os, const\
    \ std::array<_Tp, _Nm> &__a) {\n  if constexpr (_Nm) {\n    __os << __a[0];\n\
    \    for (size_t __i = 1; __i != _Nm; ++__i) __os << ' ' << __a[__i];\n  }\n \
    \ return __os;\n}\n\n/**\n * @brief Stream insertion operator for std::pair.\n\
    \ *\n * @param __os Output stream\n * @param __p Pair\n * @return Reference to\
    \ __os.\n */\ntemplate <class _Os, class _T1, class _T2>\nostream_ref<_Os> operator<<(_Os\
    \ &__os, const std::pair<_T1, _T2> &__p) {\n  return __os << __p.first << ' '\
    \ << __p.second;\n}\n\n/**\n * @brief Stream insertion operator for std::tuple.\n\
    \ *\n * @param __os Output stream\n * @param __t Tuple\n * @return Reference to\
    \ __os.\n */\ntemplate <class _Os, class _Tp, size_t _Nm = 0>\ntypename std::enable_if<bool(std::tuple_size<_Tp>::value\
    \ + 1),\n                        ostream_ref<_Os>>::type\noperator<<(_Os &__os,\
    \ const _Tp &__t) {\n  if constexpr (_Nm != std::tuple_size<_Tp>::value) {\n \
    \   if constexpr (_Nm) __os << ' ';\n    __os << std::get<_Nm>(__t);\n    operator<<<_Os,\
    \ _Tp, _Nm + 1>(__os, __t);\n  }\n  return __os;\n}\n\ntemplate <class _Os, class\
    \ _Container,\n          typename = decltype(std::begin(std::declval<_Container>()))>\n\
    typename std::enable_if<\n    !std::is_same<std::decay_t<_Container>, std::string>::value\
    \ &&\n        !std::is_same<std::decay_t<_Container>, char *>::value,\n    ostream_ref<_Os>>::type\n\
    operator<<(_Os &__os, const _Container &__cont) {\n  bool __h = true;\n  for (auto\
    \ &&__e : __cont) __h ? __h = 0 : (__os << ' ', 0), __os << __e;\n  return __os;\n\
    }\n\n#ifdef __SIZEOF_INT128__\n\n/**\n * @brief Stream insertion operator for\
    \ __int128_t.\n *\n * @param __os Output Stream\n * @param __x 128-bit integer\n\
    \ * @return Reference to __os.\n */\ntemplate <class _Os> ostream_ref<_Os> operator<<(_Os\
    \ &__os, __int128_t __x) {\n  if (!__x) return __os << '0';\n  if (__x < 0) __os\
    \ << '-';\n  char __s[40], *__p = __s;\n  while (__x) {\n    auto __d = __x %\
    \ 10;\n    *__p++ = '0' + (__x < 0 ? -__d : __d);\n    __x /= 10;\n  }\n  *__p\
    \ = 0;\n  for (char *__t = __s; __t < --__p; ++__t) *__t ^= *__p ^= *__t ^= *__p;\n\
    \  return __os << __s;\n}\n\n/**\n * @brief Stream insertion operator for __uint128_t.\n\
    \ *\n * @param __os Output Stream\n * @param __x 128-bit unsigned integer\n *\
    \ @return Reference to __os.\n */\ntemplate <class _Os> ostream_ref<_Os> operator<<(_Os\
    \ &__os, __uint128_t __x) {\n  if (!__x) return __os << '0';\n  char __s[40],\
    \ *__p = __s;\n  while (__x) *__p++ = '0' + __x % 10, __x /= 10;\n  *__p = 0;\n\
    \  for (char *__t = __s; __t < --__p; ++__t) *__t ^= *__p ^= *__t ^= *__p;\n \
    \ return __os << __s;\n}\n\n#endif\n\n}  // namespace workspace\n#line 9 \"test/library-checker/bitwise_xor_convolution.test.cpp\"\
    \n\nint main() {\n  using namespace workspace;\n  using mint = modint<998244353>;\n\
    \  size_t n;\n  cin >> n;\n  std::vector<mint> a(1 << n), b(1 << n);\n  cin >>\
    \ a >> b;\n  std::cout << bitxor_conv(a, b) << \"\\n\";\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/bitwise_xor_convolution\"\
    \n\n#include <vector>\n\n#include \"src/algebra/convolution/bitxor.hpp\"\n#include\
    \ \"src/modular/modint.hpp\"\n#include \"src/utils/io/istream.hpp\"\n#include\
    \ \"src/utils/io/ostream.hpp\"\n\nint main() {\n  using namespace workspace;\n\
    \  using mint = modint<998244353>;\n  size_t n;\n  cin >> n;\n  std::vector<mint>\
    \ a(1 << n), b(1 << n);\n  cin >> a >> b;\n  std::cout << bitxor_conv(a, b) <<\
    \ \"\\n\";\n}\n"
  dependsOn:
  - src/algebra/convolution/bitxor.hpp
  - src/modular/modint.hpp
  - src/utils/sfinae.hpp
  - src/utils/io/istream.hpp
  - src/utils/io/ostream.hpp
  isVerificationFile: true
  path: test/library-checker/bitwise_xor_convolution.test.cpp
  requiredBy: []
  timestamp: '2021-04-11 21:05:14+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/library-checker/bitwise_xor_convolution.test.cpp
layout: document
redirect_from:
- /verify/test/library-checker/bitwise_xor_convolution.test.cpp
- /verify/test/library-checker/bitwise_xor_convolution.test.cpp.html
title: test/library-checker/bitwise_xor_convolution.test.cpp
---