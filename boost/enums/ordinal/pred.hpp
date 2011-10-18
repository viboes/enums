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
 The header \c <boost/enums/pred.hpp> declares a class template \c meta::pred<> and 
 a function \c pred() returning the predecessor of the enumeration element.
 */

#ifndef BOOST_ENUMS_ORDINAL_PRED_HPP
#define BOOST_ENUMS_ORDINAL_PRED_HPP

#include <boost/enums/scoped/native_type.hpp>
#include <boost/enums/ordinal/pos.hpp>
#include <boost/enums/ordinal/val.hpp>
#include <boost/static_assert.hpp>
#include <boost/assert.hpp>

namespace boost
{
  namespace enums
  {
    namespace meta
    {
      //! meta-function that gets the predecessor of an enumeration element.
      
      //! @Requires the position must be not 0.
      template <typename EC, typename native_type<EC>::type V>
      struct pred
      {
        BOOST_STATIC_ASSERT((pos<EC,V>::value!=0));
        BOOST_STATIC_CONSTEXPR typename native_type<EC>::type value =
          val<EC,pos<EC,V>::value-1>::value;
      };
    }
    
    //! ordinal enum predecesor.

    //! @Returns the predecessor of the enumeration element.
    //! @Throw Invalid parameter if the position is 0.
    template <typename EC>
    BOOST_CONSTEXPR EC pred(EC e)
    {
      BOOST_ASSERT(pos(e)!=0);
      return val<EC>(pos(e)-1);
    }
  }
}

#endif // BOOST_ENUMS_ORDINAL_PRED_HPP
