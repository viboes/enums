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

#ifndef BOOST_ENUMS_POS_HPP
#define BOOST_ENUMS_POS_HPP

#include <boost/enums/enum_type.hpp>
#include <boost/enums/enum_traits.hpp>


namespace boost {
  namespace enums {
    namespace meta {
      template <typename EC, typename enum_type<EC>::type V>
      struct pos; 
    }
    template <typename EC>
    int pos(EC e)
    {
      return enum_traits<EC>::pos(e);  
    }

  }
}

#endif
