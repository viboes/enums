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

#ifndef BOOST_OPAQUE_ENUM_CLASS_MACRO_HPP
#define BOOST_OPAQUE_ENUM_CLASS_MACRO_HPP

#include <boost/enums/underlying_type.hpp>
#include <boost/enums/enum_type.hpp>
#include <boost/enums/default_value.hpp>
#include <boost/enums/enum_value.hpp>
#include <boost/conversion/convert_to.hpp>
#include <boost/config.hpp>
#include <boost/preprocessor/join.hpp>
#include <boost/preprocessor/if.hpp>
#include <boost/preprocessor/greater.hpp>
#include <boost/preprocessor/empty.hpp>
#include <boost/preprocessor/seq/enum.hpp>
#include <boost/preprocessor/seq/elem.hpp>

#define BOOST_OPAQUE_DETAIL_PAIR_TO_LITERAL(R, DATA, OPTPAIR) \
  BOOST_PP_JOIN(BOOST_PP_SEQ_ELEM(PAIR,0),DATA)               \
  BOOST_PP_IF(BOOST_PP_GREATER(BOOST_PP_SE_SIZE(PAIR),1),     \
    = BOOST_PP_SEQ_ELEM(PAIR,1),BOOST_PP_EMPTY)

#define BOOST_OPAQUE_DETAIL_OPTPAIR_TO_NAME(EC, OPTPAIR)      \
  EC::BOOST_PP_SEQ_ELEM(PAIR,0)

#define BOOST_OPAQUE_DETAIL_OPTPAIR_TO_INTERNAL_NAME(OPTPAIR) \
  EC::BOOST_PP_JOIN(BOOST_PP_SEQ_ELEM(PAIR,0),_)

#define BOOST_OPAQUE_DETAIL_CONST_DECLARATION(R, EC, OPTPAIR) \
  const EC BOOST_OPAQUE_DETAIL_OPTPAIR_TO_NAME(EC, OPTPAIR)   \


#define BOOST_OPAQUE_DETAIL_CONST_DEFINITION(R, EC, OPTPAIR)  \
  const EC BOOST_OPAQUE_DETAIL_OPTPAIR_TO_NAME(EC, OPTPAIR)   \
  = EC::convert_to(                                           \
  BOOST_OPAQUE_DETAIL_OPTPAIR_TO_INTERNAL_NAME(EC, OPTPAIR)   \
  ;


#ifndef BOOST_NO_SCOPED_ENUMS

#define BOOST_ENUM_CLASS(EC, UT, SEQ)           \
  enum class EC : UT {                          \
    BOOST_PP_SEQ_ENUM(                          \
      BOOST_PP_SEQ_FOR_EACH(                    \
        BOOST_OPAQUE_DETAIL_PAIR_TO_LITERAL,    \
        BOOST_PP_EMPTY,                         \
        SEQ                                     \
      )                                         \
    )                                           \
  };

#else // BOOST_NO_SCOPED_ENUMS

#define BOOST_ENUM_CLASS_CONSTRUCTORS(EC, UT)     \
  EC() : val_()  {  }                             \
  EC(UT v) : val_(v)  {  }

#define BOOST_ENUM_CLASS_EXT(EC, UT, SEQ, CONS)   \
  class EC                                        \
  {                                               \
  public:                                         \
    enum type  {                                  \
      BOOST_PP_SEQ_ENUM(                          \
        BOOST_PP_SEQ_FOR_EACH(                    \
          BOOST_OPAQUE_DETAIL_PAIR_TO_LITERAL,    \
          BOOST_PP_EMPTY,                                      \
          SEQ                                     \
        )                                         \
      )                                           \
    };                                            \
    typedef UT underlying_type;                   \
  private:                                        \
    underlying_type val_;                         \
  public:                                         \
    BOOST_PP_SEQ_FOR_EACH(                        \
      BOOST_OPAQUE_DETAIL_CONST_DECLARATION,      \
      EC,                                         \
      SEQ                                         \
    )                                             \
    BOOST_PP_IF(CONS,                             \
      BOOST_ENUM_CLASS_CONSTRUCTORS(EC, UT),      \
      BOOST_PP_EMPTY                              \
    )                                             \
    static EC default_value()                     \
    {                                             \
      EC res;                                     \
      res.val_=EnumClass::type();                 \
      return res;                                 \
    }                                             \
    static EC convert_to(underlying_type v)       \
    {                                             \
      EC res;                                     \
      res.val_=type(v);                           \
      return res;                                 \
    }                                             \
    type get() const                              \
    {                                             \
      return type(val_);                          \
    }                                             \
  };                                              \
  BOOST_PP_SEQ_FOR_EACH(                          \
    BOOST_OPAQUE_DETAIL_CONST_DEFINITION,         \
    EC,                                           \
    SEQ                                           \
  )                                               \


#define BOOST_ENUM_CLASS(EC, UT, SEQ)       \
  BOOST_ENUM_CLASS_EXT(EC, UT, SEQ, defined(BOOST_ENUMS_NO_CONSTRUCTORS))

#endif // BOOST_NO_SCOPED_ENUMS
#endif
