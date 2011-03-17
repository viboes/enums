
#ifndef BOOST_ENUMS_MPL_ENUM_RANGE_C_HPP_INCLUDED
#define BOOST_ENUMS_MPL_ENUM_RANGE_C_HPP_INCLUDED

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
// Based on boost/mpl/range_c.hpp
//
//////////////////////////////////////////////////////////////////////////////

#include <boost/enums/mpl/enum_c.hpp>
#include <boost/enums/mpl/aux_/enum_range_c/front.hpp>
#include <boost/enums/mpl/aux_/enum_range_c/back.hpp>
#include <boost/enums/mpl/aux_/enum_range_c/size.hpp>
#include <boost/enums/mpl/aux_/enum_range_c/O1_size.hpp>
#include <boost/enums/mpl/aux_/enum_range_c/empty.hpp>
#include <boost/enums/mpl/aux_/enum_range_c/iterator.hpp>
#include <boost/enums/mpl/aux_/enum_range_c/tag.hpp>
#include <boost/enums/ordinal/size.hpp>
#include <boost/enums/ordinal/val.hpp>
#include <boost/mpl/integral_c.hpp>
#include <cstddef>

namespace boost { namespace mpl {

template<
      typename EC
    , std::size_t Start=0
    , std::size_t Finish=enums::meta::size<EC>::value
    >
struct enum_range_c
{
    typedef aux::half_open_enum_range_tag tag;
    typedef EC value_type;
    typedef enum_range_c type;

    typedef enum_c<EC, enums::meta::val<EC, Start>::value> start;
    //typedef enum_c<EC, enums::meta::val<EC, Finish>::value> finish;

    typedef enum_r_iter<EC,integral_c<std::size_t, Start> > begin;
    typedef enum_r_iter<EC,integral_c<std::size_t, Finish> > end;
};

}}

#endif // BOOST_ENUMS_MPL_ENUM_RANGE_C_HPP_INCLUDED
