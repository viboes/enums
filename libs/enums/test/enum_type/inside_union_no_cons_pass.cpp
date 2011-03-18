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

#include <boost/enums/scoped.hpp>

BOOST_ENUM_CLASS_START(EC_NoCons, int) {
    E0 = 3,
    E1,
    E2
} BOOST_ENUM_CLASS_NO_CONS_END(EC_NoCons, int)
BOOST_ENUMS_SPECIALIZATIONS(EC_NoCons, int)

// The wrapper can be used as member of a union as it is the case of the underlying enum (When constructors are not defined).
union U {
  EC_NoCons e;
  int i;
};

void pass() {

  U u;
  u.e = EC_NoCons::E1;

}
