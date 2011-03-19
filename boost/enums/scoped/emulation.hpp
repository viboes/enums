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

#ifndef BOOST_ENUMS_SCOPED_EMULATION_HPP
#define BOOST_ENUMS_SCOPED_EMULATION_HPP

#include <boost/enums/scoped/underlying_type.hpp>
#include <boost/enums/scoped/native_type.hpp>
#include <boost/enums/scoped/scoping_type.hpp>
#include <boost/enums/scoped/default_value.hpp>
#include <boost/enums/scoped/native_value.hpp>
#include <boost/enums/scoped/underlying_value.hpp>
#include <boost/enums/scoped/is_enum.hpp>
#include <boost/conversion/convert_to.hpp>
#include <boost/preprocessor/if.hpp>
#include <boost/preprocessor/empty.hpp>
#include <boost/preprocessor.hpp>
#include <boost/enums/config.hpp>

#ifndef BOOST_ENUMS_DOXYGEN_INVOKED

// macro to get the namespace par of a sequence (NS1) ... (NSn) (ENUM)
// returns (NS1) ... (NSn)

#define BOOST_ENUMS_DETAIL_NAMESPACE_SEQ(SEQ) \
  BOOST_PP_SEQ_POP_BACK(SEQ)


// macro to get the namespace par of a sequence (NS1) ... (NSn) (ENUM)
// returns ENUM

#define BOOST_ENUMS_DETAIL_ENUM(SEQ) \
  BOOST_PP_SEQ_ELEM(BOOST_PP_DEC(BOOST_PP_SEQ_SIZE(SEQ)), SEQ)

// macro to generate the following code from a sequence (NS1) ... (NSn)
// namespace NS1 {
// ...
// namespace NSn {

#define BOOST_ENUMS_DETAIL_NAMESPACE_OPEN_(r, data, elem) namespace elem {

#define BOOST_ENUMS_DETAIL_NAMESPACE_OPEN(SEQ) \
  BOOST_PP_SEQ_FOR_EACH(BOOST_ENUMS_DETAIL_NAMESPACE_OPEN_, ~, SEQ)


// macro to generate the following code from a sequence (NS1) ... (NSn)
// }
// ...
// }

#define BOOST_ENUMS_DETAIL_NAMESPACE_CLOSE_(r, data, elem) }
#define BOOST_ENUMS_DETAIL_NAMESPACE_CLOSE(SEQ) \
  BOOST_PP_SEQ_FOR_EACH(BOOST_ENUMS_DETAIL_NAMESPACE_CLOSE_, ~, SEQ)

// macro to generate the following code from a sequence (NS1) ... (NSn)
// NS1::...NSn::

#define BOOST_ENUMS_DETAIL_NAMESPACE_(r, data, elem) elem ::
#define BOOST_ENUMS_DETAIL_NAMESPACE(SEQ) \
BOOST_PP_SEQ_FOR_EACH(BOOST_ENUMS_DETAIL_NAMESPACE_, ~, SEQ)

#define BOOST_ENUMS_DETAIL_CLASS(SEQ) \
  BOOST_ENUMS_DETAIL_NAMESPACE(BOOST_ENUMS_DETAIL_NAMESPACE_SEQ(SEQ)) BOOST_ENUMS_DETAIL_ENUM(SEQ)


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
        return lhs.native_value() OP rhs.native_value();                        \
      }                                                                     \
      friend inline BOOST_CONSTEXPR bool operator OP(type lhs, EC rhs) {    \
        return lhs OP rhs.native_value();                                     \
      }                                                                     \
      friend inline BOOST_CONSTEXPR bool operator OP(EC lhs, type rhs) {    \
        return lhs.native_value() OP rhs;                                     \
      }

#endif // BOOST_NO_SCOPED_ENUMS

#if !defined(BOOST_NO_SCOPED_ENUMS) && ! defined(BOOST_NO_SCOPED_ENUMS_COMPARE)

 #define BOOST_ENUMS_DETAIL_COMPARAISON_OPERATORS(EC, UT)

#else // !defined(BOOST_NO_SCOPED_ENUMS) && ! defined(BOOST_NO_SCOPED_ENUMS_COMPARE)

 #define BOOST_ENUMS_DETAIL_COMPARAISON_OPERATORS(EC, UT)   \
      BOOST_ENUMS_DETAIL_BINARY_OPERATOR(EC, UT, ==)        \
      BOOST_ENUMS_DETAIL_BINARY_OPERATOR(EC, UT, !=)        \
      BOOST_ENUMS_DETAIL_BINARY_OPERATOR(EC, UT, <)         \
      BOOST_ENUMS_DETAIL_BINARY_OPERATOR(EC, UT, <=)        \
      BOOST_ENUMS_DETAIL_BINARY_OPERATOR(EC, UT, >)         \
      BOOST_ENUMS_DETAIL_BINARY_OPERATOR(EC, UT, >=)

#endif // !defined(BOOST_NO_SCOPED_ENUMS) && ! defined(BOOST_NO_SCOPED_ENUMS_COMPARE)

  #define BOOST_ENUMS_DETAIL_SCOPING_TYPE_SPEC(EC)            \
      namespace boost {                                       \
        namespace enums {                                     \
          template <>                                         \
          struct scoping_type<native_type<EC>::type>          \
          {                                                   \
            typedef EC type;                                  \
          };                                                  \
        }                                                     \
      }

  #define BOOST_ENUMS_DETAIL_IS_ENUM_TYPE_SPEC(EC)            \
      namespace boost {                                       \
        namespace enums {                                     \
          template <>                                         \
          struct is_enum<EC> : mpl::true_                     \
          {                                                   \
          };                                                  \
        }                                                     \
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
    inline EC convert_to(boost::enums::native_type<EC>::type  v                 \
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
  inline friend EC convert_to(boost::enums::native_type<EC>::type  v          \
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
  inline friend boost::enums::native_type<EC>::type convert_to(EC v           \
    , boost::dummy::type_tag<boost::enums::native_type<EC>::type> const&      \
  )                                                                         \
  {                                                                         \
    return boost::enums::native_value(v);                                     \
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
  type native_value() const                               \
  {                                                     \
    return type(val_);                                  \
  }                                                     \
  underlying_type underlying_value() const              \
  {                                                     \
    return val_;                                        \
  }                                                     \
  BOOST_ENUMS_DETAIL_FRIEND_CONVERSIONS(EC, UT)


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
    BOOST_ENUMS_DETAIL_COMPARAISON_OPERATORS(EC, UT)        \
  };                                                      


  #define BOOST_ENUM_TYPE_END(EC, UT)                       \
    BOOST_ENUMS_DETAIL_END_1(EC, UT)                        \
    BOOST_ENUMS_DETAIL_CONVERSIONS(EC, UT)                  \
    BOOST_ENUMS_DETAIL_END_2(EC, UT)                        \
  };                                                      

  #define BOOST_ENUM_CLASS_NO_CONS_END(EC, UT)              \
    BOOST_ENUMS_DETAIL_END_1(EC, UT)                        \
    BOOST_ENUMS_DETAIL_END_2(EC, UT)                        \
    BOOST_ENUMS_DETAIL_COMPARAISON_OPERATORS(EC, UT)        \
  };                                                      

  #define BOOST_ENUM_TYPE_NO_CONS_END(EC, UT)               \
    BOOST_ENUMS_DETAIL_END_1(EC, UT)                        \
    BOOST_ENUMS_DETAIL_CONVERSIONS(EC, UT)                  \
    BOOST_ENUMS_DETAIL_END_2(EC, UT)                        \
  };

  #define BOOST_ENUM_CLASS_CONS_END(EC, UT)                 \
    BOOST_ENUMS_DETAIL_END_1(EC, UT)                        \
    BOOST_ENUMS_DETAIL_CONSTRUCTORS(EC, UT)                 \
    BOOST_ENUMS_DETAIL_END_2(EC, UT)                        \
    BOOST_ENUMS_DETAIL_COMPARAISON_OPERATORS(EC, UT)        \
  };                                                      

  #define BOOST_ENUM_TYPE_CONS_END(EC, UT)                  \
    BOOST_ENUMS_DETAIL_END_1(EC, UT)                        \
    BOOST_ENUMS_DETAIL_CONSTRUCTORS(EC, UT)                 \
    BOOST_ENUMS_DETAIL_CONVERSIONS(EC, UT)                  \
    BOOST_ENUMS_DETAIL_END_2(EC, UT)                        \
  };                                                      

#define BOOST_ENUMS_SPECIALIZATIONS(EC, UT)   \
    BOOST_ENUMS_DETAIL_SCOPING_TYPE_SPEC(EC)  \
    BOOST_ENUMS_DETAIL_IS_ENUM_TYPE_SPEC(EC)

#define BOOST_ENUM_NS_CLASS_START(NS_EC, UT)                \
  BOOST_ENUMS_DETAIL_NAMESPACE_OPEN(BOOST_ENUMS_DETAIL_NAMESPACE_SEQ(NS_EC)) \
  BOOST_ENUM_CLASS_START(BOOST_ENUMS_DETAIL_ENUM(NS_EC), UT)

#define BOOST_ENUM_NS_TYPE_START(NS_EC, UT)                 \
  BOOST_ENUMS_DETAIL_NAMESPACE_OPEN(BOOST_ENUMS_DETAIL_NAMESPACE_SEQ(NS_EC)) \
  BOOST_ENUM_TYPE_START(BOOST_ENUMS_DETAIL_ENUM(NS_EC), UT)

#define BOOST_ENUM_NS_CLASS_END(NS_EC, UT)                     \
  BOOST_ENUM_CLASS_END(BOOST_ENUMS_DETAIL_ENUM(NS_EC), UT)  \
  BOOST_ENUMS_DETAIL_NAMESPACE_CLOSE(BOOST_ENUMS_DETAIL_NAMESPACE_SEQ(NS_EC)) \
  BOOST_ENUMS_SPECIALIZATIONS(BOOST_ENUMS_DETAIL_CLASS(NS_EC), UT)


#define BOOST_ENUM_NS_TYPE_END(NS_EC, UT)                       \
  BOOST_ENUM_TYPE_END(BOOST_ENUMS_DETAIL_ENUM(NS_EC), UT)  \
  BOOST_ENUMS_DETAIL_NAMESPACE_CLOSE(BOOST_ENUMS_DETAIL_NAMESPACE_SEQ(NS_EC)) \
  BOOST_ENUMS_SPECIALIZATIONS(BOOST_ENUMS_DETAIL_CLASS(NS_EC), UT)

#define BOOST_ENUM_NS_CLASS_NO_CONS_END(NS_EC, UT)              \
  BOOST_ENUM_CLASS_NO_CONS_END(BOOST_ENUMS_DETAIL_ENUM(NS_EC), UT)  \
  BOOST_ENUMS_DETAIL_NAMESPACE_CLOSE(BOOST_ENUMS_DETAIL_NAMESPACE_SEQ(NS_EC)) \
  BOOST_ENUMS_SPECIALIZATIONS(BOOST_ENUMS_DETAIL_CLASS(NS_EC), UT)

#define BOOST_ENUM_NS_TYPE_NO_CONS_END(NS_EC, UT)               \
  BOOST_ENUM_TYPE_NO_CONS_END(BOOST_ENUMS_DETAIL_ENUM(NS_EC), UT)  \
  BOOST_ENUMS_DETAIL_NAMESPACE_CLOSE(BOOST_ENUMS_DETAIL_NAMESPACE_SEQ(NS_EC)) \
  BOOST_ENUMS_SPECIALIZATIONS(BOOST_ENUMS_DETAIL_CLASS(NS_EC), UT)

#define BOOST_ENUM_NS_CLASS_CONS_END(NS_EC, UT)                 \
  BOOST_ENUM_CLASS_CONS_END(BOOST_ENUMS_DETAIL_ENUM(NS_EC), UT)  \
  BOOST_ENUMS_DETAIL_NAMESPACE_CLOSE(BOOST_ENUMS_DETAIL_NAMESPACE_SEQ(NS_EC)) \
  BOOST_ENUMS_SPECIALIZATIONS(BOOST_ENUMS_DETAIL_CLASS(NS_EC), UT)

#define BOOST_ENUM_NS_TYPE_CONS_END(NS_EC, UT)                  \
  BOOST_ENUM_TYPE_CONS_END(BOOST_ENUMS_DETAIL_ENUM(NS_EC), UT)  \
  BOOST_ENUMS_DETAIL_NAMESPACE_CLOSE(BOOST_ENUMS_DETAIL_NAMESPACE_SEQ(NS_EC)) \
  BOOST_ENUMS_SPECIALIZATIONS(BOOST_ENUMS_DETAIL_CLASS(NS_EC), UT)


#endif // BOOST_ENUMS_SCOPED_EMULATION_HPP
#endif
