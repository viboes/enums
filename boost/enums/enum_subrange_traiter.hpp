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

#ifndef BOOST_ENUMS_ENUM_RANGE_TRAITER_HPP
#define BOOST_ENUMS_ENUM_RANGE_TRAITER_HPP

#include <boost/enums/pos.hpp>
#include <boost/enums/first.hpp>
#include <boost/enums/last.hpp>
#include <boost/enums/emulator_type.hpp>

namespace boost {
  namespace enums {
    template <
        typename EC_type,
        EC_type First=enums::meta::first<typename emulator_type<EC_type>::type >::value,
        EC_type Last=enums::meta::last<typename emulator_type<EC_type>::type >::value
    >
    struct enum_subrange_traiter
    {
      typedef typename emulator_type<EC_type>::type EC;
      static const std::size_t first_index = enums::meta::pos<EC,First>::value;
      static const std::size_t last_index = enums::meta::pos<EC,Last>::value;

    };
  }
}

#endif // BOOST_ENUMS_ENUM_RANGE_TRAITER_HPP
