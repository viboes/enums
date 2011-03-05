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

void fail() {
  using namespace boost::enums;

  { // has the same size as the underlying type
    enum_type<EnumClass>::type e= meta::val<EnumClass,3>::value;
    (void)(e);
  }

}
