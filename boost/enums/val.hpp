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

#ifndef BOOST_ENUMS_VALUE_HPP
#define BOOST_ENUMS_VALUE_HPP

#include <boost/enums/enum_traits.hpp>
#include <boost/enums/size.hpp>
#include <boost/assert.hpp>
#include <cstddef>

namespace boost
{
  namespace enums
  {
    namespace meta
    {
      //! meta-function used to associate the position to an element of an enumeration.
      //! This meta-function must be specialized for each position of the enumeration,
      //! starting from 0 to the predecessor of the size of the enumeration .
      template <typename EC, std::size_t I>
      struct val; 
    }
    //! Returns: The enum class element associated to the position
    //! Throws: Invalid parameter if the position is out of range
    template <typename EC>
    EC val(std::size_t p)
    {
      BOOST_ASSERT(p<(meta::size<EC>::value));
      return meta::enum_traits<EC>::val(p);
    }

  }
}

#endif
