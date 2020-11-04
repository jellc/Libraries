---
data:
  _extendedDependsOn:
  - icon: ':warning:'
    path: config.hpp
    title: setup I/O before main process.
  _extendedRequiredBy:
  - icon: ':warning:'
    path: template.cpp
    title: template.cpp
  - icon: ':warning:'
    path: utils.hpp
    title: utils.hpp
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: 'printf("Case #%u: ", config::caseid)'
    links: []
  bundledCode: "#line 2 \"config.hpp\"\n#include <chrono>\n#include <iomanip>\n#include\
    \ <iostream>\n\nnamespace config {\n\nconst auto start_time{std::chrono::system_clock::now()};\n\
    \n/*\n * @fn elapsed\n * @return elapsed time of the program\n */\nint64_t elapsed()\
    \ {\n  using namespace std::chrono;\n  const auto end_time{system_clock::now()};\n\
    \  return duration_cast<milliseconds>(end_time - start_time).count();\n}\n\n/*\n\
    \ * @fn setup\n * @brief setup I/O before main process.\n */\n__attribute__((constructor))\
    \ void setup() {\n  using namespace std;\n  ios::sync_with_stdio(false);\n  cin.tie(nullptr);\n\
    \  cout << fixed << setprecision(15);\n\n#ifdef _buffer_check\n  atexit([] {\n\
    \    char bufc;\n    if (cin >> bufc)\n      cerr << \"\\n\\033[43m\\033[30mwarning:\
    \ buffer not empty.\\033[0m\\n\\n\";\n  });\n#endif\n}\n\nunsigned cases(), caseid\
    \ = 1;  // current case number, 1-indexed\n\n/*\n * @fn loop\n * @brief iterate\
    \ cases.\n * @param main called once per case\n */\ntemplate <class F> void loop(F\
    \ main) {\n  for (const unsigned total = cases(); caseid <= total; ++caseid) {\n\
    \    try {\n      main();\n    } catch (std::nullptr_t) {\n    }\n  }\n}\n\n}\
    \  // namespace config\n#line 3 \"utils/casefmt.hpp\"\n\nnamespace workspace {\n\
    \n/*\n * @brief printf(\"Case #%u: \", config::caseid)\n * @param os reference\
    \ to ostream\n * @return os\n */\nstd::ostream& casefmt(std::ostream& os) {\n\
    \  return os << \"Case #\" << config::caseid << \": \";\n}\n\n}  // namespace\
    \ workspace\n"
  code: "#pragma once\n#include \"config.hpp\"\n\nnamespace workspace {\n\n/*\n *\
    \ @brief printf(\"Case #%u: \", config::caseid)\n * @param os reference to ostream\n\
    \ * @return os\n */\nstd::ostream& casefmt(std::ostream& os) {\n  return os <<\
    \ \"Case #\" << config::caseid << \": \";\n}\n\n}  // namespace workspace\n"
  dependsOn:
  - config.hpp
  isVerificationFile: false
  path: utils/casefmt.hpp
  requiredBy:
  - template.cpp
  - utils.hpp
  timestamp: '2020-11-04 13:20:06+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: utils/casefmt.hpp
layout: document
redirect_from:
- /library/utils/casefmt.hpp
- /library/utils/casefmt.hpp.html
title: 'printf("Case #%u: ", config::caseid)'
---