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
#include <boost/static_assert.hpp>

void pass() {
  using namespace boost::enums;

  {
    BOOST_STATIC_ASSERT((meta::pos<EnumClass, EnumClass::Enum1>::value == 1));
  }

}
