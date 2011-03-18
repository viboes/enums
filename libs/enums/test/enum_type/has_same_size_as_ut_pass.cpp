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

void pass() {
  using namespace boost::enums;

  { // has the same size as the underlying type
    BOOST_STATIC_ASSERT(sizeof(EnumClass)==sizeof(underlying_type<EnumClass>::type));
  }

}
