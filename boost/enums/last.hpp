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

#ifndef BOOST_ENUMS_LAST_HPP
#define BOOST_ENUMS_LAST_HPP

#include <boost/enums/enum_type.hpp>
#include <boost/enums/val.hpp>
#include <boost/enums/size.hpp>

namespace boost {
  namespace enums {
    namespace meta {
      template <typename EC>
      struct last 
      {
        static const typename enum_type<EC>::type value = enums::meta::val<EC,enums::meta::size<EC>::value-1>::value;
      };
    }
  }
}

#endif
