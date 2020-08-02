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


# :warning: combinatorics/runtime/modint_runtime.hpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#16433cc04c471e1e6dbf9e346eeaab28">combinatorics/runtime</a>
* <a href="{{ site.github.repository_url }}/blob/master/combinatorics/runtime/modint_runtime.hpp">View this file on GitHub</a>
    - Last commit date: 2020-05-09 13:53:51+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#ifndef modint_runtime_hpp
#define modint_runtime_hpp
#include <cassert>
#include <iostream>

//*
// modulo statically fixed
class modint_runtime
{
    long long val;
    friend std::ostream &operator<<(std::ostream &os, const modint_runtime &other) noexcept { return os << other.val; }
    friend std::istream &operator>>(std::istream &is, modint_runtime &other) noexcept { long long val; other = modint_runtime((is >> val, val)); return is; }
public:
    static long long &mod() noexcept { static long long mod{}; return mod; }
    static long long identity() noexcept { return 1; }
    modint_runtime(long long x = 0) : val{(x %= mod()) < 0 ? x + mod() : x} {}
    long long value() const noexcept { return val; }
    modint_runtime operator++(int) noexcept { modint_runtime t = *this; return ++*this, t; }
    modint_runtime &operator++() noexcept { return ++val != mod() ? *this : (val = 0, *this); }
    modint_runtime operator--(int) noexcept { modint_runtime t = *this; return --*this, t; }
    modint_runtime &operator--() noexcept { return --val < 0 ? (val += mod(), *this) : *this; }
    modint_runtime &operator=(long long other) noexcept { return val = (other %= mod()) < 0 ? other + mod() : other, *this; }
    modint_runtime &operator+=(long long other) noexcept { return (val += other % mod()) < mod() ? 0 : val -= mod(), *this; }
    modint_runtime &operator+=(const modint_runtime &other) noexcept { return (val += other.val) < mod() ? 0 : val -= mod(), *this; }
    modint_runtime &operator-=(long long other) noexcept { return (val += mod() - other % mod()) < mod() ? 0 : val -= mod(), *this; }
    modint_runtime &operator-=(const modint_runtime &other) noexcept { return (val += mod() - other.val) < mod() ? 0 : val -= mod(), *this; }
    modint_runtime &operator*=(long long other) noexcept { return (val *= other % mod()) %= mod(), *this; }
    modint_runtime &operator*=(const modint_runtime &other) noexcept { return (val *= other.val) %= mod(), *this; }
    modint_runtime &operator/=(long long other) noexcept { return *this *= inverse(other); }
    modint_runtime &operator/=(const modint_runtime &other) noexcept { return *this *= inverse(other); }
    modint_runtime operator-() const noexcept { return modint_runtime(-val); }
    modint_runtime operator+(const modint_runtime &other) const noexcept { return modint_runtime{*this} += other; }
    modint_runtime operator-(const modint_runtime &other) const noexcept { return modint_runtime{*this} -= other; }
    modint_runtime operator*(const modint_runtime &other) const noexcept { return modint_runtime{*this} *= other; }
    modint_runtime operator/(const modint_runtime &other) const noexcept { return modint_runtime{*this} /= other; }
    bool operator==(const modint_runtime &other) const noexcept { return val == other.val; }
    bool operator!=(const modint_runtime &other) const noexcept { return val != other.val; }
    bool operator!() const noexcept { return !val; }
    friend modint_runtime operator+(long long x, modint_runtime y) noexcept { return {x + y.val}; }
    friend modint_runtime operator-(long long x, modint_runtime y) noexcept { return {x - y.val}; }
    friend modint_runtime operator*(long long x, modint_runtime y) noexcept { return {x % mod() * y.val}; }
    friend modint_runtime operator/(long long x, modint_runtime y) noexcept { return {x % mod() * inverse(y).val}; }
    static modint_runtime inverse(const modint_runtime &other) noexcept
    {
        assert(mod() && other.val);
        long long a{mod()}, b{other.val}, u{}, v{1}, t{};
        while(b) t = a / b, a ^= b ^= (a -= t * b) ^= b, u ^= v ^= (u -= t * v) ^= v;
        return {u};
    }
    static modint_runtime pow(modint_runtime other, long long e) noexcept
    {
        if(e < 0) e = e % (mod() - 1) + mod() - 1;
        modint_runtime res{1};
        while(e) { if(e & 1) res *= other; other *= other, e >>= 1; }
        return res;
    }
}; // class modint_runtime

/*/
// modulo individually set
class modint_runtime
{
    long long val;
    int mod;
    friend constexpr bool mod_same(const modint_runtime &x, const modint_runtime &y) { return x.mod == y.mod; }
public:
    constexpr modint_runtime(long long x) : val(x), mod{} {}
    constexpr modint_runtime(long long x, int _mod) noexcept : val((x %= _mod) < 0 ? x + _mod : x), mod(_mod) {}
    constexpr bool mod_set() const noexcept { return mod; }
    constexpr long long value() const noexcept { return val; }
    constexpr int modulo() const noexcept { return mod; }
    constexpr modint_runtime operator++(int) noexcept { modint_runtime t = *this; return ++val, t; }
    constexpr modint_runtime &operator++() noexcept { return ++val, *this; }
    constexpr modint_runtime operator--(int) noexcept { modint_runtime t = *this; return --val, t; }
    constexpr modint_runtime &operator--() noexcept { return --val, *this; }
    constexpr modint_runtime &operator=(long long other) noexcept { return val = (other %= mod) < 0 ? other + mod : other, *this; }
    constexpr modint_runtime &operator+=(long long other) noexcept { return (val += other % mod) < mod ? 0 : val -= mod, *this; }
    constexpr modint_runtime &operator+=(const modint_runtime &other) noexcept { assert(mod_same(*this, other)); return (val += other.val) < mod ? 0 : val -= mod, *this; }
    constexpr modint_runtime &operator-=(long long other) noexcept { return (val += mod - other % mod) < mod ? 0 : val -= mod, *this; }
    constexpr modint_runtime &operator-=(const modint_runtime &other) noexcept { assert(mod_same(*this, other)); return (val += mod - other.val) < mod ? 0 : val -= mod, *this; }
    constexpr modint_runtime &operator*=(long long other) noexcept { return (val *= other % mod) %= mod, *this; }
    constexpr modint_runtime &operator*=(const modint_runtime &other) noexcept { assert(mod_same(*this, other)); return (val *= other.val) %= mod, *this; }
    constexpr modint_runtime &operator/=(long long other) noexcept { return *this *= inverse(modint_runtime{other, mod}); }
    constexpr modint_runtime &operator/=(const modint_runtime &other) noexcept { assert(mod_same(*this, other)); return *this *= inverse(other); }
    constexpr modint_runtime operator-() const noexcept { return modint_runtime(-val); }
    template <typename T> constexpr modint_runtime operator+(const T &other) const noexcept { return modint_runtime(*this) += other; }
    template <typename T> constexpr modint_runtime operator-(const T &other) const noexcept { return modint_runtime(*this) -= other; }
    template <typename T> constexpr modint_runtime operator*(const T &other) const noexcept { return modint_runtime(*this) *= other; }
    template <typename T> constexpr modint_runtime operator/(const T &other) const noexcept { return modint_runtime(*this) /= other; }
    constexpr bool operator==(const modint_runtime &other) const noexcept { assert(mod_same(*this, other)); return val == other.val; }
    constexpr bool operator!=(const modint_runtime &other) const noexcept { assert(mod_same(*this, other)); return val != other.val; }
    constexpr bool operator!() const noexcept { return !val; }
    friend constexpr modint_runtime operator+(long long x, modint_runtime y) noexcept { return modint_runtime(x + y.val, y.mod); }
    friend constexpr modint_runtime operator-(long long x, modint_runtime y) noexcept { return modint_runtime(x - y.val, y.mod); }
    friend constexpr modint_runtime operator*(long long x, modint_runtime y) noexcept { return modint_runtime(x % y.mod * y.val, y.mod); }
    friend constexpr modint_runtime operator/(long long x, modint_runtime y) noexcept { return modint_runtime(x % y.mod * inverse(y).val, y.mod); }
    friend constexpr modint_runtime inverse(const modint_runtime &other) noexcept
    {
        assert(other.mod && other.val);
        long long a{other.mod}, b{other.val}, u{}, v{1}, t{};
        while(b) t = a / b, a ^= b ^= (a -= t * b) ^= b, u ^= v ^= (u -= t * v) ^= v;
        return {u, other.mod};
    }
    friend constexpr modint_runtime pow(modint_runtime other, long long e) noexcept
    {
        if(e < 0) e = e % (other.mod - 1) + other.mod - 1;
        modint_runtime res{1, other.mod};
        while(e) { if(e & 1) res *= other; other *= other, e >>= 1; }
        return res;
    }
    friend std::ostream &operator<<(std::ostream &os, const modint_runtime &other) noexcept { return os << other.val; }
    friend std::istream &operator>>(std::istream &is, modint_runtime &other) noexcept { long long val; other = modint_runtime((is >> val, val)); return is; }
}; // class modint_runtime
//*/

#endif // modint_runtime_hpp
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "combinatorics/runtime/modint_runtime.hpp"


#include <cassert>
#include <iostream>

//*
// modulo statically fixed
class modint_runtime
{
    long long val;
    friend std::ostream &operator<<(std::ostream &os, const modint_runtime &other) noexcept { return os << other.val; }
    friend std::istream &operator>>(std::istream &is, modint_runtime &other) noexcept { long long val; other = modint_runtime((is >> val, val)); return is; }
public:
    static long long &mod() noexcept { static long long mod{}; return mod; }
    static long long identity() noexcept { return 1; }
    modint_runtime(long long x = 0) : val{(x %= mod()) < 0 ? x + mod() : x} {}
    long long value() const noexcept { return val; }
    modint_runtime operator++(int) noexcept { modint_runtime t = *this; return ++*this, t; }
    modint_runtime &operator++() noexcept { return ++val != mod() ? *this : (val = 0, *this); }
    modint_runtime operator--(int) noexcept { modint_runtime t = *this; return --*this, t; }
    modint_runtime &operator--() noexcept { return --val < 0 ? (val += mod(), *this) : *this; }
    modint_runtime &operator=(long long other) noexcept { return val = (other %= mod()) < 0 ? other + mod() : other, *this; }
    modint_runtime &operator+=(long long other) noexcept { return (val += other % mod()) < mod() ? 0 : val -= mod(), *this; }
    modint_runtime &operator+=(const modint_runtime &other) noexcept { return (val += other.val) < mod() ? 0 : val -= mod(), *this; }
    modint_runtime &operator-=(long long other) noexcept { return (val += mod() - other % mod()) < mod() ? 0 : val -= mod(), *this; }
    modint_runtime &operator-=(const modint_runtime &other) noexcept { return (val += mod() - other.val) < mod() ? 0 : val -= mod(), *this; }
    modint_runtime &operator*=(long long other) noexcept { return (val *= other % mod()) %= mod(), *this; }
    modint_runtime &operator*=(const modint_runtime &other) noexcept { return (val *= other.val) %= mod(), *this; }
    modint_runtime &operator/=(long long other) noexcept { return *this *= inverse(other); }
    modint_runtime &operator/=(const modint_runtime &other) noexcept { return *this *= inverse(other); }
    modint_runtime operator-() const noexcept { return modint_runtime(-val); }
    modint_runtime operator+(const modint_runtime &other) const noexcept { return modint_runtime{*this} += other; }
    modint_runtime operator-(const modint_runtime &other) const noexcept { return modint_runtime{*this} -= other; }
    modint_runtime operator*(const modint_runtime &other) const noexcept { return modint_runtime{*this} *= other; }
    modint_runtime operator/(const modint_runtime &other) const noexcept { return modint_runtime{*this} /= other; }
    bool operator==(const modint_runtime &other) const noexcept { return val == other.val; }
    bool operator!=(const modint_runtime &other) const noexcept { return val != other.val; }
    bool operator!() const noexcept { return !val; }
    friend modint_runtime operator+(long long x, modint_runtime y) noexcept { return {x + y.val}; }
    friend modint_runtime operator-(long long x, modint_runtime y) noexcept { return {x - y.val}; }
    friend modint_runtime operator*(long long x, modint_runtime y) noexcept { return {x % mod() * y.val}; }
    friend modint_runtime operator/(long long x, modint_runtime y) noexcept { return {x % mod() * inverse(y).val}; }
    static modint_runtime inverse(const modint_runtime &other) noexcept
    {
        assert(mod() && other.val);
        long long a{mod()}, b{other.val}, u{}, v{1}, t{};
        while(b) t = a / b, a ^= b ^= (a -= t * b) ^= b, u ^= v ^= (u -= t * v) ^= v;
        return {u};
    }
    static modint_runtime pow(modint_runtime other, long long e) noexcept
    {
        if(e < 0) e = e % (mod() - 1) + mod() - 1;
        modint_runtime res{1};
        while(e) { if(e & 1) res *= other; other *= other, e >>= 1; }
        return res;
    }
}; // class modint_runtime

/*/
// modulo individually set
class modint_runtime
{
    long long val;
    int mod;
    friend constexpr bool mod_same(const modint_runtime &x, const modint_runtime &y) { return x.mod == y.mod; }
public:
    constexpr modint_runtime(long long x) : val(x), mod{} {}
    constexpr modint_runtime(long long x, int _mod) noexcept : val((x %= _mod) < 0 ? x + _mod : x), mod(_mod) {}
    constexpr bool mod_set() const noexcept { return mod; }
    constexpr long long value() const noexcept { return val; }
    constexpr int modulo() const noexcept { return mod; }
    constexpr modint_runtime operator++(int) noexcept { modint_runtime t = *this; return ++val, t; }
    constexpr modint_runtime &operator++() noexcept { return ++val, *this; }
    constexpr modint_runtime operator--(int) noexcept { modint_runtime t = *this; return --val, t; }
    constexpr modint_runtime &operator--() noexcept { return --val, *this; }
    constexpr modint_runtime &operator=(long long other) noexcept { return val = (other %= mod) < 0 ? other + mod : other, *this; }
    constexpr modint_runtime &operator+=(long long other) noexcept { return (val += other % mod) < mod ? 0 : val -= mod, *this; }
    constexpr modint_runtime &operator+=(const modint_runtime &other) noexcept { assert(mod_same(*this, other)); return (val += other.val) < mod ? 0 : val -= mod, *this; }
    constexpr modint_runtime &operator-=(long long other) noexcept { return (val += mod - other % mod) < mod ? 0 : val -= mod, *this; }
    constexpr modint_runtime &operator-=(const modint_runtime &other) noexcept { assert(mod_same(*this, other)); return (val += mod - other.val) < mod ? 0 : val -= mod, *this; }
    constexpr modint_runtime &operator*=(long long other) noexcept { return (val *= other % mod) %= mod, *this; }
    constexpr modint_runtime &operator*=(const modint_runtime &other) noexcept { assert(mod_same(*this, other)); return (val *= other.val) %= mod, *this; }
    constexpr modint_runtime &operator/=(long long other) noexcept { return *this *= inverse(modint_runtime{other, mod}); }
    constexpr modint_runtime &operator/=(const modint_runtime &other) noexcept { assert(mod_same(*this, other)); return *this *= inverse(other); }
    constexpr modint_runtime operator-() const noexcept { return modint_runtime(-val); }
    template <typename T> constexpr modint_runtime operator+(const T &other) const noexcept { return modint_runtime(*this) += other; }
    template <typename T> constexpr modint_runtime operator-(const T &other) const noexcept { return modint_runtime(*this) -= other; }
    template <typename T> constexpr modint_runtime operator*(const T &other) const noexcept { return modint_runtime(*this) *= other; }
    template <typename T> constexpr modint_runtime operator/(const T &other) const noexcept { return modint_runtime(*this) /= other; }
    constexpr bool operator==(const modint_runtime &other) const noexcept { assert(mod_same(*this, other)); return val == other.val; }
    constexpr bool operator!=(const modint_runtime &other) const noexcept { assert(mod_same(*this, other)); return val != other.val; }
    constexpr bool operator!() const noexcept { return !val; }
    friend constexpr modint_runtime operator+(long long x, modint_runtime y) noexcept { return modint_runtime(x + y.val, y.mod); }
    friend constexpr modint_runtime operator-(long long x, modint_runtime y) noexcept { return modint_runtime(x - y.val, y.mod); }
    friend constexpr modint_runtime operator*(long long x, modint_runtime y) noexcept { return modint_runtime(x % y.mod * y.val, y.mod); }
    friend constexpr modint_runtime operator/(long long x, modint_runtime y) noexcept { return modint_runtime(x % y.mod * inverse(y).val, y.mod); }
    friend constexpr modint_runtime inverse(const modint_runtime &other) noexcept
    {
        assert(other.mod && other.val);
        long long a{other.mod}, b{other.val}, u{}, v{1}, t{};
        while(b) t = a / b, a ^= b ^= (a -= t * b) ^= b, u ^= v ^= (u -= t * v) ^= v;
        return {u, other.mod};
    }
    friend constexpr modint_runtime pow(modint_runtime other, long long e) noexcept
    {
        if(e < 0) e = e % (other.mod - 1) + other.mod - 1;
        modint_runtime res{1, other.mod};
        while(e) { if(e & 1) res *= other; other *= other, e >>= 1; }
        return res;
    }
    friend std::ostream &operator<<(std::ostream &os, const modint_runtime &other) noexcept { return os << other.val; }
    friend std::istream &operator>>(std::istream &is, modint_runtime &other) noexcept { long long val; other = modint_runtime((is >> val, val)); return is; }
}; // class modint_runtime
//*/



```
{% endraw %}

<a href="../../../index.html">Back to top page</a>
