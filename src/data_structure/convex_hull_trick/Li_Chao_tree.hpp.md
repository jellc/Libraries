---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/library-checker/line_add_get_min.test.cpp
    title: test/library-checker/line_add_get_min.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/segment_add_get_min.test.cpp
    title: test/library-checker/segment_add_get_min.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Li-Chao Tree
    links: []
  bundledCode: "#line 2 \"src/data_structure/convex_hull_trick/Li_Chao_tree.hpp\"\n\
    \n/*\n * @file Li_Chao_tree.hpp\n * @brief Li-Chao Tree\n */\n\n#include <cassert>\n\
    #include <functional>\n\nnamespace workspace {\n\n/*\n * @struct Li_Chao_tree\n\
    \ * @tparam T Ordered ring.\n * @tparam Comp Comparison function object type\n\
    \ * @tparam Infinity Identity element for 'Comp'.\n * @tparam Eps Error tolerance\n\
    \ */\ntemplate <class T, class Comp = std::less<T>,\n          T Infinity = std::numeric_limits<T>::max()\
    \ / 2, T Eps = 1>\nstruct Li_Chao_tree {\n  constexpr static T infinity = Infinity;\n\
    \  constexpr static T eps = Eps;\n\n  struct line {\n    T slope = 0, intercept\
    \ = Infinity;\n    T eval(const T x) const { return slope * x + intercept; }\n\
    \  };\n\n  /*\n   * @param begin Lower bound of domain\n   * @param end Upper\
    \ bound of domain\n   * @param comp Comparison function object\n   */\n  Li_Chao_tree(const\
    \ T begin, const T end, Comp comp = Comp())\n      : begin(begin), end(end), comp(comp)\
    \ {}\n\n  ~Li_Chao_tree() { delete root; }\n\n  bool empty() const { return !root;\
    \ }\n\n  /*\n   * @fn insert\n   * @brief Insert a line.\n   * @param ln Line\n\
    \   */\n  void insert(line const &ln) { root = insert(root, begin, end, ln); }\n\
    \n  /*\n   * @fn insert\n   * @brief Insert a line.\n   * @param slope Slope\n\
    \   * @param intercept Intercept\n   */\n  void insert(const T slope, const T\
    \ intercept) {\n    insert(line{slope, intercept});\n  }\n\n  /*\n   * @fn insert\n\
    \   * @brief Insert a segment.\n   * @param seg Segment\n   * @param __begin Left\
    \ end, inclusive\n   * @param __end Right end, exclusive\n   */\n  void insert(line\
    \ const &seg, const T __begin, const T __end) {\n    if (__begin < __end) root\
    \ = insert(root, begin, end, seg, __begin, __end);\n  }\n\n  /*\n   * @fn insert\n\
    \   * @brief Insert a segment.\n   * @param slope Slope\n   * @param intercept\
    \ Intercept\n   * @param __begin Left end, inclusive\n   * @param __end Right\
    \ end, exclusive\n   */\n  void insert(const T slope, const T intercept, const\
    \ T __begin,\n              const T __end) {\n    insert(line{slope, intercept},\
    \ __begin, __end);\n  }\n\n  /*\n   * @fn eval\n   * @param x Position\n   * @return\
    \ The optimum at given position.\n   */\n  T eval(const T x) const {\n    node\
    \ *p = root;\n    T l = begin, r = end, opt = Infinity;\n    while (p) {\n   \
    \   const T nval = p->__line.eval(x);\n      if (comp(nval, opt)) opt = nval;\n\
    \      if (r - l <= Eps) break;\n      const T mid = (l + r) / 2;\n      if (x\
    \ < mid) {\n        p = p->__left;\n        r = mid;\n      } else {\n       \
    \ p = p->__right;\n        l = mid;\n      }\n    }\n    return opt;\n  }\n\n\
    \  /*\n   * @fn argmin\n   * @param x Position\n   * @return The line achieving\
    \ the optimum at given position.\n   */\n  line get(const T x) const {\n    assert(!empty());\n\
    \    node *p = root, *arg = nullptr;\n    T l = begin, r = end, opt = Infinity;\n\
    \    while (p) {\n      const T nval = p->__line.eval(x);\n      if (comp(nval,\
    \ opt)) opt = nval, arg = p;\n      if (r - l <= Eps) break;\n      const T mid\
    \ = (l + r) / 2;\n      if (x < mid) {\n        p = p->__left;\n        r = mid;\n\
    \      } else {\n        p = p->__right;\n        l = mid;\n      }\n    }\n \
    \   return arg->__line;\n  }\n\n protected:\n  struct node {\n    line __line;\n\
    \    node *__left = nullptr, *__right = nullptr;\n    node(node const &) = delete;\n\
    \    node &operator=(node const &) = delete;\n    ~node() {\n      delete __left;\n\
    \      delete __right;\n    }\n  };\n\n  const T begin, end;\n  Comp comp;\n \
    \ node *root = nullptr;\n\n  node *insert(node *const p, const T l, const T r,\
    \ line const &ln) {\n    if (!p) return new node{ln};\n    line &cur = p->__line;\n\
    \    const bool left_low = comp(ln.eval(l), cur.eval(l));\n    if (r - l <= Eps\
    \ || left_low == comp(ln.eval(r), cur.eval(r))) {\n      if (left_low) cur = ln;\n\
    \      return p;\n    }\n    const T mid = (l + r) / 2;\n    if (comp(ln.eval(mid),\
    \ cur.eval(mid))) {\n      if (left_low)\n        p->__right = insert(p->__right,\
    \ mid, r, cur);\n      else\n        p->__left = insert(p->__left, l, mid, cur);\n\
    \      cur = ln;\n    } else {\n      if (left_low)\n        p->__left = insert(p->__left,\
    \ l, mid, ln);\n      else\n        p->__right = insert(p->__right, mid, r, ln);\n\
    \    }\n    return p;\n  }\n\n  node *insert(node *p, const T l, const T r, line\
    \ const &seg, const T s,\n               const T t) {\n    if (s < l + Eps &&\
    \ r < t + Eps) return insert(p, l, r, seg);\n    if (l < t && s < r) {\n     \
    \ if (!p) p = new node{};\n      p->__left = insert(p->__left, l, (l + r) / 2,\
    \ seg, s, t);\n      p->__right = insert(p->__right, (l + r) / 2, r, seg, s, t);\n\
    \    }\n    return p;\n  }\n};\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/*\n * @file Li_Chao_tree.hpp\n * @brief Li-Chao Tree\n */\n\
    \n#include <cassert>\n#include <functional>\n\nnamespace workspace {\n\n/*\n *\
    \ @struct Li_Chao_tree\n * @tparam T Ordered ring.\n * @tparam Comp Comparison\
    \ function object type\n * @tparam Infinity Identity element for 'Comp'.\n * @tparam\
    \ Eps Error tolerance\n */\ntemplate <class T, class Comp = std::less<T>,\n  \
    \        T Infinity = std::numeric_limits<T>::max() / 2, T Eps = 1>\nstruct Li_Chao_tree\
    \ {\n  constexpr static T infinity = Infinity;\n  constexpr static T eps = Eps;\n\
    \n  struct line {\n    T slope = 0, intercept = Infinity;\n    T eval(const T\
    \ x) const { return slope * x + intercept; }\n  };\n\n  /*\n   * @param begin\
    \ Lower bound of domain\n   * @param end Upper bound of domain\n   * @param comp\
    \ Comparison function object\n   */\n  Li_Chao_tree(const T begin, const T end,\
    \ Comp comp = Comp())\n      : begin(begin), end(end), comp(comp) {}\n\n  ~Li_Chao_tree()\
    \ { delete root; }\n\n  bool empty() const { return !root; }\n\n  /*\n   * @fn\
    \ insert\n   * @brief Insert a line.\n   * @param ln Line\n   */\n  void insert(line\
    \ const &ln) { root = insert(root, begin, end, ln); }\n\n  /*\n   * @fn insert\n\
    \   * @brief Insert a line.\n   * @param slope Slope\n   * @param intercept Intercept\n\
    \   */\n  void insert(const T slope, const T intercept) {\n    insert(line{slope,\
    \ intercept});\n  }\n\n  /*\n   * @fn insert\n   * @brief Insert a segment.\n\
    \   * @param seg Segment\n   * @param __begin Left end, inclusive\n   * @param\
    \ __end Right end, exclusive\n   */\n  void insert(line const &seg, const T __begin,\
    \ const T __end) {\n    if (__begin < __end) root = insert(root, begin, end, seg,\
    \ __begin, __end);\n  }\n\n  /*\n   * @fn insert\n   * @brief Insert a segment.\n\
    \   * @param slope Slope\n   * @param intercept Intercept\n   * @param __begin\
    \ Left end, inclusive\n   * @param __end Right end, exclusive\n   */\n  void insert(const\
    \ T slope, const T intercept, const T __begin,\n              const T __end) {\n\
    \    insert(line{slope, intercept}, __begin, __end);\n  }\n\n  /*\n   * @fn eval\n\
    \   * @param x Position\n   * @return The optimum at given position.\n   */\n\
    \  T eval(const T x) const {\n    node *p = root;\n    T l = begin, r = end, opt\
    \ = Infinity;\n    while (p) {\n      const T nval = p->__line.eval(x);\n    \
    \  if (comp(nval, opt)) opt = nval;\n      if (r - l <= Eps) break;\n      const\
    \ T mid = (l + r) / 2;\n      if (x < mid) {\n        p = p->__left;\n       \
    \ r = mid;\n      } else {\n        p = p->__right;\n        l = mid;\n      }\n\
    \    }\n    return opt;\n  }\n\n  /*\n   * @fn argmin\n   * @param x Position\n\
    \   * @return The line achieving the optimum at given position.\n   */\n  line\
    \ get(const T x) const {\n    assert(!empty());\n    node *p = root, *arg = nullptr;\n\
    \    T l = begin, r = end, opt = Infinity;\n    while (p) {\n      const T nval\
    \ = p->__line.eval(x);\n      if (comp(nval, opt)) opt = nval, arg = p;\n    \
    \  if (r - l <= Eps) break;\n      const T mid = (l + r) / 2;\n      if (x < mid)\
    \ {\n        p = p->__left;\n        r = mid;\n      } else {\n        p = p->__right;\n\
    \        l = mid;\n      }\n    }\n    return arg->__line;\n  }\n\n protected:\n\
    \  struct node {\n    line __line;\n    node *__left = nullptr, *__right = nullptr;\n\
    \    node(node const &) = delete;\n    node &operator=(node const &) = delete;\n\
    \    ~node() {\n      delete __left;\n      delete __right;\n    }\n  };\n\n \
    \ const T begin, end;\n  Comp comp;\n  node *root = nullptr;\n\n  node *insert(node\
    \ *const p, const T l, const T r, line const &ln) {\n    if (!p) return new node{ln};\n\
    \    line &cur = p->__line;\n    const bool left_low = comp(ln.eval(l), cur.eval(l));\n\
    \    if (r - l <= Eps || left_low == comp(ln.eval(r), cur.eval(r))) {\n      if\
    \ (left_low) cur = ln;\n      return p;\n    }\n    const T mid = (l + r) / 2;\n\
    \    if (comp(ln.eval(mid), cur.eval(mid))) {\n      if (left_low)\n        p->__right\
    \ = insert(p->__right, mid, r, cur);\n      else\n        p->__left = insert(p->__left,\
    \ l, mid, cur);\n      cur = ln;\n    } else {\n      if (left_low)\n        p->__left\
    \ = insert(p->__left, l, mid, ln);\n      else\n        p->__right = insert(p->__right,\
    \ mid, r, ln);\n    }\n    return p;\n  }\n\n  node *insert(node *p, const T l,\
    \ const T r, line const &seg, const T s,\n               const T t) {\n    if\
    \ (s < l + Eps && r < t + Eps) return insert(p, l, r, seg);\n    if (l < t &&\
    \ s < r) {\n      if (!p) p = new node{};\n      p->__left = insert(p->__left,\
    \ l, (l + r) / 2, seg, s, t);\n      p->__right = insert(p->__right, (l + r) /\
    \ 2, r, seg, s, t);\n    }\n    return p;\n  }\n};\n\n}  // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/data_structure/convex_hull_trick/Li_Chao_tree.hpp
  requiredBy: []
  timestamp: '2020-11-23 14:16:28+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/library-checker/line_add_get_min.test.cpp
  - test/library-checker/segment_add_get_min.test.cpp
documentation_of: src/data_structure/convex_hull_trick/Li_Chao_tree.hpp
layout: document
redirect_from:
- /library/src/data_structure/convex_hull_trick/Li_Chao_tree.hpp
- /library/src/data_structure/convex_hull_trick/Li_Chao_tree.hpp.html
title: Li-Chao Tree
---