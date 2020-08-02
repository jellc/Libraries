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
<script type="text/javascript" src="../../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../../assets/css/copy-button.css" />


# :warning: combinatorics/compile-time/binomial.hpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#dfc668f450222e8dc05cbabf0a30df41">combinatorics/compile-time</a>
* <a href="{{ site.github.repository_url }}/blob/master/combinatorics/compile-time/binomial.hpp">View this file on GitHub</a>
    - Last commit date: 2020-05-18 14:28:16+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#ifndef modint_hpp
#define modint_hpp
#include <cassert>
#include <iostream>

template <int mod>
class modint
{
    int val;
public:
    constexpr long long value() const noexcept { return val; }
    constexpr modint() noexcept : val{0} {}
    constexpr modint(long long x) noexcept : val((x %= mod) < 0 ? mod + x : x) {}
    constexpr modint operator++(int) noexcept { modint t = *this; return ++val, t; }
    constexpr modint operator--(int) noexcept { modint t = *this; return --val, t; }
    constexpr modint &operator++() noexcept { return ++val, *this; }
    constexpr modint &operator--() noexcept { return --val, *this; }
    constexpr modint operator-() const noexcept { return modint(-val); }
    constexpr modint &operator+=(const modint &other) noexcept { return (val += other.val) < mod ? 0 : val -= mod, *this; }
    constexpr modint &operator-=(const modint &other) noexcept { return (val += mod - other.val) < mod ? 0 : val -= mod, *this; }
    constexpr modint &operator*=(const modint &other) noexcept { return val = (long long)val * other.val % mod, *this; }
    constexpr modint &operator/=(const modint &other) noexcept { return *this *= inverse(other); }
    constexpr modint operator+(const modint &other) const noexcept { return modint(*this) += other; }
    constexpr modint operator-(const modint &other) const noexcept { return modint(*this) -= other; }
    constexpr modint operator*(const modint &other) const noexcept { return modint(*this) *= other; }
    constexpr modint operator/(const modint &other) const noexcept { return modint(*this) /= other; }
    constexpr bool operator==(const modint &other) const noexcept { return val == other.val; }
    constexpr bool operator!=(const modint &other) const noexcept { return val != other.val; }
    constexpr bool operator!() const noexcept { return !val; }
    friend constexpr modint operator+(long long x, modint y) noexcept { return modint(x) + y; }
    friend constexpr modint operator-(long long x, modint y) noexcept { return modint(x) - y; }
    friend constexpr modint operator*(long long x, modint y) noexcept { return modint(x) * y; }
    friend constexpr modint operator/(long long x, modint y) noexcept { return modint(x) / y; }
    static constexpr modint inverse(const modint &other) noexcept
    {
        assert(other != 0);
        int a{mod}, b{other.val}, u{}, v{1}, t{};
        while(b) t = a / b, a ^= b ^= (a -= t * b) ^= b, u ^= v ^= (u -= t * v) ^= v;
        return {u};
    }
    static constexpr modint pow(modint other, long long e) noexcept
    {
        if(e < 0) e = e % (mod - 1) + mod - 1;
        modint res{1};
        while(e) { if(e & 1) res *= other; other *= other, e >>= 1; }
        return res;
    }
    friend std::ostream &operator<<(std::ostream &os, const modint &other) noexcept { return os << other.val; }
    friend std::istream &operator>>(std::istream &is, modint &other) noexcept { long long val; other = {(is >> val, val)}; return is; }
}; // class modint

#endif // modint_hpp

#ifndef binomial_hpp
#define binomial_hpp

namespace binomial
{
    constexpr int mod = 998244353;
    constexpr int size = 1 << 20;
    using mint = modint<mod>;
    namespace
    {
        namespace internal_helper
        {
            struct fact_impl
            {
                int _fact[size], _inv[size], _invfact[size];
                fact_impl() : _fact{1}, _inv{0, 1}, _invfact{1}
                {
                    for(int i = 1; i < size; ++i) _fact[i] = (long long)_fact[i - 1] * i % mod;
                    for(int i = 2; i < size; ++i) _inv[i] = mod - (long long)mod / i * _inv[mod % i] % mod;
                    for(int i = 1; i < size; ++i) _invfact[i] = (long long)_invfact[i - 1] * _inv[i] % mod;
                }
            } fact_calced;
        } // namespace internal_helper
        mint fact(int x) noexcept { assert(x < size); return x < 0 ? 0 : internal_helper::fact_calced._fact[x]; }
        mint invfact(int x) noexcept { assert(x < size); return x < 0 ? 0 : internal_helper::fact_calced._invfact[x]; }
        mint inv(int x) noexcept { assert(x < size); return x < 0 ? 0 : internal_helper::fact_calced._inv[x]; }
    } // unnamed namespace
    mint binom(int n, int k) noexcept { return fact(n) * invfact(k) * invfact(n - k); }
    mint fallfact(int n, int k) noexcept { return fact(n) * invfact(n - k); }
    mint risefact(int n, int k) noexcept { return fallfact(n + k - 1, k); }
    // time complexity: O(min(n, k) * log(n))
    mint stirling_2nd(int n, int k) noexcept
    {
        if(n < k) return 0;
        mint res{};
        for(int i{}, j{k}; j >= 0; ++i, --j)
            if(i & 1) res -= mint::pow(j, n) * invfact(j) * invfact(i);
            else res += mint::pow(j, n) * invfact(j) * invfact(i);
        return res;
    };
    // time complexity: O(min(n, k) * log(n))
    mint bell(int n, int k) noexcept
    {
        if(n < k) k = n;
        mint res{}, alt{};
        for(int i{}, j{k}; j >= 0; ++i, --j)
        {
            if(i & 1) alt -= invfact(i);
            else alt += invfact(i);
            res += alt * mint::pow(j, n) * invfact(j);
        }
        return res;
    }
    namespace internal_helper {} // namespace internal_helper
} // namespace binomial

#endif // binomial_hpp
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
Traceback (most recent call last):
  File "/opt/hostedtoolcache/Python/3.8.5/x64/lib/python3.8/site-packages/onlinejudge_verify/docs.py", line 349, in write_contents
    bundled_code = language.bundle(self.file_class.file_path, basedir=pathlib.Path.cwd())
  File "/opt/hostedtoolcache/Python/3.8.5/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus.py", line 185, in bundle
    bundler.update(path)
  File "/opt/hostedtoolcache/Python/3.8.5/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py", line 282, in update
    raise BundleErrorAt(path, i + 1, "found codes out of include guard")
onlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: combinatorics/compile-time/binomial.hpp: line 53: found codes out of include guard

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>
