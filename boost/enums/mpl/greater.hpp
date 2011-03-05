//  greater.hpp
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


#ifndef BOOST_ENUMS_MPL_GREATER_HPP
#define BOOST_ENUMS_MPL_GREATER_HPP

#include <boost/enums/mpl/enum_c_tag.hpp>
#include <boost/mpl/integral_c.hpp>
#include <boost/mpl/greater.hpp>

namespace boost {
namespace mpl {

template<>
struct greater_impl< enum_c_tag,enum_c_tag >
{
    template< typename R1, typename R2 > struct apply
        : greater<
            integral_c<typename E1::underlying_type, (typename E1::underlying_type)(E1::value)>,
            integral_c<typename E2::underlying_type, (typename E2::underlying_type)(E2::value)>
        >
    {
    };
};
}
}

#endif  // BOOST_ENUMS_MPL_GREATER_HPP
