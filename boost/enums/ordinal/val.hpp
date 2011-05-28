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
 The header @c <boost/enums/val.hpp> declares a class template @c meta::val<> and 
 a function @c val() associating a position to an element of an enumeration.
 */

#ifndef BOOST_ENUMS_VALUE_HPP
#define BOOST_ENUMS_VALUE_HPP

#include <boost/enums/ordinal/traits.hpp>
#include <boost/enums/ordinal/size.hpp>
#include <boost/enums/scoped/native_type.hpp>
#include <boost/assert.hpp>
#include <cstddef>

namespace boost
{
  namespace enums
  {
    namespace meta
    {
      //! meta-function used to associate the position to an element of an enumeration.
        
      //! @Note This meta-function must be specialized for each position of the enumeration,
      //! starting from 0 to the predecessor of the size of the enumeration .
      template <typename EC, std::size_t I>
#ifndef BOOST_ENUMS_DOXYGEN_INVOKED
        struct val; 
#else
        struct val
        {
          //! The nested @c value to be defined for each scoped enum
          //!  specialization.
          constexpr typename native_type<EC>::type value;
        };    
#endif
        
    }
    //! ordinal enum value  
      
    //! @Params
    //! @Param{p,the position}
    //! @returns The enum class element associated to the position @c p.
    //! @throws std::out_of_range if the position is out of range.
    template <typename EC>
    EC val(std::size_t p)
    {
      BOOST_ASSERT(p<(meta::size<EC>::value));
      return meta::enum_traits<EC>::val(p);
    }

  }
}

#endif
