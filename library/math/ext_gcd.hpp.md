---
layout: default
---

<!-- mathjax config similar to math.stackexchange -->
<script type="text/javascript" async
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/MathJax.js?config=TeX-MML-AM_CHTML">
</script>
<script type="text/x-mathjax-config">
  MathJax.Hub.Config({
    TeX: { equationNumbers: { autoNumber: "AMS" }},
    tex2jax: {
      inlineMath: [ ['$','$'] ],
      processEscapes: true
    },
    "HTML-CSS": { matchFontHeight: false },
    displayAlign: "left",
    displayIndent: "2em"
  });
</script>

<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/jquery-balloon-js@1.1.2/jquery.balloon.min.js" integrity="sha256-ZEYs9VrgAeNuPvs15E39OsyOJaIkXEEt10fzxJ20+2I=" crossorigin="anonymous"></script>
<script type="text/javascript" src="../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../assets/css/copy-button.css" />


# :heavy_check_mark: math/ext_gcd.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#7e676e9e663beb40fd133f5ee24487c2">math</a>
* <a href="{{ site.github.repository_url }}/blob/master/math/ext_gcd.hpp">View this file on GitHub</a>
    - Last commit date: 2020-08-11 16:02:40+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/test/aizu-online-judge/extended_euclid_algorithm.test.cpp.html">test/aizu-online-judge/extended_euclid_algorithm.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once
#include <tuple>
template <class int_type, std::enable_if_t<std::is_integral<int_type>::value, std::nullptr_t> = nullptr>
constexpr std::pair<int_type, int_type> ext_gcd(int_type a, int_type b)
{
    bool neg_a = a < 0, neg_b = b < 0;
    int_type p{1}, q{}, r{}, s{1}, t{};
    while(b)
    {
        r ^= p ^= r ^= p -= (t = a / b) * r;
        s ^= q ^= s ^= q -= t * s;
        b ^= a ^= b ^= a %= b;
    }
    return {neg_a ? -p : p, neg_b ? -q : q};
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "math/ext_gcd.hpp"
#include <tuple>
template <class int_type, std::enable_if_t<std::is_integral<int_type>::value, std::nullptr_t> = nullptr>
constexpr std::pair<int_type, int_type> ext_gcd(int_type a, int_type b)
{
    bool neg_a = a < 0, neg_b = b < 0;
    int_type p{1}, q{}, r{}, s{1}, t{};
    while(b)
    {
        r ^= p ^= r ^= p -= (t = a / b) * r;
        s ^= q ^= s ^= q -= t * s;
        b ^= a ^= b ^= a %= b;
    }
    return {neg_a ? -p : p, neg_b ? -q : q};
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>
