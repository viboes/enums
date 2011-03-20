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
 
 @brief Generates a @c boost::enums::meta::size specialization.
 
 <b>Warning</b>: This macro is presented here for exposition only reasons and is not part of the interface.
 
 <b>Parameters</b>:
 - NS_EC, the @p NAMESPACES_CLASS sequence
 - EL, the @p ENUMERATOR_LIST sequence

 <b>Result</b>: 
 @code
 template <>                                                   
 struct size<BOOST_ENUMS_NAMESPACES_CLASS_QNAME(NS_EC)>        
 {                                                             
 static const std::size_t value = BOOST_PP_SEQ_SIZE(EL);                             
 };                                                            
 @endcode

 */

#define BOOST_ENUMS_ENUM_DCL_SIZE_SPE(NS_EC, EL)                \
  template <>                                                   \
  struct size<BOOST_ENUMS_NAMESPACES_CLASS_QNAME(NS_EC)>        \
  {                                                             \
    static const std::size_t value;                             \
  };                                                            \
  const std::size_t                                             \
  size<BOOST_ENUMS_NAMESPACES_CLASS_QNAME(NS_EC)>::value =      \
    BOOST_PP_SEQ_SIZE(EL);

/**
 
 @brief Generates a @c boost::enums::meta::pos/val specialization.
 
 <b>Warning</b>: This macro is presented here for exposition only reasons and is not part of the interface.
 
 <b>Parameters</b>:
 - P: the position in the ENUMERATOR_LIST sequence
 - QNAME, the @p NAMESPACES_CLASS qualified name
 - ED, the ENUMERATOR_DEFINITION sequence
 
 <b>Result</b>: 
 @code
 template <>                                               
 struct pos<QNAME, QNAME :: BOOST_ENUMS_ENUMERATOR_DEFINITION_ID(ED)> 
 {                                                         
   BOOST_STATIC_CONSTEXPR std::size_t value = P;           
 };                                                        
 template <>                                               
 struct val<QNAME, P>                                       
 {                                                         
   BOOST_STATIC_CONSTEXPR                                  
   boost::enums::native_type<QNAME>::type value =           
     QNAME::BOOST_ENUMS_ENUMERATOR_DEFINITION_ID(ED);     
 };
 
 @endcode
 
 */

#define BOOST_ENUMS_ENUM_DCL_POS_VAL_SPE(P, QNAME, ED)     \
  template <>                                               \
  struct pos<QNAME, QNAME :: BOOST_ENUMS_ENUMERATOR_DEFINITION_ID(ED)> \
  {                                                         \
    BOOST_STATIC_CONSTEXPR std::size_t value = P;           \
  };                                                        \
  template <>                                               \
  struct val<QNAME, P>                                       \
  {                                                         \
    BOOST_STATIC_CONSTEXPR                                  \
    boost::enums::native_type<QNAME>::type value =           \
      QNAME::BOOST_ENUMS_ENUMERATOR_DEFINITION_ID(ED);     \
  };

/**
 
 @brief Generates the enum_trait specialization.
 
 <b>Warning</b>: This macro is presented here for exposition only reasons and is not part of the interface.
 
 <b>Parameters</b>:
 - NS_EC, the NAMESPACES_CLASS sequence
 - TRAITER: the enum traiter template class 
 <b>Result</b>: 
 @code
 template <>                                                   
 struct enum_traits<BOOST_ENUMS_NAMESPACES_CLASS_QNAME(NS_EC)> 
   : TRAITER<BOOST_ENUMS_NAMESPACES_CLASS_QNAME(NS_EC)>        
 {};
 @endcode
 
 */

#define BOOST_ENUMS_ENUM_DCL_TRAITS_SPE(NS_EC, TRAITER)         \
  template <>                                                   \
  struct enum_traits<BOOST_ENUMS_NAMESPACES_CLASS_QNAME(NS_EC)> \
    : TRAITER<BOOST_ENUMS_NAMESPACES_CLASS_QNAME(NS_EC)>        \
  {};

/**
 
 @brief Generates all the needed specialization associated to an ordinal scoped enum.
 
 <b>Warning</b>: This macro is presented here for exposition only reasons and is not part of the interface.
 
 <b>Parameters</b>:
 - NS_EC, the NAMESPACES_CLASS sequence
 - TRAITER: the enum traiter template class 
 <b>Result</b>: 
 @code
  namespace boost {                                                 
    namespace enums {                                               
      namespace meta {                                              
        BOOST_ENUMS_ENUM_DCL_SIZE_SPE(NS_EC, EL)                    
        BOOST_PP_SEQ_FOR_EACH(                                      
          BOOST_ENUMS_ENUM_DCL_POS_VAL_SPE,                         
          BOOST_ENUMS_NAMESPACES_CLASS_QNAME(NS_EC),                
          EL                                                        
        )                                                           
        BOOST_ENUMS_ENUM_DCL_TRAITS_SPE(NS_EC, TRAITER)             
      }                                                            
    }                                                               
  } 
 @endcode
 
 */

#define BOOST_ENUMS_ENUM_DCL_SPE(NS_EC, EL, TRAITER)                \
  namespace boost {                                                 \
    namespace enums {                                               \
      namespace meta {                                              \
        BOOST_ENUMS_ENUM_DCL_SIZE_SPE(NS_EC, EL)                    \
        BOOST_PP_SEQ_FOR_EACH(                                      \
          BOOST_ENUMS_ENUM_DCL_POS_VAL_SPE,                         \
          BOOST_ENUMS_NAMESPACES_CLASS_QNAME(NS_EC),                \
          EL                                                        \
        )                                                           \
        BOOST_ENUMS_ENUM_DCL_TRAITS_SPE(NS_EC, TRAITER)             \
      }                                                             \
    }                                                               \
  }

/**
 
 @brief Generates all the needed definition associated to an ordinal scoped enum type with string conversions and constructors.
 
 <b>Parameters</b>:
 - NS_EC: the NAMESPACES_CLASS sequence
 - UT: the underlying type
 - EL: the ENUMERATOR_LIST sequence
 - TRAITER: the enum traiter template class 
 
 <b>Result</b>: 
 @code
 BOOST_ENUM_NS_TYPE_START(NS_EC, UT)                               
 {                                                                 
   BOOST_ENUMS_ENUMERATOR_LIST_GENERATE(EL)                       
 }                                                                 
 BOOST_ENUM_NS_TYPE_CONS_END(NS_EC, UT)                            
 BOOST_ENUMS_ENUM_DCL_SPE(NS_EC, EL, TRAITER)
 @endcode
 
 */

#define BOOST_ENUMS_ENUM_TYPE_DCL_CONS(NS_EC, UT, EL, TRAITER)      \
  BOOST_ENUM_NS_TYPE_START(NS_EC, UT)                               \
  {                                                                 \
    BOOST_ENUMS_ENUMERATOR_LIST_GENERATE(EL)                        \
  }                                                                 \
  BOOST_ENUM_NS_TYPE_CONS_END(NS_EC, UT)                            \
  BOOST_ENUMS_ENUM_DCL_SPE(NS_EC, EL, TRAITER)

/**
 
 @brief Generates all the needed definition associated to an ordinal scoped enum type with string conversions and without constructors.
 
 <b>Parameters</b>:
 - NS_EC: the NAMESPACES_CLASS sequence
 - UT: the underlying type
 - EL: the ENUMERATOR_LIST sequence
 - TRAITER: the enum traiter template class 
 
 <b>Result</b>: 
 @code
 BOOST_ENUM_NS_TYPE_START(NS_EC, UT)                               
 {                                                                 
 BOOST_ENUMS_ENUMERATOR_LIST_GENERATE(EL)                       
 }                                                                 
 BOOST_ENUM_NS_TYPE_NO_CONS_END(NS_EC, UT)                            
 BOOST_ENUMS_ENUM_DCL_SPE(NS_EC, EL, TRAITER)
 @endcode
 
 */
#define BOOST_ENUMS_ENUM_TYPE_DCL_NO_CONS(NS_EC, UT, EL, TRAITER)   \
  BOOST_ENUM_NS_TYPE_START(NS_EC, UT)                               \
  {                                                                 \
    BOOST_ENUMS_ENUMERATOR_LIST_GENERATE(EL)                        \
  }                                                                 \
  BOOST_ENUM_NS_TYPE_NO_CONS_END(NS_EC, UT)                         \
  BOOST_ENUMS_ENUM_DCL_SPE(NS_EC, EL, TRAITER)

/**
 
 @brief Generates all the needed definition associated to an ordinal scoped enum class with string conversions and with constructors.
 
 <b>Parameters</b>:
 - NS_EC: the NAMESPACES_CLASS sequence
 - UT: the underlying type
 - EL: the ENUMERATOR_LIST sequence
 - TRAITER: the enum traiter template class 
 
 <b>Result</b>: 
 @code
 BOOST_ENUM_NS_CLASS_START(NS_EC, UT)                               
 {                                                                 
 BOOST_ENUMS_ENUMERATOR_LIST_GENERATE(EL)                       
 }                                                                 
 BOOST_ENUM_NS_CLASS_CONS_END(NS_EC, UT)                            
 BOOST_ENUMS_ENUM_DCL_SPE(NS_EC, EL, TRAITER)
 @endcode
 
 */

#define BOOST_ENUMS_ENUM_CLASS_DCL_CONS(NS_EC, UT, EL, TRAITER)     \
  BOOST_ENUM_NS_CLASS_START(NS_EC, UT)                              \
  {                                                                 \
    BOOST_ENUMS_ENUMERATOR_LIST_GENERATE(EL)                        \
  }                                                                 \
  BOOST_ENUM_NS_CLASS_CONS_END(NS_EC, UT)                           \
  BOOST_ENUMS_ENUM_DCL_SPE(NS_EC, EL, TRAITER)

/**
 
 @brief Generates all the needed definition associated to an ordinal scoped enum class with string conversions and without constructors.
 
 <b>Parameters</b>:
 - NS_EC: the NAMESPACES_CLASS sequence
 - UT: the underlying type
 - EL: the ENUMERATOR_LIST sequence
 - TRAITER: the enum traiter template class 
 
 <b>Result</b>: 
 @code
 BOOST_ENUM_NS_CLASS_START(NS_EC, UT)                               
 {                                                                 
 BOOST_ENUMS_ENUMERATOR_LIST_GENERATE(EL)                       
 }                                                                 
 BOOST_ENUM_NS_CLASS_NO_CONS_END(NS_EC, UT)                            
 BOOST_ENUMS_ENUM_DCL_SPE(NS_EC, EL, TRAITER)
 @endcode
 
 */

#define BOOST_ENUMS_ENUM_CLASS_DCL_NO_CONS(NS_EC, UT, EL, TRAITER)  \
  BOOST_ENUM_NS_CLASS_START(NS_EC, UT)                              \
  {                                                                 \
    BOOST_ENUMS_ENUMERATOR_LIST_GENERATE(EL)                        \
  }                                                                 \
  BOOST_ENUM_NS_CLASS_NO_CONS_END(NS_EC, UT)                        \
  BOOST_ENUMS_ENUM_DCL_SPE(NS_EC, EL, TRAITER)




#endif // BOOST_ENUMS_PP_ENUMERATOR_LIST_HPP
