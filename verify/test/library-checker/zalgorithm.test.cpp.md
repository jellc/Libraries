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


# :heavy_check_mark: test/library-checker/zalgorithm.test.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#8a40f8ed03f4cdb6c2fe0a2d4731a143">test/library-checker</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/library-checker/zalgorithm.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-08-03 01:03:44+09:00


* see: <a href="https://judge.yosupo.jp/problem/zalgorithm">https://judge.yosupo.jp/problem/zalgorithm</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/string/Z_algorithm.hpp.html">string/Z_algorithm.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/zalgorithm"
#include "../../string/Z_algorithm.hpp"
#include <bits/stdc++.h>

int main()
{
    std::string s;
    std::cin>>s;
    Z_algorithm z(s);
    for(int e: z) printf(" %d",e);
    puts("");
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/library-checker/zalgorithm.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/zalgorithm"
#line 1 "string/Z_algorithm.hpp"



#include <string>
#include <vector>

template <class str_type = std::string>
class Z_algorithm
{
    str_type key;
    std::vector<size_t> z;

    void make()
    {
        if(z.empty()) return;
        for(size_t i{1}, j{0}; i != size(); ++i)
        {
            if(z[i - j] + i < z[j] + j)
            {
                z[i] = z[i - j];
            }
            else
            {
                size_t k{z[j] + j > i ? z[j] + j - i : 0};
                while(k + i < size() && key[k] == key[k + i]) ++k;
                z[i] = k;
                j = i;
            }
        }
        z.front() = size();
    }

public:
    Z_algorithm(const str_type &key) : key(key), z(size()) { make(); }

    std::vector<size_t>::const_iterator begin() const { return z.begin(); }
    std::vector<size_t>::const_iterator end() const { return z.end(); }

    size_t size() const { return key.size(); }

    size_t operator[](size_t i) { assert(i < size()); return z[i]; }

    std::vector<size_t> pattern_search(const str_type &str) const
    {
        str_type ccat(key);
        ccat.insert(end(ccat), begin(str), end(str));
        Z_algorithm z(ccat);
        std::vector<size_t> res(z.begin() + size(), z.end());
        for(size_t &x : res) if(x > size()) x = size();
        return res;
    }
};


#line 3 "test/library-checker/zalgorithm.test.cpp"
#include <bits/stdc++.h>

int main()
{
    std::string s;
    std::cin>>s;
    Z_algorithm z(s);
    for(int e: z) printf(" %d",e);
    puts("");
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>
