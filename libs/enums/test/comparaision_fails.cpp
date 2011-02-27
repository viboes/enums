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

void fail() {

  { // The wrapper can be compared
    EnumClass e0;
    e0= EnumClass::Default;
    BOOST_TEST(e0 < EnumClass::Enum2);
  }
  { // The wrapper can be compared
    EnumClass e0;
    e0= EnumClass::Default;
    EnumClass e1;
    e1= EnumClass::Enum2;
    BOOST_TEST(e0 < e1);
  }

}
