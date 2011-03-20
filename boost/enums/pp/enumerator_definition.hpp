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

#ifndef BOOST_ENUMS_PP_ENUMERATOR_DEFINITION_HPP
#define BOOST_ENUMS_PP_ENUMERATOR_DEFINITION_HPP


#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/seq.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <boost/preprocessor/comparison/greater.hpp>
//#include <boost/preprocessor.hpp>

/** @file


 @brief ENUMERATOR_DEFINITION data type and macros.

 @details
 

 An ENUMERATOR_DEFINITION is a sequence legth 1, 2 or 3 where 
 - the fist element is a C++ identifier, 
 - the second is a C++ constant-expression and 
 - the 3rd a C++ string literal

 <b>Examples</b>:
 @code
  (Red)
  (Green)(0)
  (Blue)(2)("Azul")
 @endcode

 All the operations are named BOOST_ENUMS_ENUMERATOR_DEFINITION_:
 - ID : ED -> first element
 - VAL : ED, DEF -> second element or DEF
 - STR : ED -> third element or "ID"
 
 */ 

/**

 @brief This macro is used to get the identifier from a ENUMERATOR_DEFINITION.
 
 <b>Parameters</b>:
 - ED: the ENUMERATOR_DEFINITION
 
 <b>Result</b>: the first element of @p ED.

 */

#define BOOST_ENUMS_ENUMERATOR_DEFINITION_ID(ED)                      \
  BOOST_PP_SEQ_ELEM(0, ED)
  
#ifndef BOOST_ENUMS_DOXYGEN_INVOKED

#define BOOST_ENUMS_DETAIL_ENUMERATOR_DEFINITION_VAL_OK(ED, DEFAULT)  \
  BOOST_PP_SEQ_ELEM(1, ED)

#define BOOST_ENUMS_DETAIL_ENUMERATOR_DEFINITION_VAL_KO(ED, DEFAULT)  \
  DEFAULT

#endif

/**
 
 @brief This macro is used to get the constant-expression from a ENUMERATOR_DEFINITION.
 
 <b>Parameters</b>:
 - ED: the ENUMERATOR_DEFINITION }
 - DEFAULT: the default value when there is no second element.

 <b>Result</b>: the second element of the @p ED or @p DEFAULT.
 
 */
#define BOOST_ENUMS_ENUMERATOR_DEFINITION_VAL(ED,DEFAULT)             \
  BOOST_PP_IIF(                                                       \
    BOOST_PP_GREATER(BOOST_PP_SEQ_SIZE(ED),1)                         \
    , BOOST_ENUMS_DETAIL_ENUMERATOR_DEFINITION_VAL_OK                 \
    , BOOST_ENUMS_DETAIL_ENUMERATOR_DEFINITION_VAL_KO                 \
  )(ED,DEFAULT)

#ifndef BOOST_ENUMS_DOXYGEN_INVOKED

#define BOOST_ENUMS_DETAIL_ENUMERATOR_DEFINITION_STR_OK(ED)           \
  BOOST_PP_SEQ_ELEM(2, ED)

#define BOOST_ENUMS_DETAIL_ENUMERATOR_DEFINITION_STR_KO(ED)           \
  BOOST_PP_STRINGIZE(BOOST_ENUMS_ENUMERATOR_DEFINITION_ID(ED))

#endif
/**
 
 @brief This macro is used to get the string literal from a ENUMERATOR_DEFINITION.

 <b>Parameters</b>:
 - ED, the ENUMERATOR_DEFINITION.

 <b>Result</b>: the third element of @p ED or the string representation of ED'ID.
 
 */
#define BOOST_ENUMS_ENUMERATOR_DEFINITION_STR(ED)                     \
  BOOST_PP_IIF(                                                       \
    BOOST_PP_GREATER(BOOST_PP_SEQ_SIZE(ED),2)                         \
    , BOOST_ENUMS_DETAIL_ENUMERATOR_DEFINITION_VAL_OK                 \
    , BOOST_ENUMS_DETAIL_ENUMERATOR_DEFINITION_VAL_KO                 \
  )(ED)

#ifndef BOOST_ENUMS_DOXYGEN_INVOKED

#define BOOST_ENUMS_DETAIL_ENUMERATOR_DEFINITION_ASSIGN_VAL(ED)  \
  = BOOST_PP_SEQ_ELEM(1, ED)

#define BOOST_ENUMS_DETAIL_NOTHING_1(ED)


/**
 
 @brief This macro is used to get the constant-expression from a ENUMERATOR_DEFINITION.
 
 <b>Parameters</b>:
 - ED: the ENUMERATOR_DEFINITION }
 - DEFAULT: the default value when there is no second element.
 
 <b>Result</b>: the second element of the @p ED or @p DEFAULT.
 
 */
#define BOOST_ENUMS_ENUMERATOR_DEFINITION_OPT_ASSIGN_VAL(ED)        \
  BOOST_PP_IIF(                                                     \
  BOOST_PP_GREATER(BOOST_PP_SEQ_SIZE(ED),1)                         \
    , BOOST_ENUMS_DETAIL_ENUMERATOR_DEFINITION_ASSIGN_VAL           \
    , BOOST_ENUMS_DETAIL_NOTHING_1                                  \
  )(ED)
#endif

/**
 
 @brief generates a enumerator_definition from a ENUMERATOR_DEFINITION.
 
 <b>Parameters</b>:
 - ED, the ENUMERATOR_DEFINITION
 - DEFAULT: the default value when there is no second element.

 <b>Result</b>: 
 @code
 ID(ED) [= VAL(ED)]
 @endcode
 
 <b>Note</b>: The optional part is generated if there is a second element.
 
 */
#define BOOST_ENUMS_ENUMERATOR_DEFINITION_CPP_ENUMERATOR_DEFINITION(ED) \
  BOOST_ENUMS_ENUMERATOR_DEFINITION_ID(ED) \
  BOOST_ENUMS_ENUMERATOR_DEFINITION_OPT_ASSIGN_VAL(ED)

#endif // BOOST_ENUMS_PP_ENUMERATOR_DEFINITION_HPP
