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


# :warning: data_structure/segment_tree/segment_tree.hpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#fba856dbe1aaa5374a50a27f6dcea717">data_structure/segment_tree</a>
* <a href="{{ site.github.repository_url }}/blob/master/data_structure/segment_tree/segment_tree.hpp">View this file on GitHub</a>
    - Last commit date: 2020-07-08 02:39:24+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include <cassert>
#include <vector>

template <class monoid>
class segment_tree
{
    using size_type = typename std::vector<monoid>::size_type;

    class unique_queue
    {
        size_type *que, *begin, *end;
        bool *in;

    public:
        unique_queue() : que(), begin(), end(), in() {}
        unique_queue(size_type n) : que(new size_type[n]), begin(que), end(que), in(new bool[n]{}) {}
        ~unique_queue() { delete[] que; delete[] in; }

        void clear() { begin = end = que; }
        bool empty() const { return begin == end; }
        bool push(size_type index)
        {
            if(in[index]) return false;
            return in[*end++ = index] = true;
        }
        size_type pop() { return in[*begin] = false, *begin++; }
    }; // struct unique_queue

    size_type size_orig, height, size_ext;
    std::vector<monoid> data;
    unique_queue que;

    void recalc(const size_type node) { data[node] = data[node << 1] + data[node << 1 | 1]; }

    void rebuild()
    {
        while(!que.empty())
        {
            const size_type index = que.pop() >> 1;
            if(index && que.push(index)) recalc(index);
        }
        que.clear();
    }

    template <class pred_type>
    size_type left_search_subtree(size_type index, const pred_type pred, monoid mono) const
    {
        assert(index);
        while(index < size_ext)
        {
            const monoid tmp = data[(index <<= 1) | 1] + mono;
            if(pred(tmp)) mono = tmp;
            else ++index;
        }
        return ++index -= size_ext;
    }

    template <class pred_type>
    size_type right_search_subtree(size_type index, const pred_type pred, monoid mono) const
    {
        assert(index);
        while(index < size_ext)
        {
            const monoid tmp = mono + data[index <<= 1];
            if(pred(tmp)) ++index, mono = tmp;
        }
        return (index -= size_ext) < size_orig ? index : size_orig;
    }

public:
    segment_tree(const size_type n = 0) : size_orig{n}, height(n > 1 ? 32 - __builtin_clz(n - 1) : 0), size_ext{1u << height}, data(size_ext << 1), que(size_ext << 1) {}

    segment_tree(const size_type n, const monoid &init) : segment_tree(n)
    {
        std::fill(std::next(std::begin(data), size_ext), std::end(data), init);
        for(size_type i{size_ext}; --i; ) recalc(i);
    }

    template <class iter_type, class value_type = typename std::iterator_traits<iter_type>::value_type>
    segment_tree(iter_type first, iter_type last)
        : size_orig(std::distance(first, last)), height(size_orig > 1 ? 32 - __builtin_clz(size_orig - 1) : 0), size_ext{1u << height}, data(size_ext << 1), que(size_ext << 1)
    {
        static_assert(std::is_constructible<monoid, value_type>::value, "monoid(iter_type::value_type) is not constructible.");
        for(auto iter{std::next(std::begin(data), size_ext)}; iter != std::end(data) && first != last; ++iter, ++first) *iter = monoid{*first};
        for(size_type i{size_ext}; --i; ) recalc(i);
    }

    template <class container_type, typename = typename container_type::value_type>
    segment_tree(const container_type &cont) : segment_tree(std::begin(cont), std::end(cont)) {}

    size_type size() const { return size_orig; }
    size_type capacity() const { return size_ext; }

    // reference to the element at the index.
    typename decltype(data)::reference operator[](size_type index)
    {
        assert(index < size_orig);
        que.push(index |= size_ext);
        return data[index];
    }

    // const reference to the element at the index.
    typename decltype(data)::const_reference operator[](size_type index) const
    {
        assert(index < size_orig);
        return data[index |= size_orig];
    }

    monoid fold(size_type first, size_type last)
    {
        assert(last <= size_orig);
        rebuild();
        monoid leftval{}, rightval{};
        first += size_ext, last += size_ext;
        while(first < last)
        {
            if(first & 1) leftval = leftval + data[first++];
            if(last & 1) rightval = data[--last] + rightval;
            first >>= 1, last >>= 1;
        }
        return leftval + rightval;
    }

    monoid fold() { return fold(0, size_orig); }

    template <class pred_type>
    size_type left_search(size_type right, const pred_type pred)
    {
        assert(right <= size_orig);
        rebuild();
        right += size_ext;
        monoid mono{};
        for(size_type left{size_ext}; left != right; left >>= 1, right >>= 1)
        {
            if((left & 1) != (right & 1))
            {
                const monoid tmp = data[--right] + mono;
                if(!pred(tmp)) return left_search_subtree(right, pred, mono);
                mono = tmp;
            }
        }
        return 0;
    }

    template <class pred_type>
    size_type right_search(size_type left, const pred_type pred)
    {
        assert(left <= size_orig);
        rebuild();
        left += size_ext;
        monoid mono{};
        for(size_type right{size_ext << 1}; left != right; left >>= 1, right >>= 1)
        {
            if((left & 1) != (right & 1))
            {
                const monoid tmp = mono + data[left];
                if(!pred(tmp)) return right_search_subtree(left, pred, mono);
                mono = tmp;
                ++left;
            }
        }
        return size_orig;
    }
}; // class segment_tree
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "data_structure/segment_tree/segment_tree.hpp"
#include <cassert>
#include <vector>

template <class monoid>
class segment_tree
{
    using size_type = typename std::vector<monoid>::size_type;

    class unique_queue
    {
        size_type *que, *begin, *end;
        bool *in;

    public:
        unique_queue() : que(), begin(), end(), in() {}
        unique_queue(size_type n) : que(new size_type[n]), begin(que), end(que), in(new bool[n]{}) {}
        ~unique_queue() { delete[] que; delete[] in; }

        void clear() { begin = end = que; }
        bool empty() const { return begin == end; }
        bool push(size_type index)
        {
            if(in[index]) return false;
            return in[*end++ = index] = true;
        }
        size_type pop() { return in[*begin] = false, *begin++; }
    }; // struct unique_queue

    size_type size_orig, height, size_ext;
    std::vector<monoid> data;
    unique_queue que;

    void recalc(const size_type node) { data[node] = data[node << 1] + data[node << 1 | 1]; }

    void rebuild()
    {
        while(!que.empty())
        {
            const size_type index = que.pop() >> 1;
            if(index && que.push(index)) recalc(index);
        }
        que.clear();
    }

    template <class pred_type>
    size_type left_search_subtree(size_type index, const pred_type pred, monoid mono) const
    {
        assert(index);
        while(index < size_ext)
        {
            const monoid tmp = data[(index <<= 1) | 1] + mono;
            if(pred(tmp)) mono = tmp;
            else ++index;
        }
        return ++index -= size_ext;
    }

    template <class pred_type>
    size_type right_search_subtree(size_type index, const pred_type pred, monoid mono) const
    {
        assert(index);
        while(index < size_ext)
        {
            const monoid tmp = mono + data[index <<= 1];
            if(pred(tmp)) ++index, mono = tmp;
        }
        return (index -= size_ext) < size_orig ? index : size_orig;
    }

public:
    segment_tree(const size_type n = 0) : size_orig{n}, height(n > 1 ? 32 - __builtin_clz(n - 1) : 0), size_ext{1u << height}, data(size_ext << 1), que(size_ext << 1) {}

    segment_tree(const size_type n, const monoid &init) : segment_tree(n)
    {
        std::fill(std::next(std::begin(data), size_ext), std::end(data), init);
        for(size_type i{size_ext}; --i; ) recalc(i);
    }

    template <class iter_type, class value_type = typename std::iterator_traits<iter_type>::value_type>
    segment_tree(iter_type first, iter_type last)
        : size_orig(std::distance(first, last)), height(size_orig > 1 ? 32 - __builtin_clz(size_orig - 1) : 0), size_ext{1u << height}, data(size_ext << 1), que(size_ext << 1)
    {
        static_assert(std::is_constructible<monoid, value_type>::value, "monoid(iter_type::value_type) is not constructible.");
        for(auto iter{std::next(std::begin(data), size_ext)}; iter != std::end(data) && first != last; ++iter, ++first) *iter = monoid{*first};
        for(size_type i{size_ext}; --i; ) recalc(i);
    }

    template <class container_type, typename = typename container_type::value_type>
    segment_tree(const container_type &cont) : segment_tree(std::begin(cont), std::end(cont)) {}

    size_type size() const { return size_orig; }
    size_type capacity() const { return size_ext; }

    // reference to the element at the index.
    typename decltype(data)::reference operator[](size_type index)
    {
        assert(index < size_orig);
        que.push(index |= size_ext);
        return data[index];
    }

    // const reference to the element at the index.
    typename decltype(data)::const_reference operator[](size_type index) const
    {
        assert(index < size_orig);
        return data[index |= size_orig];
    }

    monoid fold(size_type first, size_type last)
    {
        assert(last <= size_orig);
        rebuild();
        monoid leftval{}, rightval{};
        first += size_ext, last += size_ext;
        while(first < last)
        {
            if(first & 1) leftval = leftval + data[first++];
            if(last & 1) rightval = data[--last] + rightval;
            first >>= 1, last >>= 1;
        }
        return leftval + rightval;
    }

    monoid fold() { return fold(0, size_orig); }

    template <class pred_type>
    size_type left_search(size_type right, const pred_type pred)
    {
        assert(right <= size_orig);
        rebuild();
        right += size_ext;
        monoid mono{};
        for(size_type left{size_ext}; left != right; left >>= 1, right >>= 1)
        {
            if((left & 1) != (right & 1))
            {
                const monoid tmp = data[--right] + mono;
                if(!pred(tmp)) return left_search_subtree(right, pred, mono);
                mono = tmp;
            }
        }
        return 0;
    }

    template <class pred_type>
    size_type right_search(size_type left, const pred_type pred)
    {
        assert(left <= size_orig);
        rebuild();
        left += size_ext;
        monoid mono{};
        for(size_type right{size_ext << 1}; left != right; left >>= 1, right >>= 1)
        {
            if((left & 1) != (right & 1))
            {
                const monoid tmp = mono + data[left];
                if(!pred(tmp)) return right_search_subtree(left, pred, mono);
                mono = tmp;
                ++left;
            }
        }
        return size_orig;
    }
}; // class segment_tree

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>
