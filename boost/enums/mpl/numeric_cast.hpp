//  numeric_cast.hpp
//
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
// Adapted from libcxx tests
//
//////////////////////////////////////////////////////////////////////////////


#ifndef BOOST_ENUMS_MPL_NUMERIC_CAST_HPP
#define BOOST_ENUMS_MPL_NUMERIC_CAST_HPP

#include <boost/enums/mpl/enum_c.hpp>
#include <boost/mpl/integral_c.hpp>
#include <boost/enums/mpl/enum_c_tag.hpp>
#include <boost/mpl/numeric_cast.hpp>

namespace boost 
{
  namespace mpl 
  {
	//! \c numeric_cast specialization for \c integral_c_tag and \c enum_c_tag
    template<> struct numeric_cast< integral_c_tag,enum_c_tag >
    {
      template< typename N > struct apply
        : integral_c< typename N::underlying_type, N::value >
      {
      };
    };
  }
}

#endif  // BOOST_ENUMS_MPL_NUMERIC_CAST_HPP
