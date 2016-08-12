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

#ifndef ENUMTYPE_HPP
#define ENUMTYPE_HPP

#include <boost/enums/scoped/underlying_type.hpp>
#include <boost/enums/scoped/native_type.hpp>
#include <boost/enums/scoped/default_value.hpp>
#include <boost/enums/scoped/native_value.hpp>
#include <boost/enums/ordinal/pos.hpp>
#include <boost/enums/ordinal/first.hpp>
#include <boost/enums/ordinal/last.hpp>
#include <boost/enums/ordinal/size.hpp>
#include <boost/enums/ordinal/traits.hpp>
#ifndef BOOST_ENUMS_NOT_DEPENDS_ON_CONVERSION
#include <boost/conversion/explicit_convert_to.hpp>
#endif
#include <boost/enums/ordinal/linear_traiter.hpp>
#include <boost/enums/scoped/emulation.hpp>
#include <cassert>
#include <cstring>
#include <string>
#include <boost/enums/pp/enum_declaration.hpp>


#define CTOR

#if 1
BOOST_ENUMS_ENUM_TYPE_DCL_CONS((EnumClass), unsigned char,
                                ( (Default)(3) )
                                ( (Enum1)    )
                                ( (Enum2)    )
                                , linear_enum_traiter)
#else
#if 1

BOOST_ENUM_TYPE_START(EnumClass, unsigned char) {
  Default = 3,
  Enum1,
  Enum2
} BOOST_ENUM_TYPE_CONS_END(EnumClass, unsigned char)
#else

struct EnumClassNS {
  enum type {
    Default = 3,
    Enum1,
    Enum2
  };
};
typedef  boost::enums::enum_type_cons<EnumClassNS, unsigned char> EnumClass;

#endif
BOOST_ENUMS_SPECIALIZATIONS(EnumClass, unsigned char)

//!  conversion from c-string.
inline EnumClass explicit_convert_to(const char* str
  , boost::conversion::dummy::type_tag<EnumClass> const&
)
{
    if (strcmp(str, "Default") ==0)  { return boost::conversion::explicit_convert_to<EnumClass>(EnumClass::Default); }
    if (strcmp(str, "Enum1") ==0)    { return  boost::conversion::explicit_convert_to<EnumClass>(EnumClass::Enum1); }
    if (strcmp(str, "Enum2") ==0)  { return  boost::conversion::explicit_convert_to<EnumClass>(EnumClass::Enum2); }
    throw "invalid string for EnumClass";
}

//!  conversion from std::string.
inline EnumClass explicit_convert_to(const std::string& str
  , boost::conversion::dummy::type_tag<EnumClass> const&
)
{
    return boost::conversion::explicit_convert_to<EnumClass>(str.c_str());
}

//!explicit conversion to c-string.
inline const char* c_str(EnumClass e)
{
    switch (boost::enums::native_value(e))
    {
    case EnumClass::Default : return("EnumClass::Default");
    case EnumClass::Enum1:    return("EnumClass::Enum1");
    case EnumClass::Enum2 :   return("EnumClass::Enum2");
    default:
      return("EnumClass::???");
    }
}

#error
namespace boost {
  namespace enums {
    namespace meta {

    template <>
    struct size<EnumClass>
    {
      BOOST_STATIC_CONSTEXPR std::size_t value = 3;
    };
    template <>
    struct pos<EnumClass, EnumClass::Default>
    {
      BOOST_STATIC_CONSTEXPR std::size_t value = 0;
    };
    template <>
    struct pos<EnumClass, EnumClass::Enum1>
    {
      BOOST_STATIC_CONSTEXPR std::size_t value = 1;
    };
    template <>
    struct pos<EnumClass, EnumClass::Enum2>
    {
      BOOST_STATIC_CONSTEXPR std::size_t value = 2;
    };

    template <>
    struct val<EnumClass, 0>
    {
      BOOST_STATIC_CONSTEXPR boost::enums::native_type<EnumClass>::type value = EnumClass::Default;
    };
    template <>
    struct val<EnumClass, 1>
    {
      BOOST_STATIC_CONSTEXPR boost::enums::native_type<EnumClass>::type value = EnumClass::Enum1;
    };
    template <>
    struct val<EnumClass, 2>
    {
      BOOST_STATIC_CONSTEXPR boost::enums::native_type<EnumClass>::type value = EnumClass::Enum2;
    };
    template <>
    struct enum_traits<EnumClass>
    : linear_enum_traiter<EnumClass>
    {
    };
    } // namespace meta
  }
}

#endif

//! OSTRREAM overloading
template <typename OSTREAM>
inline OSTREAM& operator <<(OSTREAM& os, EnumClass v) {
  os << int(boost::enums::native_value(v));
  return os;
}

#endif
