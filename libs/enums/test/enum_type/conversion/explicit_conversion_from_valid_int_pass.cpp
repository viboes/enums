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

  { // Explicit conversion from valid int works
    //EnumClass e((unsigned char)(4));
    EnumClass e(EnumClass(4));
    //EnumClass e(boost::conversion::explicit_convert_to<EnumClass>((unsigned char)(4)));
    BOOST_TEST(e==EnumClass::Enum1);
  }

  return boost::report_errors();
}
