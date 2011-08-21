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

#include "./EnumClass.hpp"
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_enum.hpp>

//enum E {E_a,E_b,E_c};
//BOOST_STATIC_ASSERT((boost::is_enum<E>::value));
//enum class EC {a,b,c};
//BOOST_STATIC_ASSERT((boost::is_enum<EC>::value));

//#include <type_traits>
//BOOST_STATIC_ASSERT((std::is_enum<E>::value));
//BOOST_STATIC_ASSERT((std::is_enum<EC>::value));

void pass() {
  using namespace boost::enums;

  { // has the same size as the underlying type
    //BOOST_STATIC_ASSERT((std::is_enum<EnumClass>::value));
    BOOST_STATIC_ASSERT((boost::enums::is_enum<EnumClass>::value));
    BOOST_STATIC_ASSERT((!boost::enums::is_enum<int>::value));
  }

}
