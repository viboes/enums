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
  using namespace boost::enums;

  // equal comparable
  {
    Ex::EnumClass e;
    e = Ex::EnumClass::Enum2;
    BOOST_TEST(e==Ex::EnumClass::Enum2);
  }
  {
    Ex::EnumClass e;
    e = Ex::EnumClass::Enum2;
    BOOST_TEST(Ex::EnumClass::Enum2==e);
  }
  {
    Ex::EnumClass e1, e2;
    e1 = Ex::EnumClass::Enum2;
    e2 = Ex::EnumClass::Enum2;
    BOOST_TEST(e1==e2);
  }

  return boost::report_errors();
}
