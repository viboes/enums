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
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>

void pass() {
  using namespace boost::enums;

  {
    BOOST_STATIC_ASSERT((boost::enums::is_enum<EnumClass>::value));
    BOOST_STATIC_ASSERT((!boost::enums::is_enum<int>::value));
  }

}
