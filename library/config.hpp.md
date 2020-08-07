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
<script type="text/javascript" src="../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../assets/css/copy-button.css" />


# :warning: config.hpp

<a href="../index.html">Back to top page</a>

* category: <a href="../index.html#5058f1af8388633f609cadb75a75dc9d">.</a>
* <a href="{{ site.github.repository_url }}/blob/master/config.hpp">View this file on GitHub</a>
    - Last commit date: 2020-08-06 05:02:44+09:00




## Required by

* :warning: <a href="template.cpp.html">template.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include <chrono>
#include <iostream>
#include <iomanip>
namespace config
{
    const auto start_time{std::chrono::system_clock::now()};
    int64_t elapsed()
    {
        using namespace std::chrono;
        const auto end_time{system_clock::now()};
        return duration_cast<milliseconds>(end_time - start_time).count();
    }
    __attribute__((constructor)) void setup()
    {
        using namespace std;
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        cout << fixed << setprecision(15);
        #ifdef _buffer_check
            atexit([]{ ofstream cnsl("CON"); char bufc; if(cin >> bufc) cnsl << "\n\033[1;35mwarning\033[0m: buffer not empty.\n\n"; });
        #endif
    }
    unsigned cases(void);
    template <class C> void main() { for(unsigned t = cases(); t; --t) C(); }
}
struct solver; int main() { config::main<solver>(); }

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "config.hpp"
#include <chrono>
#include <iostream>
#include <iomanip>
namespace config
{
    const auto start_time{std::chrono::system_clock::now()};
    int64_t elapsed()
    {
        using namespace std::chrono;
        const auto end_time{system_clock::now()};
        return duration_cast<milliseconds>(end_time - start_time).count();
    }
    __attribute__((constructor)) void setup()
    {
        using namespace std;
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        cout << fixed << setprecision(15);
        #ifdef _buffer_check
            atexit([]{ ofstream cnsl("CON"); char bufc; if(cin >> bufc) cnsl << "\n\033[1;35mwarning\033[0m: buffer not empty.\n\n"; });
        #endif
    }
    unsigned cases(void);
    template <class C> void main() { for(unsigned t = cases(); t; --t) C(); }
}
struct solver; int main() { config::main<solver>(); }

```
{% endraw %}

<a href="../index.html">Back to top page</a>
