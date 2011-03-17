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

#ifndef BOOST_ENUMS_SCOPED_NATIVE_TYPE_HPP
#define BOOST_ENUMS_SCOPED_NATIVE_TYPE_HPP

#include <boost/config.hpp>

namespace boost
{
  namespace enums
  {
    //! meta-function to get the native enum type associated to an enum class
    //! or its emulation
    template <typename EC>
    struct enum_type
    {
#ifndef BOOST_ENUMS_DOXYGEN_INVOKED
  #ifdef BOOST_NO_SCOPED_ENUMS
		typedef typename EC::type type;
  #else
		typedef EC type;
  #endif
#else
		typedef <see below> type;
#endif
    };
  }
}

#endif // BOOST_ENUMS_SCOPED_NATIVE_TYPE_HPP
