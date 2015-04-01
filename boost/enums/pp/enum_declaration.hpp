//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 2011,2015.
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


#include <boost/enums/config.hpp>
#include <boost/enums/pp/enumerator_list.hpp>
#include <boost/enums/pp/namespaces.hpp>

#include <boost/preprocessor/seq.hpp>
#include <boost/enums/ordinal.hpp>
#include <boost/enums/scoped.hpp>

/** @file


 @brief enum-declaration associated macros.


 */
#define BOOST_ENUMS_ENUM_DCL_STR_TO_ID2(P, ENUM, ED)                   \
  if (strcmp(                                                         \
        str,                                                          \
        BOOST_ENUMS_ENUMERATOR_DEFINITION_STR(ED)                     \
     ) == 0)                                                          \
  {                                                                   \
    return ENUM(                                   \
              ENUM::BOOST_ENUMS_ENUMERATOR_DEFINITION_ID(ED)          \
            );                                                        \
  }

#define BOOST_ENUMS_ENUM_DCL_STR_TO_ID(P, ENUM, ED)                   \
  if (std::string(str)==                                                         \
        BOOST_ENUMS_ENUMERATOR_DEFINITION_STR(ED)                     \
     )                                                          \
  {                                                                   \
    return ENUM(                                   \
              ENUM::BOOST_ENUMS_ENUMERATOR_DEFINITION_ID(ED)          \
            );                                                        \
  }

#define BOOST_ENUMS_ENUM_DCL_ID_TO_STR(P, ENUM, ED)                   \
  case ENUM::BOOST_ENUMS_ENUMERATOR_DEFINITION_ID(ED) :         \
    return(BOOST_ENUMS_ENUMERATOR_DEFINITION_STR(ED));


#define BOOST_ENUMS_DCL_STRING_CONVERSIONS(ENUM, EL)                        \
  inline                                                              \
  ENUM explicit_convert_to(                                                          \
      const char* str,                                                      \
      boost::conversion::dummy::type_tag<ENUM> const&                                   \
    )                                                                       \
  {                                                                         \
    BOOST_PP_SEQ_FOR_EACH(                                                  \
                        BOOST_ENUMS_ENUM_DCL_STR_TO_ID,                     \
                        ENUM,                                               \
                        EL                                                  \
                        )                                                   \
    throw "invalid string for "                                             \
      BOOST_PP_STRINGIZE(ENUM);                                             \
  }                                                                         \
                                                                            \
  inline                                                              \
  ENUM explicit_convert_to(                                                          \
    const std::string& str,                                                 \
    boost::conversion::dummy::type_tag<ENUM> const&                                     \
  )                                                                         \
  {                                                                         \
    return boost::conversion::explicit_convert_to<ENUM>(                                         \
      str.c_str()                                                           \
    );                                                                      \
  }                                                                         \
                                                                            \
  inline                                                              \
  const char* c_str(ENUM e)                                                 \
  {                                                                         \
    switch (boost::enums::native_value(e))                                  \
    {                                                                       \
      BOOST_PP_SEQ_FOR_EACH(                                                \
        BOOST_ENUMS_ENUM_DCL_ID_TO_STR,                                     \
        ENUM,                                                               \
        EL                                                                  \
      )                                                                     \
      default:                                                              \
        throw "invalid value for "                                          \
          BOOST_PP_STRINGIZE(ENUM);                                         \
    }                                                                       \
  }                                                                         \


#ifndef BOOST_ENUMS_NOT_DEPENDS_ON_CONVERSION
#define BOOST_ENUMS_DCL_STRING_CONVERSIONS_SPECIALIZATIONS(ENUM, EL)        \
    namespace boost {                                                       \
      namespace conversion {                                                \
        template <>                                                         \
        struct explicit_converter_cp<ENUM,const char*> : true_type {        \
          ENUM operator()(const char* str) {                                \
            BOOST_PP_SEQ_FOR_EACH(                                          \
                        BOOST_ENUMS_ENUM_DCL_STR_TO_ID,                     \
                        ENUM,                                               \
                        EL                                                  \
                        )                                                   \
            throw "invalid string for "                                     \
                BOOST_PP_STRINGIZE(ENUM);                                   \
          }                                                                 \
        };                                                                  \
        template <>                                                         \
        struct explicit_converter_cp<ENUM,std::string> : true_type {        \
          ENUM operator()(std::string const& str) {                                  \
            return boost::conversion::explicit_convert_to<ENUM>(            \
              str.c_str()                                                   \
            );                                                              \
          }                                                                 \
        };                                                                  \
      }                                                                     \
    }                                                                       \
  inline                                                                    \
  const char* c_str(ENUM e)                                                 \
  {                                                                         \
    switch (boost::enums::native_value(e))                                  \
    {                                                                       \
      BOOST_PP_SEQ_FOR_EACH(                                                \
        BOOST_ENUMS_ENUM_DCL_ID_TO_STR,                                     \
        ENUM,                                                               \
        EL                                                                  \
      )                                                                     \
      default:                                                              \
        throw "invalid value for "                                          \
          BOOST_PP_STRINGIZE(ENUM);                                         \
    }                                                                       \
  }                                                                         \

#else
#define BOOST_ENUMS_DCL_STRING_CONVERSIONS_SPECIALIZATIONS(ENUM, EL)        \
  inline                                                                    \
  const char* c_str(ENUM e)                                                 \
  {                                                                         \
    switch (boost::enums::native_value(e))                                  \
    {                                                                       \
      BOOST_PP_SEQ_FOR_EACH(                                                \
        BOOST_ENUMS_ENUM_DCL_ID_TO_STR,                                     \
        ENUM,                                                               \
        EL                                                                  \
      )                                                                     \
      default:                                                              \
        throw "invalid value for "                                          \
          BOOST_PP_STRINGIZE(ENUM);                                         \
    }                                                                       \
  }
#endif

/**

 @brief Generates a @c boost::enums::meta::size specialization.

 @Remark This macro is presented here for exposition only reasons and is not part of the interface.

 @Params
 @Param{NS_EC, the @p NAMESPACES_CLASS sequence}
 @Param{EL, the @p ENUMERATOR_LIST sequence}

 @Result
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
  enum {value=BOOST_PP_SEQ_SIZE(EL)};\
  };                                                            \
// None of the fiollowing declaration works when we need the size as template parameter ?
//    BOOST_STATIC_CONSTANT(std::size_t,  value=BOOST_PP_SEQ_SIZE(EL));
//    static const std::size_t value=BOOST_PP_SEQ_SIZE(EL);

#define BOOST_ENUMS_ENUM_DCL_SIZE_SPE2(NS_EC, EL)                \
  const std::size_t                                             \
  size<BOOST_ENUMS_NAMESPACES_CLASS_QNAME(NS_EC)>::value =      \
    BOOST_PP_SEQ_SIZE(EL);

/**

 @brief Generates a @c boost::enums::meta::pos/val specialization.

 @Remark This macro is presented here for exposition only reasons and is not part of the interface.

 @Params
 @Param{P,NOT USED}
 @Param{QNAME,the @p NAMESPACES_CLASS qualified name}
 @Param{P,the position in the @c ENUMERATOR_LIST sequence}
 @Param{ED, the @c ENUMERATOR_DEFINITION sequence}

 @Result
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

#define BOOST_ENUMS_ENUM_DCL_POS_VAL_SPE(R, QNAME, P, ED)     \
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

 @Remark This macro is presented here for exposition only reasons and is not part of the interface.

 @Params
 @Param{NS_EC, the @c NAMESPACES_CLASS sequence}
 @Param{TRAITER,the enum traiter template class}

 @Result
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

 @Remark This macro is presented here for exposition only reasons and is not part of the interface.

 @Params
 @Param{NS_EC,the @c NAMESPACES_CLASS sequence}
 @Param{TRAITER,the enum traiter template class}
 @Result
 @code
  namespace boost {
    namespace enums {
      namespace meta {
        BOOST_ENUMS_ENUM_DCL_SIZE_SPE(NS_EC, EL)
        BOOST_PP_SEQ_FOR_EACH_I(
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
        BOOST_PP_SEQ_FOR_EACH_I(                                      \
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

 @Params
 @Param{NS_EC, the @c NAMESPACES_CLASS sequence}
 @Param{UT,the underlying type}
 @Param{EL,the @c ENUMERATOR_LIST sequence}
 @Param{TRAITER,the enum traiter template class}

 @Result
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
  }                                                                \
  BOOST_ENUM_NS_TYPE_CONS_END(NS_EC, UT)                            \
  BOOST_ENUMS_ENUM_DCL_SPE(NS_EC, EL, TRAITER) \
  BOOST_ENUMS_DCL_STRING_CONVERSIONS_SPECIALIZATIONS(BOOST_ENUMS_NAMESPACES_CLASS_QNAME(NS_EC), EL)

#if 0
  BOOST_ENUMS_NAMESPACES_OPEN(BOOST_ENUMS_NAMESPACES_CLASS_NS(NS_EC)) \
  BOOST_ENUMS_DCL_STRING_CONVERSIONS(BOOST_ENUMS_NAMESPACES_CLASS_ENUM(NS_EC), EL) \
  BOOST_ENUMS_NAMESPACES_CLOSE(BOOST_ENUMS_NAMESPACES_CLASS_NS(NS_EC))
#endif

/**

 @brief Generates all the needed definition associated to an ordinal scoped enum type with string conversions and without constructors.

 @Params
 @Param{NS_EC, the @c NAMESPACES_CLASS sequence}
 @Param{UT,the underlying type}
 @Param{EL,the @c ENUMERATOR_LIST sequence}
 @Param{TRAITER,the enum traiter template class}

 @Result
 @cond
 BOOST_ENUMS_ENUM_TYPE_DCL_NO_CONS((NS1)...(NSk)(EC), UT, ((E1))...((En)), TRAITER)

 namespace NS1 {
 ...
 namespace NSk {

 class EC {
 public:
   enum type { E1, ... En };
   typedef UT underlying_type;
  private:
    underlying_type val_;
  public:
    operator type() { return type(val_); }
    EC& operator =(type rhs) {
      val_=static_cast<underlying_type>(rhs);
      return *this;
    }
    static EC default_value() {
      EC res;
      res.val_=static_cast<underlying_type>(EC::type());
      return res;
    }
    type native_value() const { return type(val_); }
    underlying_type underlying_value() const { return val_; }
 };
 } // NSk
 ...
 } // NS1
 @endcond
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
  BOOST_ENUMS_ENUM_DCL_SPE(NS_EC, EL, TRAITER) \
  BOOST_ENUMS_DCL_STRING_CONVERSIONS_SPECIALIZATIONS(BOOST_ENUMS_NAMESPACES_CLASS_QNAME(NS_EC), EL)

#if 0
  BOOST_ENUMS_NAMESPACES_OPEN(BOOST_ENUMS_NAMESPACES_CLASS_NS(NS_EC)) \
  BOOST_ENUMS_DCL_STRING_CONVERSIONS(BOOST_ENUMS_NAMESPACES_CLASS_ENUM(NS_EC), EL) \
  BOOST_ENUMS_NAMESPACES_CLOSE(BOOST_ENUMS_NAMESPACES_CLASS_NS(NS_EC))
#endif

/**

 @brief Generates all the needed definition associated to an ordinal scoped enum class with string conversions and with constructors.

 @Params
 @Param{NS_EC, the @c NAMESPACES_CLASS sequence}
 @Param{UT,the underlying type}
 @Param{EL,the @c ENUMERATOR_LIST sequence}
 @Param{TRAITER,the enum traiter template class}

 @Result
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
  }                                                                \
  BOOST_ENUM_NS_CLASS_CONS_END(NS_EC, UT)                           \
  BOOST_ENUMS_ENUM_DCL_SPE(NS_EC, EL, TRAITER) \
  BOOST_ENUMS_DCL_STRING_CONVERSIONS_SPECIALIZATIONS(BOOST_ENUMS_NAMESPACES_CLASS_QNAME(NS_EC), EL)

#if 0
  BOOST_ENUMS_NAMESPACES_OPEN(BOOST_ENUMS_NAMESPACES_CLASS_NS(NS_EC)) \
  BOOST_ENUMS_DCL_STRING_CONVERSIONS(BOOST_ENUMS_NAMESPACES_CLASS_ENUM(NS_EC), EL) \
  BOOST_ENUMS_NAMESPACES_CLOSE(BOOST_ENUMS_NAMESPACES_CLASS_NS(NS_EC))
#endif

/**

 @brief Generates all the needed definition associated to an ordinal scoped enum class with string conversions and without constructors.

 @Params
 @Param{NS_EC, the @c NAMESPACES_CLASS sequence}
 @Param{UT,the underlying type}
 @Param{EL,the @c ENUMERATOR_LIST sequence}
 @Param{TRAITER,the enum traiter template class}

 @Result
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
  }                                                                \
  BOOST_ENUM_NS_CLASS_NO_CONS_END(NS_EC, UT)                        \
  BOOST_ENUMS_ENUM_DCL_SPE(NS_EC, EL, TRAITER) \
  BOOST_ENUMS_DCL_STRING_CONVERSIONS_SPECIALIZATIONS(BOOST_ENUMS_NAMESPACES_CLASS_QNAME(NS_EC), EL)

#if 0
  BOOST_ENUMS_NAMESPACES_OPEN(BOOST_ENUMS_NAMESPACES_CLASS_NS(NS_EC)) \
  BOOST_ENUMS_DCL_STRING_CONVERSIONS(BOOST_ENUMS_NAMESPACES_CLASS_ENUM(NS_EC), EL) \
  BOOST_ENUMS_NAMESPACES_CLOSE(BOOST_ENUMS_NAMESPACES_CLASS_NS(NS_EC))
#endif




#endif // BOOST_ENUMS_PP_ENUMERATOR_LIST_HPP
