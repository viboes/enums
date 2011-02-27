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

#ifndef BOOST_ENUMS_DEFAULT_VALUE_HPP
#define BOOST_ENUMS_DEFAULT_VALUE_HPP

#include <boost/config.hpp>

namespace boost {
  namespace enums {

    //!  build a enum class with the default value
    template <typename EC>
    inline EC default_value()
    {
#ifdef BOOST_NO_SCOPED_ENUMS
      return EC::default_value();
#else
      return EC();
#endif
    }

  }
}

#endif
