
#ifndef BOOST_ENUMS_MPL_AUX_ENUM_RANGE_C_EMPTY_HPP_INCLUDED
#define BOOST_ENUMS_MPL_AUX_ENUM_RANGE_C_EMPTY_HPP_INCLUDED

//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 2011,2012.
// Distributed under the Boost
// Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or
// copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/enums for documentation.
//
// Based on boost/mpl/aux_/empty.hpp
//
//////////////////////////////////////////////////////////////////////////////

#include <boost/mpl/empty_fwd.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/enums/mpl/aux_/enum_range_c/tag.hpp>

namespace boost { namespace mpl {

template<>
struct empty_impl< aux::half_open_enum_range_tag >
{
    template< typename Range > struct apply
        : equal_to<
              typename begin<Range>::type::position
            , typename end<Range>::type::position
            >
    {
    };
};

}}

#endif // BOOST_ENUMS_MPL_AUX_ENUM_RANGE_C_EMPTY_HPP_INCLUDED
