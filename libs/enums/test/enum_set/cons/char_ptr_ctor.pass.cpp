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

// template <class charT>
//     explicit bitset(const charT* str,
//                     typename basic_string<charT>::size_type n = basic_string<charT>::npos,
//                     charT zero = charT('0'), charT one = charT('1'));

#include "./Ex.hpp"
#include <boost/enums/containers/enum_set.hpp>
#include <boost/enums/ordinal/size.hpp>
#include <boost/enums/ordinal/val.hpp>
#include <boost/detail/lightweight_test.hpp>

using namespace boost::enums;

template <typename EC>
void test_char_pointer_ctor()
{
    {
    try
    {
        enum_set<EC> v("xxx1010101010xxxx");
        BOOST_TEST(false);
    }
    catch (std::invalid_argument&)
    {
    }
    }

    {
    const char str[] ="1010101010";
    enum_set<EC> v(str);
    std::size_t M = std::min<std::size_t>(meta::size<EC>::value, 10);
    for (std::size_t i = 0; i < M; ++i)
        BOOST_TEST(v[val<EC>(i)] == (str[M - 1 - i] == '1'));
    for (std::size_t i = 10; i < meta::size<EC>::value; ++i)
        BOOST_TEST(v[val<EC>(i)] == false);
    }
}

int main()
{
    test_char_pointer_ctor<EC3>();
    //~ test_char_pointer_ctor<1>();
    //~ test_char_pointer_ctor<31>();
    //~ test_char_pointer_ctor<32>();
    //~ test_char_pointer_ctor<33>();
    //~ test_char_pointer_ctor<63>();
    //~ test_char_pointer_ctor<64>();
    //~ test_char_pointer_ctor<65>();
    //~ test_char_pointer_ctor<1000>();
    return boost::report_errors();
}
