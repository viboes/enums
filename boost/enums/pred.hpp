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

#ifndef BOOST_ENUMS_PRED_HPP
#define BOOST_ENUMS_PRED_HPP

#include <boost/enums/enum_type.hpp>
#include <boost/enums/pos.hpp>
#include <boost/enums/val.hpp>
#include <boost/static_assert.hpp>
#include <boost/assert.hpp>

namespace boost
{
  namespace enums
  {
    namespace meta
    {
      //! meta-function that gets the predecessor of an enumeration element
      //! Pre-condition: the position must be not 0
      template <typename EC, typename enum_type<EC>::type V>
      struct pred
      {
        BOOST_STATIC_ASSERT((pos<EC,V>::value!=0));
        BOOST_STATIC_CONSTEXPR typename enum_type<EC>::type value =
          val<EC,pos<EC,V>::value-1>::value;
      };
    }

    //! Returns: the predecessor of the enumeration element
    //! Throws: Invalid parameter if the position is 0
    template <typename EC>
    BOOST_CONSTEXPR EC pred(EC e)
    {
      BOOSt_ASSERT(pos(e)!=0);
      return val<EC>(pos(e)-1);
    }
  }
}

#endif
