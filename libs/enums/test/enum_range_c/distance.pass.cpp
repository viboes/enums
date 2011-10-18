
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
#include <boost/mpl/distance.hpp>
#include "./Ex.hpp"
#include <boost/mpl/aux_/test.hpp>


MPL_TEST_CASE()
{
    typedef enum_range_c<EC3> r;
    typedef begin<r>::type first;
    typedef end<r>::type last;

    MPL_ASSERT_RELATION( ( mpl::distance<first,last>::value ), ==, 3 );

}
