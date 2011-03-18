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

/*!
 \file
 \brief  
 The header \c <boost/enums/last.hpp> declares a class template \c meta::last<> and 
 a function \c last() returning the last element of an enumeration.
 */

#ifndef BOOST_ENUMS_ORDINAL_LAST_HPP
#define BOOST_ENUMS_ORDINAL_LAST_HPP

#include <boost/enums/scoped/native_type.hpp>
#include <boost/enums/ordinal/val.hpp>
#include <boost/enums/ordinal/size.hpp>

namespace boost
{
  namespace enums
  {
    namespace meta
    {
      //! meta-function: first element of an enumeration
      template <typename EC>
      struct last
      {
        BOOST_STATIC_CONSTEXPR typename native_type<EC>::type value = val<EC,size<EC>::value-1>::value;
      };
    }
    //! Returns the the last element of an enumeration
    //! Throws: Nothing
    template <typename EC>
    BOOST_CONSTEXPR EC last()
    {
        return meta::val<EC,meta::size<EC>::value-1>::value;
    }
  }
}

#endif // BOOST_ENUMS_ORDINAL_LAST_HPP
