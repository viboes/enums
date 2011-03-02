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

// void fill(const T& u);

#include <boost/enums/enum_array.hpp>
#include "./Ex.hpp"
#include <boost/detail/lightweight_test.hpp>


int main()
{
    {
        typedef double T;
        typedef boost::enums::enum_array<T, EC3> C;
        C c = {{1, 2, 3.5}};        c.fill(5.5);
        BOOST_TEST(c.size() == 3);
        BOOST_TEST(c[EC3::Enum0] == 5.5);
        BOOST_TEST(c[EC3::Enum1] == 5.5);
        BOOST_TEST(c[EC3::Enum2] == 5.5);
    }
    return boost::report_errors();
}
