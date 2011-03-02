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

#ifndef BOOST_ENUMS_VALUE_HPP
#define BOOST_ENUMS_VALUE_HPP

#include <boost/enums/enum_traits.hpp>

namespace boost {
  namespace enums {
    namespace meta {
      template <typename EC, int I>
      struct val; 
    }
    template <typename EC>
    EC val(std::size_t p)
    {
      return enum_traits<EC>::val(p);  
    }

  }
}

#endif
