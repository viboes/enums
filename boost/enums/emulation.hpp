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
#include <boost/enums/emulator_type.hpp>
#include <boost/enums/default_value.hpp>
#include <boost/enums/enum_value.hpp>
#include <boost/enums/underlying_value.hpp>
#include <boost/conversion/convert_to.hpp>
#include <boost/preprocessor/if.hpp>
#include <boost/preprocessor/empty.hpp>
#include <boost/enums/config.hpp>

#ifndef BOOST_ENUMS_DOXYGEN_INVOKED

#ifndef BOOST_NO_SCOPED_ENUMS
    #define BOOST_ENUMS_DETAIL_BINARY_OPERATOR(EC, UT, OP)          \
      inline BOOST_CONSTEXPR bool operator OP(EC lhs, EC rhs) {     \
        return (UT)(lhs)                                            \
        OP                                                          \
        (UT)(rhs);                                                  \
      }

#else // BOOST_NO_SCOPED_ENUMS

  #define BOOST_ENUMS_DETAIL_BINARY_OPERATOR(EC, UT, OP)                    \
      friend inline BOOST_CONSTEXPR bool operator OP(EC lhs, EC rhs) {      \
        return lhs.enum_value() OP rhs.enum_value();                        \
      }                                                                     \
      friend inline BOOST_CONSTEXPR bool operator OP(type lhs, EC rhs) {    \
        return lhs OP rhs.enum_value();                                     \
      }                                                                     \
      friend inline BOOST_CONSTEXPR bool operator OP(EC lhs, type rhs) {    \
        return lhs.enum_value() OP rhs;                                     \
      }

#endif // BOOST_NO_SCOPED_ENUMS

#if !defined(BOOST_NO_SCOPED_ENUMS) && ! defined(BOOST_NO_SCOPED_ENUMS_COMPARE)

 #define BOOST_ENUMS_DETAIL_COMPARAISON_OPERATORS(EC, UT)

#else // !defined(BOOST_NO_SCOPED_ENUMS) && ! defined(BOOST_NO_SCOPED_ENUMS_COMPARE)

 #define BOOST_ENUMS_DETAIL_COMPARAISON_OPERATORS(EC, UT)  \
      BOOST_ENUMS_DETAIL_BINARY_OPERATOR(EC, UT, ==)      \
      BOOST_ENUMS_DETAIL_BINARY_OPERATOR(EC, UT, !=)      \
      BOOST_ENUMS_DETAIL_BINARY_OPERATOR(EC, UT, <)       \
      BOOST_ENUMS_DETAIL_BINARY_OPERATOR(EC, UT, <=)      \
      BOOST_ENUMS_DETAIL_BINARY_OPERATOR(EC, UT, >)       \
      BOOST_ENUMS_DETAIL_BINARY_OPERATOR(EC, UT, >=)

#endif // !defined(BOOST_NO_SCOPED_ENUMS) && ! defined(BOOST_NO_SCOPED_ENUMS_COMPARE)

  #define BOOST_ENUMS_DETAIL_EMULATOR_TYPE_SPEC(EC)   \
      namespace boost {                               \
        namespace enums {                             \
          template <>                                 \
          struct emulator_type<enum_type<EC>::type>   \
          {                                           \
            typedef EC type;                          \
          };                                          \
        }                                             \
      }

#ifndef BOOST_NO_SCOPED_ENUMS

  #ifdef BOOST_NO_UNDERLYING_TYPE

    #define BOOST_ENUMS_DETAIL_UNDERLYING_TYPE_SPEC(EC, UT)   \
      namespace boost {                                       \
        namespace enums {                                     \
          template <>                                         \
          struct underlying_type<EC>                          \
          {                                                   \
            typedef UT type;                                  \
          };                                                  \
        }                                                     \
      }

  #else // BOOST_NO_UNDERLYING_TYPE

    #define BOOST_ENUMS_DETAIL_UNDERLYING_TYPE_SPEC(EC, UT)

  #endif // BOOST_NO_UNDERLYING_TYPE


  #define BOOST_ENUMS_DETAIL_FRIEND_CONVERSIONS(EC, UT)                       \
    inline EC convert_to(UT v                                                 \
      , boost::dummy::type_tag<EC> const&                                     \
    )                                                                         \
    {                                                                         \
      return EC(v);                                                           \
    }                                                                         \
    inline EC convert_to(boost::enums::enum_type<EC>::type  v                 \
      , boost::dummy::type_tag<EC> const&                                     \
    )                                                                         \
    {                                                                         \
      return v;                                                               \
    }                                                                         \
    inline UT convert_to(EC v                                                 \
      , boost::dummy::type_tag<UT> const&                                     \
    )                                                                         \
    {                                                                         \
      return boost::enums::underlying_value(v);                               \
    }
#else

#define BOOST_ENUMS_DETAIL_CONSTRUCTORS(EC, UT)             \
  EC() : val_(static_cast<underlying_type>(type()))  {  }   \
  EC(type v) : val_(static_cast<underlying_type>(v))  {  }  \
  explicit EC(underlying_type v) : val_(v)  {  }


#define BOOST_ENUMS_DETAIL_CONVERSIONS(EC, UT)    \
  operator underlying_type() { return val_; }     \
  operator type() { return type(val_); }


#define BOOST_ENUMS_DETAIL_END_1(EC, UT)          \
    ;                                             \
    typedef UT underlying_type;                   \
  private:                                        \
    underlying_type val_;                         \
  public:



#define BOOST_ENUMS_DETAIL_FRIEND_CONVERSIONS(EC, UT)                       \
  inline friend EC convert_to(UT v                                          \
    , boost::dummy::type_tag<EC> const&                                     \
  )                                                                         \
  {                                                                         \
    return EC::convert_to(v);                                               \
  }                                                                         \
  inline friend EC convert_to(boost::enums::enum_type<EC>::type  v          \
    , boost::dummy::type_tag<EC> const&                                     \
  )                                                                         \
  {                                                                         \
    return EC::convert_to(v);                                               \
  }                                                                         \
  inline friend UT convert_to(EC v                                          \
    , boost::dummy::type_tag<UT> const&                                     \
  )                                                                         \
  {                                                                         \
    return boost::enums::underlying_value(v);                               \
  }                                                                         \
  inline friend boost::enums::enum_type<EC>::type convert_to(EC v           \
    , boost::dummy::type_tag<boost::enums::enum_type<EC>::type> const&      \
  )                                                                         \
  {                                                                         \
    return boost::enums::enum_value(v);                                     \
  }


#define BOOST_ENUMS_DETAIL_END_2(EC, UT)                  \
  EC& operator =(type rhs) {                            \
    val_=static_cast<underlying_type>(rhs);             \
    return *this;                                       \
  }                                                     \
  static EC default_value()                             \
  {                                                     \
    EC res;                                             \
    res.val_=static_cast<underlying_type>(EC::type());  \
    return res;                                         \
  }                                                     \
  static EC convert_to(underlying_type v)               \
  {                                                     \
    EC res;                                             \
    res.val_=v;                                         \
    return res;                                         \
  }                                                     \
  static EC convert_to(type v)                          \
  {                                                     \
    EC res;                                             \
    res.val_=static_cast<underlying_type>(v);           \
    return res;                                         \
  }                                                     \
  type enum_value() const                               \
  {                                                     \
    return type(val_);                                  \
  }                                                     \
  underlying_type underlying_value() const              \
  {                                                     \
    return val_;                                        \
  }                                                     \
  BOOST_ENUMS_DETAIL_COMPARAISON_OPERATORS(EC, UT)      \
  BOOST_ENUMS_DETAIL_FRIEND_CONVERSIONS(EC, UT)         \
};                                                      


#endif
#endif

#ifndef BOOST_NO_SCOPED_ENUMS

  #define BOOST_ENUM_CLASS_START(EC, UT)            \
    enum class EC : UT

  #define BOOST_ENUM_TYPE_START(EC, UT)             \
    enum EC : UT

  #define BOOST_ENUM_CLASS_END(EC, UT)              \
    ;                                               \
    BOOST_ENUMS_DETAIL_FRIEND_CONVERSIONS(EC, UT)   \
    BOOST_ENUMS_DETAIL_COMPARAISON_OPERATORS(EC, UT)

  #define BOOST_ENUM_TYPE_END(EC, UT)               \
    ;                                               \
    BOOST_ENUMS_DETAIL_FRIEND_CONVERSIONS(EC, UT)   \
    BOOST_ENUMS_DETAIL_COMPARAISON_OPERATORS(EC, UT)

  #define BOOST_ENUM_CLASS_NO_CONS_END(EC, UT)      \
    ;                                               \
    BOOST_ENUMS_DETAIL_FRIEND_CONVERSIONS(EC, UT)   \
    BOOST_ENUMS_DETAIL_COMPARAISON_OPERATORS(EC, UT)

  #define BOOST_ENUM_TYPE_NO_CONS_END(EC, UT)       \
    ;                                               \
    BOOST_ENUMS_DETAIL_FRIEND_CONVERSIONS(EC, UT)   \
    BOOST_ENUMS_DETAIL_COMPARAISON_OPERATORS(EC, UT)

  #define BOOST_ENUM_CLASS_CONS_END(EC, UT)         \
    ;                                               \
    BOOST_ENUMS_DETAIL_FRIEND_CONVERSIONS(EC, UT)   \
    BOOST_ENUMS_DETAIL_COMPARAISON_OPERATORS(EC, UT)

  #define BOOST_ENUM_TYPE_CONS_END(EC, UT)          \
    ;                                               \
    BOOST_ENUMS_DETAIL_FRIEND_CONVERSIONS(EC, UT)   \
    BOOST_ENUMS_DETAIL_COMPARAISON_OPERATORS(EC, UT)

  #define BOOST_ENUMS_SPECIALIZATIONS(EC, UT)       \
    BOOST_ENUMS_DETAIL_UNDERLYING_TYPE_SPEC(EC, UT)

#else // BOOST_NO_SCOPED_ENUMS

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


  #define BOOST_ENUM_CLASS_END(EC, UT)                      \
    BOOST_ENUMS_DETAIL_END_1(EC, UT)                        \
    BOOST_ENUMS_DETAIL_END_2(EC, UT)                        \

  #define BOOST_ENUM_TYPE_END(EC, UT)                       \
    BOOST_ENUMS_DETAIL_END_1(EC, UT)                        \
    BOOST_ENUMS_DETAIL_CONVERSIONS(EC, UT)                  \
    BOOST_ENUMS_DETAIL_END_2(EC, UT)                        \

  #define BOOST_ENUM_CLASS_NO_CONS_END(EC, UT)              \
    BOOST_ENUMS_DETAIL_END_1(EC, UT)                        \
    BOOST_ENUMS_DETAIL_END_2(EC, UT)                        \

  #define BOOST_ENUM_TYPE_NO_CONS_END(EC, UT)               \
    BOOST_ENUMS_DETAIL_END_1(EC, UT)                        \
    BOOST_ENUMS_DETAIL_CONVERSIONS(EC, UT)                  \
    BOOST_ENUMS_DETAIL_END_2(EC, UT)                        \

  #define BOOST_ENUM_CLASS_CONS_END(EC, UT)                 \
    BOOST_ENUMS_DETAIL_END_1(EC, UT)                        \
    BOOST_ENUMS_DETAIL_CONSTRUCTORS(EC, UT)                 \
    BOOST_ENUMS_DETAIL_END_2(EC, UT)                        \

  #define BOOST_ENUM_TYPE_CONS_END(EC, UT)                  \
    BOOST_ENUMS_DETAIL_END_1(EC, UT)                        \
    BOOST_ENUMS_DETAIL_CONSTRUCTORS(EC, UT)                 \
    BOOST_ENUMS_DETAIL_CONVERSIONS(EC, UT)                  \
    BOOST_ENUMS_DETAIL_END_2(EC, UT)                        \


#define BOOST_ENUMS_SPECIALIZATIONS(EC, UT) \
    BOOST_ENUMS_DETAIL_EMULATOR_TYPE_SPEC(EC)


#endif // BOOST_NO_SCOPED_ENUMS
#endif
