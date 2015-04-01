//  less_equal.hpp
//
//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 2011,2014.
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


#ifndef BOOST_ENUMS_MPL_LESS_EQUAL_HPP
#define BOOST_ENUMS_MPL_LESS_EQUAL_HPP

#include <boost/enums/mpl/enum_c_tag.hpp>
#include <boost/mpl/integral_c.hpp>
#include <boost/mpl/less_equal.hpp>

namespace boost
{
  namespace mpl
  {
    //! \c less_equal_impl specialization for \c enum_c_tag
    template<>
    struct less_equal_impl< enum_c_tag,enum_c_tag >
    {
      template< typename E1, typename E2 > struct apply
        : less_equal<
            integral_c<typename E1::underlying_type, (typename E1::underlying_type)(E1::value)>,
            integral_c<typename E2::underlying_type, (typename E2::underlying_type)(E2::value)>
        >
      {
      };
    };
  }
}

#endif  // BOOST_ENUMS_MPL_LESS_EQUAL_HPP
