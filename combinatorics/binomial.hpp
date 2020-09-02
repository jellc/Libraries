#pragma once
#include "factorial.hpp"
#include "modulus/modint.hpp"
#include "modulus/inverse.hpp"
template <class> struct binomial;
template <int_fast64_t mod>
struct binomial<modint<mod>>
{
    using value_type = modint<mod>;
    struct mulinv_Op
    {
        inverse<value_type> &inv;
        value_type operator()(value_type f, size_t n) const { return f * inv(n); }
    };
    static inverse<value_type> inv;
    static factorial<value_type, mulinv_Op> fact_inv;
    static factorial<value_type> fact;
    value_type operator()(int n, int k) { return fact_inv(k) * fact_inv(n - k) * fact(n); }
};
template <int_fast64_t mod> inverse<modint<mod>> binomial<modint<mod>>::inv;
template <int_fast64_t mod> factorial<modint<mod>, class binomial<modint<mod>>::mulinv_Op> binomial<modint<mod>>::fact_inv{1, mulinv_Op{binomial<modint<mod>>::inv}};
template <int_fast64_t mod> factorial<modint<mod>> binomial<modint<mod>>::fact;
