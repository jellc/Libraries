---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Cat
    links: []
  bundledCode: "#line 2 \"src/utils/cat.hpp\"\n\n/**\n * @file cat.hpp\n * @brief\
    \ Cat\n */\n\n#include <iterator>\n\nnamespace workspace {\n\n/**\n * @brief Concatenate\
    \ two sequences.\n *\n * @param __c1\n * @param __c2\n * @return Concatenated\
    \ sequence.\n */\ntemplate <class _C1, class _C2>\nconstexpr decltype(auto) cat(_C1\
    \ &&__c1, _C2 &&__c2) noexcept {\n  auto __c = std::forward<_C1>(__c1);\n\n  if\
    \ constexpr (std::is_rvalue_reference<decltype(__c2)>::value)\n    __c.insert(std::end(__c),\
    \ std::move_iterator(std::begin(__c2)),\n               std::move_iterator(std::end(__c2)));\n\
    \n  else\n    __c.insert(std::end(__c), std::cbegin(__c2), std::cend(__c2));\n\
    \n  return __c;\n}\n\n/**\n * @return Concatenated sequence.\n */\ntemplate <class\
    \ _C1, class _C2, class... _Args>\nconstexpr decltype(auto) cat(_C1 &&__c1, _C2\
    \ &&__c2,\n                             _Args &&...__args) noexcept {\n  return\
    \ cat(cat(std::forward<_C1>(__c1), std::forward<_C2>(__c2)),\n             std::forward<_Args>(__args)...);\n\
    }\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/**\n * @file cat.hpp\n * @brief Cat\n */\n\n#include <iterator>\n\
    \nnamespace workspace {\n\n/**\n * @brief Concatenate two sequences.\n *\n * @param\
    \ __c1\n * @param __c2\n * @return Concatenated sequence.\n */\ntemplate <class\
    \ _C1, class _C2>\nconstexpr decltype(auto) cat(_C1 &&__c1, _C2 &&__c2) noexcept\
    \ {\n  auto __c = std::forward<_C1>(__c1);\n\n  if constexpr (std::is_rvalue_reference<decltype(__c2)>::value)\n\
    \    __c.insert(std::end(__c), std::move_iterator(std::begin(__c2)),\n       \
    \        std::move_iterator(std::end(__c2)));\n\n  else\n    __c.insert(std::end(__c),\
    \ std::cbegin(__c2), std::cend(__c2));\n\n  return __c;\n}\n\n/**\n * @return\
    \ Concatenated sequence.\n */\ntemplate <class _C1, class _C2, class... _Args>\n\
    constexpr decltype(auto) cat(_C1 &&__c1, _C2 &&__c2,\n                       \
    \      _Args &&...__args) noexcept {\n  return cat(cat(std::forward<_C1>(__c1),\
    \ std::forward<_C2>(__c2)),\n             std::forward<_Args>(__args)...);\n}\n\
    \n}  // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/utils/cat.hpp
  requiredBy: []
  timestamp: '2021-02-25 03:01:05+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/utils/cat.hpp
layout: document
redirect_from:
- /library/src/utils/cat.hpp
- /library/src/utils/cat.hpp.html
title: Cat
---