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
#ifndef BOOST_ENUMS_NOT_DEPENDS_ON_CONVERSION

  { // Explicit conversion from invalid int results in run-time error (undefined behavior)
    EnumClass e(boost::conversion::explicit_convert_to<EnumClass>((unsigned char)(6)));
    BOOST_TEST((unsigned char)(native_value(e))==(unsigned char)(6));
  }
#endif
  return boost::report_errors();
}
