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
#include <boost/enums/ordinal/succ.hpp>
#include <boost/enums/mpl/enum_c.hpp>
#include <boost/enums/mpl/equal_to.hpp>

void pass() {
  using namespace boost;
  using namespace boost::enums;

  {
    BOOST_STATIC_ASSERT((
      int(meta::succ<Ex::EnumClass,Ex::EnumClass::Default>::value) == int(Ex::EnumClass::Enum1)
    ));

    BOOST_STATIC_ASSERT((
      int(meta::succ<Ex::EnumClass,Ex::EnumClass::Enum1>::value) == int(Ex::EnumClass::Enum2)
    ));
  }

}
