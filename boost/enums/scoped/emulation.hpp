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

#include <boost/enums/config.hpp>

#include <boost/enums/scoped/underlying_type.hpp>
#include <boost/enums/scoped/native_type.hpp>
#include <boost/enums/scoped/scoping_type.hpp>
#include <boost/enums/scoped/default_value.hpp>
#include <boost/enums/scoped/native_value.hpp>
#include <boost/enums/scoped/underlying_value.hpp>
#include <boost/enums/scoped/is_enum.hpp>
#ifndef BOOST_ENUMS_NOT_DEPENDS_ON_CONVERSION
#include <boost/conversion/explicit_convert_to.hpp>
#endif
#include <boost/enums/pp/namespaces.hpp>
//#include <cstring>

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
        return lhs.native_value() OP rhs.native_value();                    \
      }                                                                     \
      friend inline BOOST_CONSTEXPR bool operator OP(type lhs, EC rhs) {    \
        return lhs OP rhs.native_value();                                   \
      }                                                                     \
      friend inline BOOST_CONSTEXPR bool operator OP(EC lhs, type rhs) {    \
        return lhs.native_value() OP rhs;                                   \
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
          namespace meta {                                    \
            template <>                                       \
            struct scoping_type<native_type<EC>::type>        \
            {                                                 \
              typedef EC type;                                \
            };                                                \
          }                                                   \
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
          namespace meta {                                    \
            template <>                                       \
            struct underlying_type<EC>                        \
            {                                                 \
              typedef UT type;                                \
            };                                                \
          }                                                   \
        }                                                     \
      }

  #else // BOOST_NO_UNDERLYING_TYPE

    #define BOOST_ENUMS_DETAIL_UNDERLYING_TYPE_SPEC(EC, UT)

  #endif // BOOST_NO_UNDERLYING_TYPE


  #define BOOST_ENUMS_DETAIL_FRIEND_CONVERSIONS(EC, UT)                       \
    inline EC explicit_convert_to(UT v                                                 \
      , boost::conversion::dummy::type_tag<EC> const&                                     \
    )                                                                         \
    {                                                                         \
      return EC(v);                                                           \
    }                                                                         \
    inline EC explicit_convert_to(boost::enums::native_type<EC>::type  v                 \
      , boost::conversion::dummy::type_tag<EC> const&                                     \
    )                                                                         \
    {                                                                         \
      return v;                                                               \
    }                                                                         \
    inline UT explicit_convert_to(EC v                                                 \
      , boost::conversion::dummy::type_tag<UT> const&                                     \
    )                                                                         \
    {                                                                         \
      return boost::enums::underlying_value(v);                               \
    }

  #define BOOST_ENUMS_DETAIL_CONVERSIONS_SPECIALIZATIONS(EC, UT)              \
    namespace boost {                                                         \
      namespace conversion {                                                  \
        template <>                                                           \
        struct explicit_converter_cp<EC,UT> : true_type {                     \
          EC operator()(UT const &v) {                                        \
            return EC(v);                                                     \
          }                                                                   \
        };                                                                    \
        template <>                                                           \
        struct explicit_converter_cp<UT,EC> : true_type {                     \
          UT operator()(EC const &v) {                                        \
            return boost::enums::underlying_value(v);                         \
          }                                                                   \
        };                                                                    \
        template <>                                                           \
        struct explicit_converter_cp<EC,boost::enums::native_type<EC>::type>  \
          : true_type {                                                       \
          EC operator()(boost::enums::native_type<EC>::type const &v) {       \
            return v;                                                         \
          }                                                                   \
        };                                                                    \
      }                                                                       \
    }                                                                         \

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
  inline EC explicit_convert_to(UT v                                          \
    , boost::conversion::dummy::type_tag<EC> const&                                     \
  )                                                                         \
  {                                                                         \
    return EC::explicit_convert_to(v);                                               \
  }                                                                         \
  inline  EC explicit_convert_to(boost::enums::native_type<EC>::type  v          \
    , boost::conversion::dummy::type_tag<EC> const&                                     \
  )                                                                         \
  {                                                                         \
    return EC::explicit_convert_to(v);                                               \
  }                                                                         \
  inline  UT explicit_convert_to(EC v                                          \
    , boost::conversion::dummy::type_tag<UT> const&                                     \
  )                                                                         \
  {                                                                         \
    return boost::enums::underlying_value(v);                               \
  }                                                                         \
  inline  boost::enums::native_type<EC>::type explicit_convert_to(EC v           \
    , boost::conversion::dummy::type_tag<boost::enums::native_type<EC>::type> const&      \
  )                                                                         \
  {                                                                         \
    return boost::enums::native_value(v);                                     \
  }

  #define BOOST_ENUMS_DETAIL_CONVERSIONS_SPECIALIZATIONS(EC, UT)              \
    namespace boost {                                                         \
      namespace conversion {                                                  \
        template <>                                                           \
        struct explicit_converter_cp<EC,UT> : true_type {                     \
          EC operator()(UT const &v) {                                        \
            return EC::explicit_convert_to(v);                                \
          }                                                                   \
        };                                                                    \
        template <>                                                           \
        struct explicit_converter_cp<UT,EC> : true_type {                     \
          UT operator()(EC const &v) {                                        \
            return boost::enums::underlying_value(v);                         \
          }                                                                   \
        };                                                                    \
        template <>                                                           \
        struct explicit_converter_cp<EC,boost::enums::native_type<EC>::type>  \
          : true_type {                                                       \
          EC operator()(boost::enums::native_type<EC>::type const &v) {       \
            return EC::explicit_convert_to(v);                                \
          }                                                                   \
        };                                                                    \
        template <>                                                           \
        struct explicit_converter_cp<boost::enums::native_type<EC>::type, EC> \
          : true_type {                                                       \
          boost::enums::native_type<EC>::type operator()(EC const &v) {       \
            return boost::enums::native_value(v);                             \
          }                                                                   \
        };                                                                    \
      }                                                                       \
    }                                                                         \

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
  static EC explicit_convert_to(underlying_type v)               \
  {                                                     \
    EC res;                                             \
    res.val_=v;                                         \
    return res;                                         \
  }                                                     \
  static EC explicit_convert_to(type v)                          \
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
  }


  //BOOST_ENUMS_DETAIL_FRIEND_CONVERSIONS(EC, UT)


#endif
#endif

#ifndef BOOST_NO_SCOPED_ENUMS

  #define BOOST_ENUM_CLASS_START(EC, UT)            \
    enum class EC : UT

  #define BOOST_ENUM_TYPE_START(EC, UT)             \
    enum EC : UT

  #define BOOST_ENUM_CLASS_END(EC, UT)              \
    ;                                               \
    BOOST_ENUMS_DETAIL_COMPARAISON_OPERATORS(EC, UT)

  #define BOOST_ENUM_TYPE_END(EC, UT)               \
    ;                                               \
    BOOST_ENUMS_DETAIL_COMPARAISON_OPERATORS(EC, UT)

  #define BOOST_ENUM_CLASS_NO_CONS_END(EC, UT)      \
    ;                                               \
    BOOST_ENUMS_DETAIL_COMPARAISON_OPERATORS(EC, UT)

  #define BOOST_ENUM_TYPE_NO_CONS_END(EC, UT)       \
    ;                                               \
    BOOST_ENUMS_DETAIL_COMPARAISON_OPERATORS(EC, UT)

  #define BOOST_ENUM_CLASS_CONS_END(EC, UT)         \
    ;                                               \
    BOOST_ENUMS_DETAIL_COMPARAISON_OPERATORS(EC, UT)

  #define BOOST_ENUM_TYPE_CONS_END(EC, UT)          \
    ;                                               \
    BOOST_ENUMS_DETAIL_COMPARAISON_OPERATORS(EC, UT)

  #define BOOST_ENUMS_SPECIALIZATIONS(EC, UT)       \
    BOOST_ENUMS_DETAIL_UNDERLYING_TYPE_SPEC(EC, UT)

#ifndef BOOST_ENUMS_NOT_DEPENDS_ON_CONVERSION
  #define BOOST_ENUMS_OUT(NS_EC, UT)       \
  BOOST_ENUMS_SPECIALIZATIONS(BOOST_ENUMS_NAMESPACES_CLASS_QNAME(NS_EC), UT) \
  BOOST_ENUMS_DETAIL_CONVERSIONS_SPECIALIZATIONS(BOOST_ENUMS_NAMESPACES_CLASS_QNAME(NS_EC),UT)
#else
  #define BOOST_ENUMS_OUT(NS_EC, UT)       \
  BOOST_ENUMS_SPECIALIZATIONS(BOOST_ENUMS_NAMESPACES_CLASS_QNAME(NS_EC), UT)
#endif
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

#ifndef BOOST_ENUMS_NOT_DEPENDS_ON_CONVERSION
  #define BOOST_ENUMS_OUT(NS_EC, UT)       \
  BOOST_ENUMS_SPECIALIZATIONS(BOOST_ENUMS_NAMESPACES_CLASS_QNAME(NS_EC), UT) \
  BOOST_ENUMS_DETAIL_CONVERSIONS_SPECIALIZATIONS(BOOST_ENUMS_NAMESPACES_CLASS_QNAME(NS_EC),UT)
#else
  #define BOOST_ENUMS_OUT(NS_EC, UT)       \
  BOOST_ENUMS_SPECIALIZATIONS(BOOST_ENUMS_NAMESPACES_CLASS_QNAME(NS_EC), UT)
#endif

#endif
#define BOOST_ENUM_NS_CLASS_START(QNAME, UT)                \
  BOOST_ENUMS_QNAME_OPEN(QNAME) \
  BOOST_ENUM_CLASS_START(BOOST_ENUMS_QNAME_NAME(QNAME), UT)

#define BOOST_ENUM_NS_TYPE_START(QNAME, UT)                 \
  BOOST_ENUMS_QNAME_OPEN(QNAME) \
  BOOST_ENUM_TYPE_START(BOOST_ENUMS_QNAME_NAME(QNAME), UT)

#define BOOST_ENUM_NS_CLASS_END(QNAME, UT)                     \
  BOOST_ENUM_CLASS_END(BOOST_ENUMS_QNAME_NAME(QNAME), UT)  \
  BOOST_ENUMS_QNAME_CLOSE(QNAME) \
  BOOST_ENUMS_OUT(QNAME, UT)


#define BOOST_ENUM_NS_TYPE_END(QNAME, UT)                       \
  BOOST_ENUM_TYPE_END(BOOST_ENUMS_QNAME_NAME(QNAME), UT)  \
  BOOST_ENUMS_QNAME_CLOSE(QNAME) \
  BOOST_ENUMS_OUT(QNAME, UT)

#define BOOST_ENUM_NS_CLASS_NO_CONS_END(QNAME, UT)              \
  BOOST_ENUM_CLASS_NO_CONS_END(BOOST_ENUMS_QNAME_NAME(QNAME), UT)  \
  BOOST_ENUMS_QNAME_CLOSE(QNAME) \
  BOOST_ENUMS_OUT(QNAME, UT)

#define BOOST_ENUM_NS_TYPE_NO_CONS_END(NS_EC, UT)               \
  BOOST_ENUM_TYPE_NO_CONS_END(BOOST_ENUMS_QNAME_NAME(QNAME), UT)  \
  BOOST_ENUMS_QNAME_CLOSE(QNAME) \
  BOOST_ENUMS_OUT(QNAME, UT)

#define BOOST_ENUM_NS_CLASS_CONS_END(QNAME, UT)                 \
  BOOST_ENUM_CLASS_CONS_END(BOOST_ENUMS_QNAME_NAME(QNAME), UT)  \
  BOOST_ENUMS_QNAME_CLOSE(QNAME) \
  BOOST_ENUMS_OUT(QNAME, UT)

#define BOOST_ENUM_NS_TYPE_CONS_END(QNAME, UT)                  \
  BOOST_ENUM_TYPE_CONS_END(BOOST_ENUMS_QNAME_NAME(QNAME), UT)  \
  BOOST_ENUMS_QNAME_CLOSE(QNAME) \
  BOOST_ENUMS_OUT(QNAME, UT)

#endif // BOOST_ENUMS_SCOPED_EMULATION_HPP
