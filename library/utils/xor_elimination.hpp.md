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


# :warning: utils/xor_elimination.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#2b3583e6e17721c54496bd04e57a0c15">utils</a>
* <a href="{{ site.github.repository_url }}/blob/master/utils/xor_elimination.hpp">View this file on GitHub</a>
    - Last commit date: 2020-07-08 02:35:35+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include <vector>

template <class expr>
struct xor_elimination
{
    std::vector<expr> base;
    bool add(expr e)
    {
        for(const expr &b : base) if((b ^ e) < e) e ^= b;
        if(e) base.emplace_back(e);
        return e;
    }
    size_t dim() const { return base.size(); }
}; // struct binary_elimination
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "utils/xor_elimination.hpp"
#include <vector>

template <class expr>
struct xor_elimination
{
    std::vector<expr> base;
    bool add(expr e)
    {
        for(const expr &b : base) if((b ^ e) < e) e ^= b;
        if(e) base.emplace_back(e);
        return e;
    }
    size_t dim() const { return base.size(); }
}; // struct binary_elimination

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

