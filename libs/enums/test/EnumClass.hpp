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

#ifndef ENUMCLASS_HPP
#define ENUMCLASS_HPP


#include <boost/enums/underlying_type.hpp>
#include <boost/enums/enum_type.hpp>
#include <boost/enums/default_value.hpp>
#include <boost/enums/enum_value.hpp>
#include <boost/enums/pos.hpp>
#include <boost/enums/first.hpp>
#include <boost/enums/last.hpp>
#include <boost/enums/size.hpp>
#include <boost/enums/enum_traits.hpp>
#include <boost/conversion/convert_to.hpp>
#include <boost/enums/enum_traiter.hpp>
#include <boost/enums/emulation.hpp>
#include <cassert>
#include <cstring>
#include <string>
#include <boost/enums/enum_class_cons.hpp>
#include <boost/enums/enum_class_no_cons.hpp>
#include <boost/enums/enum_type_cons.hpp>
#include <boost/enums/enum_type_no_cons.hpp>

#define CTOR
#if 0

BOOST_ENUM_CLASS_START(EnumClass, unsigned char) {
  Default = 3,
  Enum1,
  Enum2
} BOOST_ENUM_CLASS_CONS_END(EnumClass, unsigned char)
#else

struct EnumClassNS {
  enum type {
    Default = 3,
    Enum1,
    Enum2
  };
}; 
typedef  boost::enums::enum_class_cons<EnumClassNS, unsigned char> EnumClass;

#endif
BOOST_ENUMS_SPECIALIZATIONS(EnumClass, unsigned char)

//!  conversion from c-string.
inline EnumClass convert_to(const char* str
  , boost::dummy::type_tag<EnumClass> const&
)
{
    if (strcmp(str, "Default") ==0)  { return boost::convert_to<EnumClass>(EnumClass::Default); }
    if (strcmp(str, "Enum1") ==0)    { return  boost::convert_to<EnumClass>(EnumClass::Enum1); }
    if (strcmp(str, "Enum2") ==0)  { return  boost::convert_to<EnumClass>(EnumClass::Enum2); }
    throw "invalid string for EnumClass";
}

//!  conversion from std::string.
inline EnumClass convert_to(const std::string& str
  , boost::dummy::type_tag<EnumClass> const&
)
{
    return boost::convert_to<EnumClass>(str.c_str());
}

//!explicit conversion to c-string.
inline const char* c_str(EnumClass e)
{
    switch (boost::enums::enum_value(e))
    {
    case EnumClass::Default : return("EnumClass::Default");
    case EnumClass::Enum1:    return("EnumClass::Enum1");
    case EnumClass::Enum2 :   return("EnumClass::Enum2");
    default:
      return("EnumClass::???");
    }
}

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
      BOOST_STATIC_CONSTEXPR boost::enums::enum_type<EnumClass>::type value = EnumClass::Default;
    };
    template <>
    struct val<EnumClass, 1>
    {
      BOOST_STATIC_CONSTEXPR boost::enums::enum_type<EnumClass>::type value = EnumClass::Enum1;
    };
    template <>
    struct val<EnumClass, 2>
    {
      BOOST_STATIC_CONSTEXPR boost::enums::enum_type<EnumClass>::type value = EnumClass::Enum2;
    };
    template <>
    struct enum_traits<EnumClass>
    : linear_enum_traiter<EnumClass>
    {
    };
    } // namespace meta
  }
}



//! OSTRREAM overloading
template <typename OSTREAM>
inline OSTREAM& operator <<(OSTREAM& os, EnumClass v) {
  os << int(boost::enums::enum_value(v));
  return os;
}

#endif
