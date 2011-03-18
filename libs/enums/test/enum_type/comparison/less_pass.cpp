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
//////////////////////////////////////////////////////////////////////////////

#include "./EnumType.hpp"
#include <boost/detail/lightweight_test.hpp>

int main() {
  // is less than comparable
  {
    EnumClass e;
    e= EnumClass::Default;
    BOOST_TEST(e < EnumClass::Enum2);
  }
  {
    EnumClass e;
    e= EnumClass::Enum2;
    BOOST_TEST(EnumClass::Enum1<e);
  }
  {
    EnumClass e0;
    e0= EnumClass::Default;
    EnumClass e1;
    e1= EnumClass::Enum2;
    BOOST_TEST(e0 < e1);
  }
  return boost::report_errors();
}
