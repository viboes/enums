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

#ifndef BOOST_ENUMS_PP_NAMESPACES_HPP
#define BOOST_ENUMS_PP_NAMESPACES_HPP

#include <boost/preprocessor/if.hpp>
#include <boost/preprocessor/empty.hpp>
#include <boost/preprocessor/seq.hpp>
#include <boost/preprocessor/dec.hpp>
//#include <boost/preprocessor.hpp>


// (NS1) ... (NSn) (ENUM)
// ==>
// (NS1) ... (NSn)

#define BOOST_ENUMS_NAMESPACES_CLASS_NS(SEQ) \
  BOOST_PP_SEQ_POP_BACK(SEQ)


// (NS1) ... (NSn) (ENUM)
// ==>
// ENUM

#define BOOST_ENUMS_NAMESPACES_CLASS_ENUM(SEQ) \
  BOOST_PP_SEQ_ELEM(BOOST_PP_DEC(BOOST_PP_SEQ_SIZE(SEQ)), SEQ)

// (NS1) ... (NSn)
// ==>
// namespace NS1 { ... namespace NSn {

#define BOOST_ENUMS_NAMESPACES_OPEN_(r, data, elem) namespace elem {

#define BOOST_ENUMS_NAMESPACES_OPEN(SEQ) \
  BOOST_PP_SEQ_FOR_EACH(BOOST_ENUMS_NAMESPACES_OPEN_, ~, SEQ)


// (NS1) ... (NSn)
// ==>
// } ... }

#define BOOST_ENUMS_NAMESPACES_CLOSE_(r, data, elem) }
#define BOOST_ENUMS_NAMESPACES_CLOSE(SEQ) \
  BOOST_PP_SEQ_FOR_EACH(BOOST_ENUMS_NAMESPACES_CLOSE_, ~, SEQ)

// (NS1) ... (NSn)
// ==>
// NS1::...NSn::

#define BOOST_ENUMS_NAMESPACES_CLASS_QNAME_PRE_(r, data, elem) elem ::
#define BOOST_ENUMS_NAMESPACES_CLASS_QNAME_PRE(SEQ) \
  BOOST_PP_SEQ_FOR_EACH(BOOST_ENUMS_NAMESPACES_CLASS_QNAME_PRE_, ~, SEQ)

// (NS1) ... (NSn) (ENUM)
// ==>
// NS1::...NSn::ENUM 

#define BOOST_ENUMS_NAMESPACES_CLASS_QNAME(SEQ) \
  BOOST_ENUMS_NAMESPACES_CLASS_QNAME_PRE(BOOST_ENUMS_NAMESPACES_CLASS_NS(SEQ)) BOOST_ENUMS_NAMESPACES_CLASS_ENUM(SEQ)

#endif // BOOST_ENUMS_PP_NAMESPACES_HPP
