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

// test bitset(string, pos, n, zero, one);

#include "./Ex.hpp"
#include <boost/enums/enum_set.hpp>
#include <boost/enums/val.hpp>
#include <boost/detail/lightweight_test.hpp>

using namespace boost::enums;


template <typename EC>
void test_string_ctor()
{
    {
    try
    {
        std::string str("xxx1010101010xxxx");
        enum_set<EC>  v(str, str.size()+1, 10);
        BOOST_TEST(false);
    }
    catch (std::out_of_range&)
    {
    }
    }

    {
    try
    {
        std::string str("xxx1010101010xxxx");
        enum_set<EC>  v(str, 2, 10);
        BOOST_TEST(false);
    }
    catch (std::invalid_argument&)
    {
    }
    }

    {
    std::string str("xxx1010101010xxxx");
    enum_set<EC>  v(str, 3, 10);
    std::size_t M = std::min<std::size_t>(meta::size<EC>::value, 10);
    for (std::size_t i = 0; i < M; ++i)
        BOOST_TEST(v[val<EC>(i)] == (str[3 + M - 1 - i] == '1'));
    for (std::size_t i = 10; i < meta::size<EC>::value; ++i)
        BOOST_TEST(v[val<EC>(i)] == false);
    }

    {
    try
    {
        std::string str("xxxbababababaxxxx");
        enum_set<EC> v(str, 2, 10, 'a', 'b');
        BOOST_TEST(false);
    }
    catch (std::invalid_argument&)
    {
    }
    }

    {
    std::string str("xxxbababababaxxxx");
    enum_set<EC> v(str, 3, 10, 'a', 'b');
    std::size_t M = std::min<std::size_t>(meta::size<EC>::value, 10);
    for (std::size_t i = 0; i < M; ++i)
        BOOST_TEST(v[val<EC>(i)] == (str[3 + M - 1 - i] == 'b'));
    for (std::size_t i = 10; i < meta::size<EC>::value; ++i)
        BOOST_TEST(v[val<EC>(i)] == false);
    }
}

int main()
{
    test_string_ctor<EC3>();
    //~ test_string_ctor<1>();
    //~ test_string_ctor<31>();
    //~ test_string_ctor<32>();
    //~ test_string_ctor<33>();
    //~ test_string_ctor<63>();
    //~ test_string_ctor<64>();
    //~ test_string_ctor<65>();
    //~ test_string_ctor<1000>();
    return boost::report_errors();
}
