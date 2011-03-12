
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
#include <boost/mpl/advance.hpp>
#include <boost/mpl/distance.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/back.hpp>
#include <boost/mpl/aux_/test.hpp>
#include "./Ex.hpp"
#include <boost/enums/mpl/enum_c.hpp>

MPL_TEST_CASE()
{
    typedef enum_range_c<EC3,0,0> range0;
    typedef enum_range_c<EC3,0,1> range1;
    typedef enum_range_c<EC3> range3;

    MPL_ASSERT_RELATION( size<range0>::value, ==, 0 );
    MPL_ASSERT_RELATION( size<range1>::value, ==, 1 );
    MPL_ASSERT_RELATION( size<range3>::value, ==, 3 );

    MPL_ASSERT(( empty<range0> ));
    MPL_ASSERT_NOT(( empty<range1> ));
    MPL_ASSERT_NOT(( empty<range3> ));

    MPL_ASSERT(( is_same< begin<range0>::type, end<range0>::type > ));
    MPL_ASSERT_NOT(( is_same<begin<range1>::type, end<range1>::type > ));
    MPL_ASSERT_NOT(( is_same<begin<range3>::type, end<range3>::type > ));

//    MPL_ASSERT_RELATION( front<range1>::type::value, ==, EC3::Enum0 );
//    MPL_ASSERT_RELATION( back<range1>::type::value, ==, EC3::Enum0 );
//    MPL_ASSERT_RELATION( front<range3>::type::value, ==, EC3::Enum0 );
//    MPL_ASSERT_RELATION( back<range3>::type::value, ==, EC3::Enum2 );
    MPL_ASSERT(( is_same<enum_c<EC3,front<range1>::type::value>,
        enum_c<EC3,EC3::Enum0> > ));
    MPL_ASSERT(( is_same< enum_c<EC3,back<range1>::type::value>,
        enum_c<EC3,EC3::Enum0> > ));
    MPL_ASSERT(( is_same< enum_c<EC3,front<range3>::type::value>,
        enum_c<EC3,EC3::Enum0> > ));
    MPL_ASSERT(( is_same< enum_c<EC3,back<range3>::type::value>,
        enum_c<EC3,EC3::Enum2> > ));
}

MPL_TEST_CASE()
{
    typedef enum_range_c<EC3> r;
    typedef begin<r>::type first;
    typedef end<r>::type last;

    MPL_ASSERT(( is_same< advance_c<first,3>::type, last > ));
    MPL_ASSERT(( is_same< advance_c<last,-3>::type, first > ));

    MPL_ASSERT_RELATION( ( mpl::distance<first,last>::value ), ==, 3 );

//    typedef advance_c<first,5>::type iter;
//    MPL_ASSERT_RELATION( deref<iter>::type::value, ==, 5 );
}
