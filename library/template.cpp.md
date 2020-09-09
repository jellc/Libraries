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


# :warning: template.cpp

<a href="../index.html">Back to top page</a>

* category: <a href="../index.html#5058f1af8388633f609cadb75a75dc9d">.</a>
* <a href="{{ site.github.repository_url }}/blob/master/template.cpp">View this file on GitHub</a>
    - Last commit date: 2020-09-09 06:36:03+09:00




## Depends on

* :warning: <a href="config.hpp.html">config.hpp</a>
* :warning: <a href="gcc_builtin.hpp.html">gcc_builtin.hpp</a>
* :warning: <a href="gcc_option.hpp.html">gcc_option.hpp</a>
* :heavy_check_mark: <a href="utils/binary_search.hpp.html">utils/binary_search.hpp</a>
* :warning: <a href="utils/casefmt.hpp.html">utils/casefmt.hpp</a>
* :warning: <a href="utils/chval.hpp.html">utils/chval.hpp</a>
* :warning: <a href="utils/fixed_point.hpp.html">utils/fixed_point.hpp</a>
* :heavy_check_mark: <a href="utils/hash.hpp.html">utils/hash.hpp</a>
* :heavy_check_mark: <a href="utils/read.hpp.html">utils/read.hpp</a>
* :question: <a href="utils/sfinae.hpp.html">utils/sfinae.hpp</a>
* :heavy_check_mark: <a href="utils/stream.hpp.html">utils/stream.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include <bits/extc++.h>

#include "config.hpp"
#include "gcc_builtin.hpp"
#include "gcc_option.hpp"
#include "utils/binary_search.hpp"
#include "utils/casefmt.hpp"
#include "utils/chval.hpp"
#include "utils/fixed_point.hpp"
#include "utils/hash.hpp"
#include "utils/read.hpp"
#include "utils/stream.hpp"

namespace workspace {
constexpr char eol = '\n';
using namespace std;
using i64 = int_least64_t;
using p32 = pair<int, int>;
using p64 = pair<i64, i64>;
template <class T, class Comp = std::less<T>>
using priority_queue = std::priority_queue<T, std::vector<T>, Comp>;
template <class T> using stack = std::stack<T, std::vector<T>>;
struct solver;
}  // namespace workspace
int main() { config::main<workspace::solver>(); }
unsigned config::cases() {
  // return -1; // not specify
  // int t; std::cin >> t; return t; // given
  return 1;
}

struct workspace::solver {
  solver() {
    // start here!
  }
};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "template.cpp"
#include <bits/extc++.h>

#line 5 "config.hpp"
namespace config {
const auto start_time{std::chrono::system_clock::now()};
int64_t elapsed() {
  using namespace std::chrono;
  const auto end_time{system_clock::now()};
  return duration_cast<milliseconds>(end_time - start_time).count();
}
__attribute__((constructor)) void setup() {
  using namespace std;
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout << fixed << setprecision(15);
#ifdef _buffer_check
  atexit([] {
    char bufc;
    if (cin >> bufc)
      cerr << "\n\033[43m\033[30mwarning: buffer not empty.\033[0m\n\n";
  });
#endif
}
unsigned cases(void), caseid = 1;
template <class C> void main() {
  for (const unsigned total = cases(); caseid <= total; ++caseid) C();
}
}  // namespace config
#line 3 "gcc_builtin.hpp"
namespace workspace {
constexpr int clz32(const uint32_t &n) noexcept { return __builtin_clz(n); }
constexpr int clz64(const uint64_t &n) noexcept{ return __builtin_clzll(n); }
constexpr int ctz(const uint64_t &n) noexcept { return __builtin_ctzll(n); }
constexpr int popcnt(const uint64_t &n) noexcept { return __builtin_popcountll(n); }
} // namespace workspace
#line 2 "gcc_option.hpp"
#ifdef ONLINE_JUDGE
    #pragma GCC optimize("O3")
    #pragma GCC target("avx,avx2")
    #pragma GCC optimize("unroll-loops")
#endif
#line 5 "utils/binary_search.hpp"
namespace workspace {
// binary search on discrete range.
template <class iter_type, class pred_type>
std::enable_if_t<
    std::is_convertible_v<std::invoke_result_t<pred_type, iter_type>, bool>,
    iter_type>
binary_search(iter_type ok, iter_type ng, pred_type pred) {
  assert(ok != ng);
  __int128_t dist(ng - ok);
  while (dist > 1 || dist < -1) {
    iter_type mid(ok + dist / 2);
    if (pred(mid))
      ok = mid, dist -= dist / 2;
    else
      ng = mid, dist /= 2;
  }
  return ok;
}
// parallel binary search on discrete range.
template <class iter_type, class pred_type>
std::enable_if_t<std::is_convertible_v<
                     std::invoke_result_t<pred_type, std::vector<iter_type>>,
                     std::vector<bool>>,
                 std::vector<iter_type>>
binary_search(std::vector<std::pair<iter_type, iter_type>> ends,
              pred_type pred) {
  std::vector<iter_type> mids(ends.size());
  for (;;) {
    bool all_found = true;
    for (size_t i{}; i != ends.size(); ++i) {
      auto [ok, ng] = ends[i];
      iter_type mid(ok + (ng - ok) / 2);
      if (mids[i] != mid) {
        all_found = false;
        mids[i] = mid;
      }
    }
    if (all_found) break;
    auto res = pred(mids);
    for (size_t i{}; i != ends.size(); ++i) {
      (res[i] ? ends[i].first : ends[i].second) = mids[i];
    }
  }
  return mids;
}
// binary search on real numbers.
template <class real_type, class pred_type>
std::enable_if_t<
    std::is_convertible_v<std::invoke_result_t<pred_type, real_type>, bool>,
    real_type>
binary_search(real_type ok, real_type ng, const real_type eps, pred_type pred) {
  assert(ok != ng);
  while (ok + eps < ng || ng + eps < ok) {
    real_type mid{(ok + ng) / 2};
    (pred(mid) ? ok : ng) = mid;
  }
  return ok;
}
// parallel binary search on real numbers.
template <class real_type, class pred_type>
std::enable_if_t<std::is_convertible_v<
                     std::invoke_result_t<pred_type, std::vector<real_type>>,
                     std::vector<bool>>,
                 std::vector<real_type>>
binary_search(std::vector<std::pair<real_type, real_type>> ends,
              const real_type eps, pred_type pred) {
  std::vector<real_type> mids(ends.size());
  for (;;) {
    bool all_found = true;
    for (size_t i{}; i != ends.size(); ++i) {
      auto [ok, ng] = ends[i];
      if (ok + eps < ng || ng + eps < ok) {
        all_found = false;
        mids[i] = (ok + ng) / 2;
      }
    }
    if (all_found) break;
    auto res = pred(mids);
    for (size_t i{}; i != ends.size(); ++i) {
      (res[i] ? ends[i].first : ends[i].second) = mids[i];
    }
  }
  return mids;
}
}  // namespace workspace
#line 3 "utils/casefmt.hpp"
namespace workspace {
std::ostream &casefmt(std::ostream& os) { return os << "Case #" << config::caseid << ": "; }
} // namespace workspace
#line 3 "utils/chval.hpp"
namespace workspace {
template <class T, class Comp = std::less<T>> bool chle(T &x, const T &y, Comp comp = Comp()) { return comp(y, x) ? x = y, true : false; }
template <class T, class Comp = std::less<T>> bool chge(T &x, const T &y, Comp comp = Comp()) { return comp(x, y) ? x = y, true : false; }
} // namespace workspace
#line 3 "utils/fixed_point.hpp"
namespace workspace {
// specify the return type of lambda.
template <class lambda_type>
class fixed_point
{
    lambda_type func;
public:
    fixed_point(lambda_type &&f) : func(std::move(f)) {}
    template <class... Args> auto operator()(Args &&... args) const { return func(*this, std::forward<Args>(args)...); }
};
} // namespace workspace
#line 3 "utils/sfinae.hpp"
#include <type_traits>

template <class type, template <class> class trait>
using enable_if_trait_type = typename std::enable_if<trait<type>::value>::type;

template <class Container>
using element_type = typename std::decay<decltype(
    *std::begin(std::declval<Container&>()))>::type;

template <class T, class = void> struct is_integral_ext : std::false_type {};
template <class T>
struct is_integral_ext<
    T, typename std::enable_if<std::is_integral<T>::value>::type>
    : std::true_type {};
template <> struct is_integral_ext<__int128_t> : std::true_type {};
template <> struct is_integral_ext<__uint128_t> : std::true_type {};
template <class T>
constexpr static bool is_integral_ext_v = is_integral_ext<T>::value;

template <typename T, typename = void> struct multiplicable_uint {
  using type = uint_least32_t;
};
template <typename T>
struct multiplicable_uint<T, typename std::enable_if<(2 < sizeof(T))>::type> {
  using type = uint_least64_t;
};
template <typename T>
struct multiplicable_uint<T, typename std::enable_if<(4 < sizeof(T))>::type> {
  using type = __uint128_t;
};
#line 7 "utils/hash.hpp"
namespace workspace {
template <class T, class = void>
struct hash : std::hash<T> {};
template <class Unique_bits_type>
struct hash<Unique_bits_type, enable_if_trait_type<Unique_bits_type, std::has_unique_object_representations>>
{
    size_t operator()(uint64_t x) const
    {
        static const uint64_t m = std::random_device{}();
        x ^= x >> 23;
        // x *= 0x2127599bf4325c37ULL;
        x ^= m;
        x ^= x >> 47;
        return x - (x >> 32);
    }
};
template <class Key>
size_t hash_combine(const size_t &seed, const Key &key)
{
    return seed ^ (hash<Key>()(key) + 0x9e3779b9 /* + (seed << 6) + (seed >> 2) */ );
}
template <class T1, class T2>
struct hash<std::pair<T1, T2>>
{
    size_t operator()(const std::pair<T1, T2> &pair) const
    {
        return hash_combine(hash<T1>()(pair.first), pair.second);
    }
};
template <class... T>
class hash<std::tuple<T...>>
{
    template <class Tuple, size_t index = std::tuple_size<Tuple>::value - 1> struct tuple_hash { static uint64_t apply(const Tuple &t) { return hash_combine(tuple_hash<Tuple, index - 1>::apply(t), std::get<index>(t)); } };
    template <class Tuple> struct tuple_hash<Tuple, size_t(-1)> { static uint64_t apply(const Tuple &t) { return 0; } };
public:
    uint64_t operator()(const std::tuple<T...> &t) const { return tuple_hash<std::tuple<T...>>::apply(t); }
};
template <class hash_table>
struct hash_table_wrapper : hash_table
{
    using key_type = typename hash_table::key_type;
    size_t count(const key_type &key) const { return hash_table::find(key) != hash_table::end(); }
    template <class... Args> auto emplace(Args&&... args) { return hash_table::insert(typename hash_table::value_type(args...)); }
};
template <class Key, class Mapped = __gnu_pbds::null_type>
using cc_hash_table = hash_table_wrapper<__gnu_pbds::cc_hash_table<Key, Mapped, hash<Key>>>;
template <class Key, class Mapped = __gnu_pbds::null_type>
using gp_hash_table = hash_table_wrapper<__gnu_pbds::gp_hash_table<Key, Mapped, hash<Key>>>;
template <class Key, class Mapped>
using unordered_map = std::unordered_map<Key, Mapped, hash<Key>>;
template <class Key>
using unordered_set = std::unordered_set<Key, hash<Key>>;
} // namespace workspace
#line 3 "utils/read.hpp"
namespace workspace {
// read with std::cin.
template <class T = void>
struct read
{
    typename std::remove_const<T>::type value;
    template <class... types>
    read(types... args) : value(args...) { std::cin >> value; }
    operator T() const { return value; }
};
template <>
struct read<void>
{
    template <class T>
    operator T() const { T value; std::cin >> value; return value; }
};
} // namespace workspace
#line 4 "utils/stream.hpp"

#line 6 "utils/stream.hpp"
namespace std {
template <class T, class U> istream &operator>>(istream &is, pair<T, U> &p) {
  return is >> p.first >> p.second;
}
template <class T, class U>
ostream &operator<<(ostream &os, const pair<T, U> &p) {
  return os << p.first << ' ' << p.second;
}
template <class tuple_t, size_t index> struct tuple_is {
  static istream &apply(istream &is, tuple_t &t) {
    tuple_is<tuple_t, index - 1>::apply(is, t);
    return is >> get<index>(t);
  }
};
template <class tuple_t> struct tuple_is<tuple_t, SIZE_MAX> {
  static istream &apply(istream &is, tuple_t &t) { return is; }
};
template <class... T> istream &operator>>(istream &is, tuple<T...> &t) {
  return tuple_is<tuple<T...>, tuple_size<tuple<T...>>::value - 1>::apply(is,
                                                                          t);
}
template <class tuple_t, size_t index> struct tuple_os {
  static ostream &apply(ostream &os, const tuple_t &t) {
    tuple_os<tuple_t, index - 1>::apply(os, t);
    return os << ' ' << get<index>(t);
  }
};
template <class tuple_t> struct tuple_os<tuple_t, 0> {
  static ostream &apply(ostream &os, const tuple_t &t) {
    return os << get<0>(t);
  }
};
template <class tuple_t> struct tuple_os<tuple_t, SIZE_MAX> {
  static ostream &apply(ostream &os, const tuple_t &t) { return os; }
};
template <class... T> ostream &operator<<(ostream &os, const tuple<T...> &t) {
  return tuple_os<tuple<T...>, tuple_size<tuple<T...>>::value - 1>::apply(os,
                                                                          t);
}
template <class Container, typename Value = element_type<Container>>
typename enable_if<!is_same<typename decay<Container>::type, string>::value &&
                       !is_same<typename decay<Container>::type, char *>::value,
                   istream &>::type
operator>>(istream &is, Container &cont) {
  for (auto &&e : cont) is >> e;
  return is;
}
template <class Container, typename Value = element_type<Container>>
typename enable_if<!is_same<typename decay<Container>::type, string>::value &&
                       !is_same<typename decay<Container>::type, char *>::value,
                   ostream &>::type
operator<<(ostream &os, const Container &cont) {
  bool head = true;
  for (auto &&e : cont) head ? head = 0 : (os << ' ', 0), os << e;
  return os;
}
}  // namespace std
#line 13 "template.cpp"

namespace workspace {
constexpr char eol = '\n';
using namespace std;
using i64 = int_least64_t;
using p32 = pair<int, int>;
using p64 = pair<i64, i64>;
template <class T, class Comp = std::less<T>>
using priority_queue = std::priority_queue<T, std::vector<T>, Comp>;
template <class T> using stack = std::stack<T, std::vector<T>>;
struct solver;
}  // namespace workspace
int main() { config::main<workspace::solver>(); }
unsigned config::cases() {
  // return -1; // not specify
  // int t; std::cin >> t; return t; // given
  return 1;
}

struct workspace::solver {
  solver() {
    // start here!
  }
};

```
{% endraw %}

<a href="../index.html">Back to top page</a>
