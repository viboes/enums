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

#ifndef BOOST_ENUMS_FIRST_HPP
#define BOOST_ENUMS_FIRST_HPP

#include <boost/enums/enum_type.hpp>
#include <boost/enums/val.hpp>

namespace boost {
  namespace enums {
    namespace meta {
      template <typename EC>
      struct first 
      {
        static const typename enum_type<EC>::type value = enums::meta::val<EC,0>::value;
      };
    }
  }
}

#endif
