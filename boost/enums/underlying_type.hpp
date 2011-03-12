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

#ifndef BOOST_ENUMS_UNDERLYING_TYPE_HPP
#define BOOST_ENUMS_UNDERLYING_TYPE_HPP

#include <boost/enums/config.hpp>
#ifndef BOOST_NO_UNDERLYING_TYPE
  #include <type_traits>
#endif

namespace boost
{
  namespace enums
  {

  //! T must be an enumeration type or the emulation of a enum class.
  //! The member typedef type name the underlying type of T.
  //! This meta-function must be specialized for the compilers providing enum
  //! class but don't providing the std::underlying_type meta-function.
    template <typename EC>
    struct underlying_type
    {
      #ifdef BOOST_NO_SCOPED_ENUMS
        typedef typename EC::underlying_type type;
      #else
        #ifndef BOOST_NO_UNDERLYING_TYPE
          typedef std::underlying_type<EC>::type type;
        #endif
      #endif
    };
  }
}

#endif
