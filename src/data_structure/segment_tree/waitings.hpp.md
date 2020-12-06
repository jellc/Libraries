---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: src/data_structure/segment_tree/basic.hpp
    title: Segment Tree
  - icon: ':heavy_check_mark:'
    path: src/data_structure/segment_tree/lazy.hpp
    title: Lazy Segment Tree
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/2450.test.cpp
    title: test/aizu-online-judge/2450.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/DSL_2_A.test.cpp
    title: test/aizu-online-judge/DSL_2_A.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/point_set_range_composite.test.cpp
    title: test/library-checker/point_set_range_composite.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/range_affine_range_sum.test.cpp
    title: test/library-checker/range_affine_range_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/static_range_inversions_query.test.cpp
    title: test/library-checker/static_range_inversions_query.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"src/data_structure/segment_tree/waitings.hpp\"\n\n#include\
    \ <cstdint>\n#include <queue>\n\nnamespace workspace {\n\nnamespace internal {\n\
    \nstruct waitings : std::queue<size_t> {\n  waitings(size_t n) : in(n) {}\n\n\
    \  bool push(size_t index) {\n    assert(index < in.size());\n    if (in[index])\
    \ return false;\n    emplace(index);\n    return (in[index] = true);\n  }\n\n\
    \  size_t pop() {\n    assert(!empty());\n    auto index = front();\n    std::queue<size_t>::pop();\n\
    \    in[index] = false;\n    return index;\n  }\n\n private:\n  std::vector<int_least8_t>\
    \ in;\n};\n\n}  // namespace internal\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n#include <cstdint>\n#include <queue>\n\nnamespace workspace\
    \ {\n\nnamespace internal {\n\nstruct waitings : std::queue<size_t> {\n  waitings(size_t\
    \ n) : in(n) {}\n\n  bool push(size_t index) {\n    assert(index < in.size());\n\
    \    if (in[index]) return false;\n    emplace(index);\n    return (in[index]\
    \ = true);\n  }\n\n  size_t pop() {\n    assert(!empty());\n    auto index = front();\n\
    \    std::queue<size_t>::pop();\n    in[index] = false;\n    return index;\n \
    \ }\n\n private:\n  std::vector<int_least8_t> in;\n};\n\n}  // namespace internal\n\
    \n}  // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/data_structure/segment_tree/waitings.hpp
  requiredBy:
  - src/data_structure/segment_tree/lazy.hpp
  - src/data_structure/segment_tree/basic.hpp
  timestamp: '2020-12-01 00:36:44+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/library-checker/range_affine_range_sum.test.cpp
  - test/library-checker/point_set_range_composite.test.cpp
  - test/library-checker/static_range_inversions_query.test.cpp
  - test/aizu-online-judge/DSL_2_A.test.cpp
  - test/aizu-online-judge/2450.test.cpp
documentation_of: src/data_structure/segment_tree/waitings.hpp
layout: document
redirect_from:
- /library/src/data_structure/segment_tree/waitings.hpp
- /library/src/data_structure/segment_tree/waitings.hpp.html
title: src/data_structure/segment_tree/waitings.hpp
---