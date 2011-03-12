
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
#include <boost/mpl/begin.hpp>
#include <boost/mpl/end.hpp>
#include <boost/mpl/aux_/test.hpp>
#include "./Ex.hpp"

MPL_TEST_CASE()
{
    typedef enum_range_c<EC3,0,0> range0;
    typedef enum_range_c<EC3,0,1> range1;

    MPL_ASSERT(( is_same< begin<range0>::type, end<range0>::type > ));
    MPL_ASSERT_NOT(( is_same<begin<range1>::type, end<range1>::type > ));

}

