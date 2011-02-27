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

#ifndef BOOST_ENUMS_ENUM_TYPE_HPP
#define BOOST_ENUMS_ENUM_TYPE_HPP

#include <boost/config.hpp>

namespace boost {
  namespace enums {

    template <typename EC>
    struct enum_type
    {
#ifdef BOOST_NO_SCOPED_ENUMS
      typedef typename EC::type type;
#else
      typedef EC type;
#endif
    };
  }
}

#endif
