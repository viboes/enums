
#ifndef BOOST_ENUMS_MPL_AUX_ENUM_RANGE_C_O1_SIZE_HPP_INCLUDED
#define BOOST_ENUMS_MPL_AUX_ENUM_RANGE_C_O1_SIZE_HPP_INCLUDED

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
// Based on boost/mpl/aux_/O1_size.hpp
//
//////////////////////////////////////////////////////////////////////////////

#include <boost/mpl/O1_size_fwd.hpp>
#include <boost/enums/mpl/aux_/enum_range_c/size.hpp>
#include <boost/enums/mpl/aux_/enum_range_c/tag.hpp>

namespace boost { namespace mpl {

template<>
struct O1_size_impl< aux::half_open_enum_range_tag >
    : size_impl< aux::half_open_enum_range_tag >
{
};

}}

#endif // BOOST_ENUMS_MPL_AUX_ENUM_RANGE_C_O1_SIZE_HPP_INCLUDED
