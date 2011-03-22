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


#ifndef BOOST_ENUMS_ORDINAL_FIRST_HPP
#define BOOST_ENUMS_ORDINAL_FIRST_HPP

#include <boost/enums/scoped/native_type.hpp>
#include <boost/enums/ordinal/val.hpp>

namespace boost
{
  namespace enums
  {
    namespace meta
    {
      //! meta-function: first element of an enumeration
      template <typename EC>
      struct first
      {
        BOOST_STATIC_CONSTEXPR typename native_type<EC>::type value = enums::meta::val<EC,0>::value;
      };
    }
    
    //! ordinal enum first.

    //! @return the the first element of an enumeration
    //! @throw Nothing
    template <typename EC>
    BOOST_CONSTEXPR EC first()
    {
        return meta::first<EC>::value;
    }
  }
}

#endif // BOOST_ENUMS_ORDINAL_FIRST_HPP
