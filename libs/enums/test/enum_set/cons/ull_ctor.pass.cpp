//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 2011.
// Distributed under the Boost
// Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or
// copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/enums for documentation.
//
// Adapted from libcxx tests
//
//////////////////////////////////////////////////////////////////////////////
//===----------------------------------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// test bitset(unsigned long long val);

#include "./Ex.hpp"
#include <boost/enums/enum_set.hpp>
#include <boost/enums/val.hpp>
#include <boost/detail/lightweight_test.hpp>

using namespace boost::enums;

template <typename EC>
void test_val_ctor()
{
    {
    enum_set<EC> v(0xAAAAAAAAAAAAAAAAULL);
    BOOST_TEST(v.size() == meta::size<EC>::value);
    unsigned M = std::min<std::size_t>(meta::size<EC>::value, 64);
    for (std::size_t i = 0; i < M; ++i)
        BOOST_TEST(v[val<EC>(i)] == ((i & 1)!=0));
    for (std::size_t i = M; i < meta::size<EC>::value; ++i)
        BOOST_TEST(v[val<EC>(i)] == false);
    }
}

int main()
{
    test_val_ctor<EC3>();
    //~ test_val_ctor<1>();
    //~ test_val_ctor<31>();
    //~ test_val_ctor<32>();
    //~ test_val_ctor<33>();
    //~ test_val_ctor<63>();
    //~ test_val_ctor<64>();
    //~ test_val_ctor<65>();
    //~ test_val_ctor<1000>();
    return boost::report_errors();
}
