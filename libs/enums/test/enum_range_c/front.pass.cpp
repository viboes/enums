
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
// Based on libs/mpl/test/range_c.hpp
//
//////////////////////////////////////////////////////////////////////////////

#include <boost/enums/mpl/enum_range_c.hpp>
#include <boost/mpl/front.hpp>
#include "./Ex.hpp"
#include <boost/enums/mpl/enum_c.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/aux_/test.hpp>

MPL_TEST_CASE()
{
  typedef enum_range_c<EC3,0,1> range1;
  typedef enum_c<EC3,EC3::Enum0> v;

  //MPL_ASSERT_RELATION( v::value, ==, EC3::Enum0 );
    //MPL_ASSERT_RELATION( front<range1>::type::value, ==, EC3::Enum0 );
    MPL_ASSERT(( is_same<enum_c<EC3,front<range1>::type::value>,
        enum_c<EC3,EC3::Enum0> > ));
    MPL_ASSERT(( is_same< enum_c<EC3,front<range1>::type::value>,
        enum_c<EC3,EC3::Enum0> > ));
}


