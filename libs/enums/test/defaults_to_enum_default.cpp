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

  { // defaults to the enum default
    EnumClass e =EnumClass() ;
    BOOST_TEST(e==EnumClass::Default);
  }
  { // defaults to the enum default
    EnumClass e = default_value<EnumClass>();
    BOOST_TEST(e==EnumClass::Default);
  }
  return boost::report_errors();

}
