//  abs.hpp
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

#ifndef BOOST_ENUMS_MPL_ENUM_C_TAG_HPP
#define BOOST_ENUMS_MPL_ENUM_C_TAG_HPP

#include <boost/mpl/int.hpp>

namespace boost 
{
  namespace mpl 
  {
    //! Tag for the enum constants
    struct enum_c_tag : int_<11> {};

  }
}

#endif  // BOOST_ENUMS_MPL_ENUM_C_TAG_HPP
