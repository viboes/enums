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
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_ENUMS_ENUM_C_HPP
#define BOOST_ENUMS_ENUM_C_HPP

#include <boost/enums/mpl/enum_c_tag.hpp>
#include <boost/enums/scoped/native_type.hpp>
#include <boost/enums/scoped/underlying_type.hpp>
#include <cstddef>

namespace boost {
  namespace mpl {
      template <typename EC, typename enums::native_type<EC>::type V>
      //template <typename EC, int V>
      struct enum_c {
        typedef enum_c_tag tag;
        typedef typename enums::native_type<EC>::type native_type;
        BOOST_STATIC_CONSTEXPR typename enums::native_type<EC>::type value = V;
        typedef enum_c type;
        typedef typename enums::native_type<EC>::type value_type;
        typedef typename enums::underlying_type<EC>::type underlying_type;
        operator EC() const { return EC(V); }
      };

  }
}

#endif
