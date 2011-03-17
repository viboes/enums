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

// <array>

// void swap(array& a);

#include <boost/enums/containers/enum_array.hpp>
#include "./Ex.hpp"
#include <boost/detail/lightweight_test.hpp>


int main()
{
    {
        typedef double T;
        typedef boost::enums::enum_array<T, EC3> C;
        C c1 = {{1, 2, 3.5}};
        C c2 = {{4, 5, 6.5}};
        c1.swap(c2);
        BOOST_TEST(c1.size() == 3);
        BOOST_TEST(c1[EC3::Enum0] == 4);
        BOOST_TEST(c1[EC3::Enum1] == 5);
        BOOST_TEST(c1[EC3::Enum2] == 6.5);
        BOOST_TEST(c2.size() == 3);
        BOOST_TEST(c2[EC3::Enum0] == 1);
        BOOST_TEST(c2[EC3::Enum1] == 2);
        BOOST_TEST(c2[EC3::Enum2] == 3.5);
    }
    return boost::report_errors();
}
