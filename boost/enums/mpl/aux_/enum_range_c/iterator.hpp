
#ifndef BOOST_ENUMS_MPL_AUX_ENUM_RANGE_C_ITERATOR_HPP_INCLUDED
#define BOOST_ENUMS_MPL_AUX_ENUM_RANGE_C_ITERATOR_HPP_INCLUDED

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
// Based on boost/mpl/aux_/iterator.hpp
//
//////////////////////////////////////////////////////////////////////////////

#include <boost/mpl/iterator_tags.hpp>
#include <boost/mpl/advance_fwd.hpp>
#include <boost/mpl/distance_fwd.hpp>
#include <boost/mpl/next_prior.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/minus.hpp>
#include <boost/mpl/aux_/value_wknd.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>
#include <boost/enums/ordinal/size.hpp>
#include <boost/enums/ordinal/val.hpp>
#include <boost/enums/mpl/aux_/enum_range_c/tag.hpp>
#include <boost/mpl/integral_c.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>

namespace boost { namespace mpl {

template <
  typename EC, typename N
> struct lazy_enum_c
{
  typedef enum_c<EC,enums::meta::val<EC,N::value>::value> type;
};

// theoretically will work on any discrete numeric type
template< typename EC, typename N > struct enum_r_iter
{
    typedef aux::enum_r_iter_tag tag;
    typedef random_access_iterator_tag category;
    typedef EC enum_type;
    typedef N position;
    typedef typename eval_if<
        equal_to<N,integral_c<std::size_t, enums::meta::size<EC>::value> >,
        identity<void>,
        lazy_enum_c<EC,N>
    >::type type;

#if defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
    typedef enum_r_iter< EC, typename mpl::next<N>::type > next;
    typedef enum_r_iter< EC, typename mpl::prior<N>::type > prior;
#endif
};

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template<
      typename EC, typename N
    >
struct next< enum_r_iter<EC,N> >
{
    typedef enum_r_iter< EC, typename mpl::next<N>::type > type;
};

template<
      typename EC, typename N
    >
struct prior< enum_r_iter<EC,N> >
{
    typedef enum_r_iter< EC, typename mpl::prior<N>::type > type;
};

#endif


template<> struct advance_impl<aux::enum_r_iter_tag>
{
    template< typename Iter, typename Dist > struct apply
    {
        typedef typename Iter::position n_;
#if BOOST_WORKAROUND(BOOST_MSVC, <= 1300)
        typedef typename plus_impl<integral_c_tag,integral_c_tag>
            ::template apply<n_,Dist>::type m_;
#else
        typedef typename plus<n_,Dist>::type m_;
#endif
        // agurt, 10/nov/04: to be generic, the code have to do something along
        // the lines below...
        //
        // typedef typename apply_wrap1<
        //       numeric_cast< typename m_::tag, typename n_::tag >
        //     , m_
        //     >::type result_;
        //
        // ... meanwhile:
        
        typedef integral_c< 
              typename aux::value_type_wknd<n_>::type
            , BOOST_MPL_AUX_VALUE_WKND(m_)::value 
            > result_;
        
        typedef enum_r_iter<typename Iter::enum_type, result_> type;
    };
};

template<> struct distance_impl<aux::enum_r_iter_tag>
{
    template< typename Iter1, typename Iter2 > struct apply
        : minus<
              typename Iter2::position
            , typename Iter1::position
            >
    {
    };
};

}}

#endif // BOOST_ENUMS_MPL_AUX_ENUM_RANGE_C_ITERATOR_HPP_INCLUDED
