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

/** @file
 
 
 @brief @c NAMESPACES, @c NAMESPACES_CLASS PP data types and macros.
 
 @details
 
 
 A @c NAMESPACES is a variable sequence of namespace identifiers.
 
 @Example
 @code
 (NS1)(NS2)
 @endcode

 A @c NAMESPACES_CLASS is a variable sequence of namespace identifiers followed by a class identifier.
 
 @Example
 @code
 (NS1)(NS2)(ENUM)
 @endcode
 
 All the operations are prefixed by @c BOOST_ENUMS_NAMESAPCES_ or @c BOOST_ENUMS_NAMESAPCES_CLASS.
 
 */ 


#ifndef BOOST_ENUMS_PP_NAMESPACES_HPP
#define BOOST_ENUMS_PP_NAMESPACES_HPP

#include <boost/preprocessor/if.hpp>
#include <boost/preprocessor/empty.hpp>
#include <boost/preprocessor/seq.hpp>
#include <boost/preprocessor/dec.hpp>
//#include <boost/preprocessor.hpp>


/**
 
 @brief Get the @c NAMESPACES part of a @c NAMESPACES_CLASS.
 
 @Params
 @Param{SEQ,the @c NAMESPACES_CLASS}
 
 @Result the @c NAMESPACES part.
 
 */


#define BOOST_ENUMS_NAMESPACES_CLASS_NS(SEQ) \
  BOOST_PP_SEQ_POP_BACK(SEQ)

/**
 
 @brief Get the CLASS part of a @c NAMESPACES_CLASS.
 
 @Params
 @Param{SEQ,the @c NAMESPACES_CLASS}
 
 @Result the @c CLASS part.
 
 */


#define BOOST_ENUMS_NAMESPACES_CLASS_ENUM(SEQ) \
  BOOST_PP_SEQ_ELEM(BOOST_PP_DEC(BOOST_PP_SEQ_SIZE(SEQ)), SEQ)

/**
 
 @brief Generate the opening of the namespaces in @c NAMESPACES.
 
 @Params
 @Param{SEQ,the @c NAMESPACES sequence}
 
 @Result
 @code
 namespace NS1 { ... namespace NSn {
 @endcode
 */


#ifndef BOOST_ENUMS_DOXYGEN_INVOKED
#define BOOST_ENUMS_NAMESPACES_OPEN_(r, data, elem) namespace elem {
#endif

#define BOOST_ENUMS_NAMESPACES_OPEN(SEQ) \
  BOOST_PP_SEQ_FOR_EACH(BOOST_ENUMS_NAMESPACES_OPEN_, ~, SEQ)

/**
 
 @brief Generate the closing of the namespaces in @c NAMESPACES.
 
 @Params
 @Param{SEQ,the @c NAMESPACES sequence}
 
 @Result
 @code
 } ... }
 @endcode
 */

#define BOOST_ENUMS_NAMESPACES_CLOSE_(r, data, elem) }
#define BOOST_ENUMS_NAMESPACES_CLOSE(SEQ) \
  BOOST_PP_SEQ_FOR_EACH(BOOST_ENUMS_NAMESPACES_CLOSE_, ~, SEQ)

#ifndef BOOST_ENUMS_DOXYGEN_INVOKED
// (NS1) ... (NSn)
// ==>
// NS1::...NSn::

#define BOOST_ENUMS_NAMESPACES_CLASS_QNAME_PRE_(r, data, elem) elem ::
#define BOOST_ENUMS_NAMESPACES_CLASS_QNAME_PRE(SEQ) \
  BOOST_PP_SEQ_FOR_EACH(BOOST_ENUMS_NAMESPACES_CLASS_QNAME_PRE_, ~, SEQ)

#endif

/**
 
 @brief the qualified name associated to @c NAMESPACES_CLASS.
 
 @Params
 - SEQ: the @c NAMESPACES_CLASS sequence
 
 @Result
 @code
 NS1::...NSn::ENUM
 @endcode
 */

#define BOOST_ENUMS_NAMESPACES_CLASS_QNAME(SEQ) \
  BOOST_ENUMS_NAMESPACES_CLASS_QNAME_PRE(BOOST_ENUMS_NAMESPACES_CLASS_NS(SEQ)) BOOST_ENUMS_NAMESPACES_CLASS_ENUM(SEQ)

#endif // BOOST_ENUMS_PP_NAMESPACES_HPP
