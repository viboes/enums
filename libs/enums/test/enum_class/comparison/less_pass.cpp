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

#include "./EnumClass.hpp"
#include <boost/detail/lightweight_test.hpp>

int main() {
  // is less than comparable
  {
    Ex::EnumClass e;
    e= Ex::EnumClass::Default;
    BOOST_TEST(e < Ex::EnumClass::Enum2);
  }
  {
    Ex::EnumClass e;
    e= Ex::EnumClass::Enum2;
    BOOST_TEST(Ex::EnumClass::Enum1<e);
  }
  {
    Ex::EnumClass e0;
    e0= Ex::EnumClass::Default;
    Ex::EnumClass e1;
    e1= Ex::EnumClass::Enum2;
    BOOST_TEST(e0 < e1);
  }
  return boost::report_errors();
}
