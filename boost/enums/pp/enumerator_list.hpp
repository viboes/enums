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

#ifndef BOOST_ENUMS_PP_ENUMERATOR_LIST_HPP
#define BOOST_ENUMS_PP_ENUMERATOR_LIST_HPP


#include <boost/preprocessor/seq.hpp>
#include <boost/enums/pp/enumerator_definition.hpp>

#include <boost/preprocessor.hpp>

/** @file


 @brief ENUMERATOR_LIST data type and macros.

 @details
 

 An ENUMERATOR_LIST is a variable sequence of ENUMERATOR_DEFINITION having a size > 0.

 <b>Example</b>:
 @code
  ( (Red) ) 
  ( (Green)(0) ) 
  ( (Blue)(2)("Azul") )
 @endcode

 All the operations are named BOOST_ENUMS_ENUMERATOR_LIST_.
 
 */ 

/**
 
 @brief Generates a enumerator_list from a ENUMERATOR_DEFINITION.
 
 <b>Parameters</b>:
 - EL, the ENUMERATOR_LIST

 <b>Result</b>: 
 @code
 ID(EL[0]) [= VAL(EL[0])], ...,ID(ED[L]) [= VAL(ED[L])] 
 @endcode
 

 */

#define BOOST_ENUMS_ENUMERATOR_DEFINITION_CPP_COMMA_ENUMERATOR_DEFINITION(r, data, elem) \
  , BOOST_ENUMS_ENUMERATOR_DEFINITION_CPP_ENUMERATOR_DEFINITION(elem)

#define BOOST_ENUMS_ENUMERATOR_LIST_GENERATE(EL) \
  BOOST_ENUMS_ENUMERATOR_DEFINITION_CPP_ENUMERATOR_DEFINITION(BOOST_PP_SEQ_ELEM(0,EL)) \
  BOOST_PP_SEQ_FOR_EACH(BOOST_ENUMS_ENUMERATOR_DEFINITION_CPP_COMMA_ENUMERATOR_DEFINITION,~,BOOST_PP_SEQ_POP_FRONT(EL))

#endif // BOOST_ENUMS_PP_ENUMERATOR_LIST_HPP
