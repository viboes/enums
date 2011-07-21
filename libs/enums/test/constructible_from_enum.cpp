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

  { // Constructible from enum
    EnumClass e(EnumClass::Enum2);
    BOOST_TEST(e==EnumClass::Enum2);
  }
  { // copy constructor emulation
    EnumClass e1=boost::explicit_convert_to<EnumClass>(EnumClass::Enum2);
    EnumClass e2=e1;
    BOOST_TEST(e2==EnumClass::Enum2);
  }
  return boost::report_errors();
}
