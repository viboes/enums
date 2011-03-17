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

struct C
{
  int i;
  C() : i(){};
};

#if defined(BOOST_NO_UNRESTRICTED_UNION)
//#warning "not applicable as unrestricted union not available"
#else
// The ENUM can NOT be used as member of a union as it is the case of the underlying enum.
union U {
  C c;
  int i;
};
#endif

