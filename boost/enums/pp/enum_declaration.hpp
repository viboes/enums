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

#ifndef BOOST_ENUMS_PP_ENUM_DECLARATION_HPP
#define BOOST_ENUMS_PP_ENUM_DECLARATION_HPP


#include <boost/enums/pp/enumerator_list.hpp>
#include <boost/enums/pp/namespaces.hpp>

#include <boost/preprocessor/seq.hpp>
//#include <boost/preprocessor.hpp>

/** @file


 @brief enum-declaration associated macros.

 
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

#define BOOST_ENUMS_ENUM_DCL_SIZE_SPE(NS_EC, EL)   \
  template <>                                                   \
  struct size<BOOST_ENUMS_NAMESPACES_CLASS_QNAME(NS_EC)>         \
  {                                                             \
    static const std::size_t value;                             \
  };                                                            \
  const std::size_t                                             \
  size<BOOST_ENUMS_NAMESPACES_CLASS_QNAME(NS_EC)>::value =       \
    BOOST_PP_SEQ_SIZE(EL);


#define BOOST_ENUMS_ENUM_DCL_POS_VAL_SPE(r, data, elem)     \
template <>                                               \
struct pos<data, data :: BOOST_ENUMS_ENUMERATOR_DEFINITION_ID(elem)>                              \
{                                                         \
BOOST_STATIC_CONSTEXPR std::size_t value = r;           \
};                                                        \
template <>                                               \
struct val<data, r>                                       \
{                                                         \
BOOST_STATIC_CONSTEXPR                                  \
boost::enums::native_type<data>::type value =           \
data::BOOST_ENUMS_ENUMERATOR_DEFINITION_ID(elem);                                           \
};



#if 0
#endif

#define BOOST_ENUMS_ENUM_DCL_TRAITS_SPE(NS_EC, TRAITER)         \
  template <>                                                   \
  struct enum_traits<BOOST_ENUMS_NAMESPACES_CLASS_QNAME(NS_EC)>  \
    : TRAITER<BOOST_ENUMS_NAMESPACES_CLASS_QNAME(NS_EC)>         \
  {};

#define BOOST_ENUMS_ENUM_DCL_SPE(NS_EC, EL, TRAITER)           \
  namespace boost {                                                 \
    namespace enums {                                               \
      namespace meta {                                              \
        BOOST_ENUMS_ENUM_DCL_SIZE_SPE(NS_EC, EL)                    \
        BOOST_PP_SEQ_FOR_EACH(                                          \
          BOOST_ENUMS_ENUM_DCL_POS_VAL_SPE,                         \
          BOOST_ENUMS_NAMESPACES_CLASS_QNAME(NS_EC),                 \
          EL                                                        \
        )                                                           \
        BOOST_ENUMS_ENUM_DCL_TRAITS_SPE(NS_EC, TRAITER)             \
      }                                                             \
    }                                                               \
  }


#define BOOST_ENUMS_ENUM_TYPE_DCL_CONS(NS_EC, UT, EL, TRAITER)      \
  BOOST_ENUM_NS_TYPE_START(NS_EC, UT)                               \
  {                                                                 \
    BOOST_ENUMS_ENUMERATOR_LIST_GENERATE(EL)                        \
  }                                                                 \
  BOOST_ENUM_NS_TYPE_CONS_END(NS_EC, UT)                            \
  BOOST_ENUMS_ENUM_DCL_SPE(NS_EC, EL, TRAITER)

#define BOOST_ENUMS_ENUM_TYPE_DCL_NO_CONS(NS_EC, UT, EL, TRAITER)   \
  BOOST_ENUM_NS_TYPE_START(NS_EC, UT)                               \
  {                                                                 \
    BOOST_ENUMS_ENUMERATOR_LIST_GENERATE(EL)                        \
  }                                                                 \
  BOOST_ENUM_NS_TYPE_NO_CONS_END(NS_EC, UT)                         \
  BOOST_ENUMS_ENUM_DCL_SPE(NS_EC, EL, TRAITER)

#define BOOST_ENUMS_ENUM_CLASS_DCL_CONS(NS_EC, UT, EL, TRAITER)     \
  BOOST_ENUM_NS_CLASS_START(NS_EC, UT)                              \
  {                                                                 \
    BOOST_ENUMS_ENUMERATOR_LIST_GENERATE(EL)                        \
  }                                                                 \
  BOOST_ENUM_NS_CLASS_CONS_END(NS_EC, UT)                           \
  BOOST_ENUMS_ENUM_DCL_SPE(NS_EC, EL, TRAITER)

#define BOOST_ENUMS_ENUM_CLASS_DCL_NO_CONS(NS_EC, UT, EL, TRAITER)  \
  BOOST_ENUM_NS_CLASS_START(NS_EC, UT)                              \
  {                                                                 \
    BOOST_ENUMS_ENUMERATOR_LIST_GENERATE(EL)                        \
  }                                                                 \
  BOOST_ENUM_NS_CLASS_NO_CONS_END(NS_EC, UT)                        \
  BOOST_ENUMS_ENUM_DCL_SPE(NS_EC, EL, TRAITER)




#endif // BOOST_ENUMS_PP_ENUMERATOR_LIST_HPP
