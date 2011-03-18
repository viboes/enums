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
  using namespace boost::enums;

  // not equal comparable
  {
    EnumClass e;
    e = EnumClass::Enum2;
    BOOST_TEST(e!=EnumClass::Default);
  }
  {
    EnumClass e;
    e = EnumClass::Enum2;
    BOOST_TEST(EnumClass::Default!=e);
  }
  {
    EnumClass e1;
    e1 = EnumClass::Enum1;
    EnumClass e2;
    e2 = EnumClass::Enum2;
    BOOST_TEST(e1!=e2);
  }

  return boost::report_errors();
}
