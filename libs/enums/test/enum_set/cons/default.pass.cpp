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

// test default ctor

#include "./Ex.hpp"
#include <boost/enums/containers/enum_set.hpp>
#include <boost/enums/ordinal/size.hpp>
#include <boost/enums/ordinal/val.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <iostream>

using namespace boost::enums;

template <typename EC>
void test_default_ctor()
{
    
  enum_set<EC> v1;
  BOOST_TEST(v1.size() == meta::size<EC>::value);
  for (std::size_t i = 0; i < meta::size<EC>::value; ++i) 
  {
    BOOST_TEST(v1[val<EC>(i)] == false);
  }
    
}

int main()
{
    test_default_ctor<EC3>();
    //~ test_default_ctor<1>();
    //~ test_default_ctor<31>();
    //~ test_default_ctor<32>();
    //~ test_default_ctor<33>();
    //~ test_default_ctor<63>();
    //~ test_default_ctor<64>();
    //~ test_default_ctor<65>();
    //~ test_default_ctor<1000>();
    return boost::report_errors();
}
