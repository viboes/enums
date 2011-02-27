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

#ifndef BOOST_ENUMS_EMULATION_HPP
#define BOOST_ENUMS_EMULATION_HPP

#include <boost/enums/underlying_type.hpp>
#include <boost/enums/enum_type.hpp>
#include <boost/enums/default_value.hpp>
#include <boost/enums/get_value.hpp>
#include <boost/conversion/convert_to.hpp>
#include <boost/config.hpp>
#include <boost/preprocessor/if.hpp>
#include <boost/preprocessor/empty.hpp>

#define BOOST_NO_UNDERLYING_TYPE
#define BOOST_ENUMS_USE_CONSTRUCTORS 1


#if 0
      BOOST_PP_IF(CONS,                             \
        BOOST_ENUMS_DETAIL_CONSTRUCTORS(EC, UT),    \
        BOOST_PP_EMPTY                            \
      )()                                             \
      BOOST_PP_IF(CONV,                             \
        BOOST_ENUMS_DETAIL_CONVERSIONS(EC, UT),     \
        BOOST_PP_EMPTY                              \
      )()                                             \

#endif

#ifndef BOOST_NO_SCOPED_ENUMS

  #ifdef BOOST_NO_UNDERLYING_TYPE

    #define BOOST_ENUMS_DETAIL_UNDERLYING_TYPE_SPEC(EC, UT)  \
      namespace boost {                               \
        namespace enums {                             \
          template <>                                 \
          struct underlying_type<EC>                  \
          {                                           \
            typedef UT type;                          \
          };                                          \
        }                                             \
      }

  #else // BOOST_NO_UNDERLYING_TYPE

    #define BOOST_ENUMS_DETAIL_UNDERLYING_TYPE_SPEC(EC, UT)

  #endif // BOOST_NO_UNDERLYING_TYPE

  #define BOOST_ENUM_CLASS_START(EC, UT)            \
    enum class EC : UT

  #define BOOST_ENUM_TYPE_START(EC, UT)             \
    enum EC : UT

  #define BOOST_ENUM_CLASS_END(EC, UT)              \
    ;                                               \
    BOOST_ENUMS_DETAIL_UNDERLYING_TYPE_SPEC(EC, UT)

  #define BOOST_ENUM_TYPE_END(EC, UT)               \
    ;                                               \
    BOOST_ENUMS_DETAIL_UNDERLYING_TYPE_SPEC(EC, UT)

  #define BOOST_ENUM_CLASS_CONS_END(EC, UT)              \
    ;                                               \
    BOOST_ENUMS_DETAIL_UNDERLYING_TYPE_SPEC(EC, UT)

  #define BOOST_ENUM_TYPE_CONS_END(EC, UT)               \
    ;                                               \
    BOOST_ENUMS_DETAIL_UNDERLYING_TYPE_SPEC(EC, UT)

#else // BOOST_NO_SCOPED_ENUMS

  #define BOOST_ENUMS_DETAIL_CONSTRUCTORS(EC, UT)   \
    EC() : val_()  {  }                             \
    EC(type v) : val_(v)  {  }

  #define BOOST_ENUMS_DETAIL_CONSTRUCTORS_AUX()    \
    BOOST_ENUMS_DETAIL_CONSTRUCTORS(EC, UT)

  #define BOOST_ENUMS_DETAIL_CONVERSIONS(EC, UT)    \
    operator UT() { return val_; }

  #define BOOST_ENUMS_DETAIL_CONVERSIONS_AUX()    \
    BOOST_ENUMS_DETAIL_CONVERSIONS(EC, UT)

  #define BOOST_ENUM_CLASS_START(EC, UT)            \
    class EC                                        \
    {                                               \
    public:                                         \
      enum type

  #define BOOST_ENUM_TYPE_START(EC, UT)             \
    class EC                                        \
    {                                               \
    public:                                         \
      enum type

  #define BOOST_ENUMS_END_1(EC, UT)                 \
      ;                                             \
      typedef UT underlying_type;                   \
    private:                                        \
      underlying_type val_;                         \
    public:


  #define BOOST_ENUMS_END_2(EC, UT)                 \
      EC& operator =(type rhs) {                    \
        val_=rhs;                                   \
        return *this;                               \
      }                                             \
      static EC default_value()                     \
      {                                             \
        EC res;                                     \
        res.val_=EnumClass::type();                 \
        return res;                                 \
      }                                             \
      static EC convert_to(underlying_type v)       \
      {                                             \
        EC res;                                     \
        res.val_=v;                                 \
        return res;                                 \
      }                                             \
      static EC convert_to(type v)                  \
      {                                             \
        EC res;                                     \
        res.val_=v;                                 \
        return res;                                 \
      }                                             \
      type get() const                              \
      {                                             \
        return type(val_);                          \
      }                                             \
      friend bool operator ==(EC lhs, EC rhs) {     \
        return lhs.get()==rhs.get();                \
      }                                             \
      friend bool operator ==(type lhs, EC rhs) {   \
        return lhs==rhs.get();                      \
      }                                             \
      friend bool operator ==(EC lhs, type rhs) {   \
        return lhs.get()==rhs;                      \
      }                                             \
      friend bool operator !=(EC lhs, EC rhs) {     \
        return lhs.get()!=rhs.get();                \
      }                                             \
      friend bool operator !=(EC lhs, type rhs) {   \
        return lhs.get()!=rhs;                      \
      }                                             \
      friend bool operator !=(type lhs, EC rhs) {   \
        return lhs!=rhs.get();                      \
      }                                             \
    };                                              \


  #define BOOST_ENUM_CLASS_END(EC, UT)              \
    BOOST_ENUMS_END_1(EC, UT)                       \
    BOOST_ENUMS_END_2(EC, UT)                       \

  #define BOOST_ENUM_TYPE_END(EC, UT)               \
    BOOST_ENUMS_END_1(EC, UT)                       \
    BOOST_ENUMS_DETAIL_CONVERSIONS(EC, UT)          \
    BOOST_ENUMS_END_2(EC, UT)                       \

  #define BOOST_ENUM_CLASS_CONS_END(EC, UT)         \
    BOOST_ENUMS_END_1(EC, UT)                       \
    BOOST_ENUMS_DETAIL_CONSTRUCTORS(EC, UT)         \
    BOOST_ENUMS_END_2(EC, UT)                       \

  #define BOOST_ENUM_TYPE_CONS_END(EC, UT)          \
    BOOST_ENUMS_END_1(EC, UT)                       \
    BOOST_ENUMS_DETAIL_CONSTRUCTORS(EC, UT)         \
    BOOST_ENUMS_DETAIL_CONVERSIONS(EC, UT)          \
    BOOST_ENUMS_END_2(EC, UT)                       \

#endif // BOOST_NO_SCOPED_ENUMS
#endif
