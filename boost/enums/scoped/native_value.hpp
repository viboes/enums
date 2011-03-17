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

#ifndef BOOST_ENUMS_SCOPED_NATIVE_VALUE_HPP
#define BOOST_ENUMS_SCOPED_NATIVE_VALUE_HPP

#include <boost/config.hpp>
#include <boost/enums/scoped/native_type.hpp>

namespace boost {
  namespace enums {

    template <typename EC>
    inline
    typename enum_type<EC>::type enum_value(EC e)
    {
#ifdef BOOST_NO_SCOPED_ENUMS
      return e.enum_value();
#else
      return e;
#endif
    }
  }
}

#endif // BOOST_ENUMS_SCOPED_NATIVE_VALUE_HPP
