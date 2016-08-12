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
    Ex::EnumClass e(Ex::EnumClass::Enum2);
    BOOST_TEST(e==Ex::EnumClass::Enum2);
  }
#ifndef BOOST_ENUMS_NOT_DEPENDS_ON_CONVERSION
  { // copy constructor emulation
    Ex::EnumClass e1=boost::conversion::explicit_convert_to<Ex::EnumClass>(Ex::EnumClass::Enum2);
    Ex::EnumClass e2=e1;
    BOOST_TEST(e2==Ex::EnumClass::Enum2);
  }
#endif
  return boost::report_errors();
}
