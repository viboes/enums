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

#ifndef BOOST_ENUMS_EMULATOR_TYPE_HPP
#define BOOST_ENUMS_EMULATOR_TYPE_HPP

#include <boost/config.hpp>

namespace boost
{
  namespace enums
  {
    //! meta-function used to get the wrapping class of an enum when emulation
    //! is used or the enum class itself when available.
    //! This meta-function must be specialized for each enum class.
    template <typename EC_type>
    struct emulator_type;
  }
}

#endif // BOOST_ENUMS_EMULATOR_TYPE_HPP
