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


#include <boost/enums/scoped/underlying_type.hpp>
#include <boost/enums/scoped/native_type.hpp>
#include <boost/enums/scoped/default_value.hpp>
#include <boost/enums/scoped/native_value.hpp>
#include <boost/enums/ordinal/pos.hpp>
#include <boost/enums/ordinal/first.hpp>
#include <boost/enums/ordinal/last.hpp>
#include <boost/enums/ordinal/size.hpp>
#include <boost/enums/ordinal/traits.hpp>
#include <boost/conversion/convert_to.hpp>
#include <boost/enums/ordinal/linear_traiter.hpp>
#include <boost/enums/scoped/emulation.hpp>
#include <cassert>
#include <cstring>
#include <string>
#include <boost/enums/scoped/enum_class_cons.hpp>
#include <boost/enums/scoped/enum_class_no_cons.hpp>
#include <boost/enums/scoped/enum_type_cons.hpp>
#include <boost/enums/scoped/enum_type_no_cons.hpp>
#include <boost/enums/pp/enum_declaration.hpp>

#define CTOR
#if 0
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
    switch (boost::enums::native_value(e))
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
#else


BOOST_ENUMS_ENUM_CLASS_DCL_CONS((EnumClass), unsigned char,                  
                                ( (Default)(3) )
                                ( (Enum1)    )
                                ( (Enum2)    )
                                , linear_enum_traiter)




#endif


//! OSTRREAM overloading
template <typename OSTREAM>
inline OSTREAM& operator <<(OSTREAM& os, EnumClass v) {
  os << int(boost::enums::native_value(v));
  return os;
}

#endif
#if 0
class EnumClass { 
public: 
  enum type { Default = 3 , Enum1 , Enum2 }; 
  inline friend EnumClass convert_to( const char* str, boost::dummy::type_tag<EnumClass> const& ) 
  { 
    if (strcmp( str, "Default" ) == 0) { return boost::convert_to<EnumClass>( EnumClass::Default ); } 
    if (strcmp( str, "Enum1" ) == 0) { return boost::convert_to<EnumClass>( EnumClass::Enum1 ); } 
    if (strcmp( str, "Enum2" ) == 0) { return boost::convert_to<EnumClass>( EnumClass::Enum2 ); } 
    throw "invalid string for " "EnumClass"; 
  } 
  inline friend EnumClass convert_to( const std::string& str, boost::dummy::type_tag<EnumClass> const& ) 
  { 
    return boost::convert_to<EnumClass>( str.c_str() ); 
  } 
  inline friend const char* c_str(EnumClass e) 
  { 
    switch (boost::enums::native_value(e)) 
    { 
      case EnumClass::EnumClass::Default : return("Default"); 
      case EnumClass::EnumClass::Enum1 : return("Enum1"); 
      case EnumClass::EnumClass::Enum2 : return("Enum2"); 
      default: throw "invalid value for " "EnumClass"; 
    } 
  } 
  typedef EnumClass this_type ; 
  typedef int underlying_type; 
private: 
  underlying_type val_; 
public: 
  EnumClass() : val_(static_cast<underlying_type>(type())) { } 
  EnumClass(type v) : val_(static_cast<underlying_type>(v)) { } 
  explicit EnumClass(underlying_type v) : val_(v) { } 
  EnumClass& operator =(type rhs) { val_=static_cast<underlying_type>(rhs); return *this; } 
  static EnumClass default_value() { EnumClass res; res.val_=static_cast<underlying_type>(EnumClass::type()); return res; } 
  static EnumClass convert_to(underlying_type v) { EnumClass res; res.val_=v; return res; } 
  static EnumClass convert_to(type v) { EnumClass res; res.val_=static_cast<underlying_type>(v); return res; } 
  type native_value() const { return type(val_); } 
  underlying_type underlying_value() const { return val_; } 
  inline friend EnumClass convert_to(int v , boost::dummy::type_tag<EnumClass> const& ) { return EnumClass::convert_to(v); } 
  inline friend EnumClass convert_to(boost::enums::native_type<EnumClass>::type v , boost::dummy::type_tag<EnumClass> const& ) { return EnumClass::convert_to(v); } 
  inline friend int convert_to(EnumClass v , boost::dummy::type_tag<int> const& ) { return boost::enums::underlying_value(v); } 
  inline friend boost::enums::native_type<EnumClass>::type convert_to(EnumClass v , boost::dummy::type_tag<boost::enums::native_type<EnumClass>::type> const& ) { 
    return boost::enums::native_value(v); 
  } 
  friend inline bool operator ==(EnumClass lhs, EnumClass rhs) { return lhs.native_value() == rhs.native_value(); } 
  friend inline bool operator ==(type lhs, EnumClass rhs) { return lhs == rhs.native_value(); } 
  friend inline bool operator ==(EnumClass lhs, type rhs) { return lhs.native_value() == rhs; } 
  friend inline bool operator !=(EnumClass lhs, EnumClass rhs) { return lhs.native_value() != rhs.native_value(); } 
  friend inline bool operator !=(type lhs, EnumClass rhs) { return lhs != rhs.native_value(); } 
  friend inline bool operator !=(EnumClass lhs, type rhs) { return lhs.native_value() != rhs; } 
  friend inline bool operator <(EnumClass lhs, EnumClass rhs) { return lhs.native_value() < rhs.native_value(); } 
  friend inline bool operator <(type lhs, EnumClass rhs) { return lhs < rhs.native_value(); } 
  friend inline bool operator <(EnumClass lhs, type rhs) { return lhs.native_value() < rhs; } 
  friend inline bool operator <=(EnumClass lhs, EnumClass rhs) { return lhs.native_value() <= rhs.native_value(); } 
  friend inline bool operator <=(type lhs, EnumClass rhs) { return lhs <= rhs.native_value(); } 
  friend inline bool operator <=(EnumClass lhs, type rhs) { return lhs.native_value() <= rhs; } 
  friend inline bool operator >(EnumClass lhs, EnumClass rhs) { return lhs.native_value() > rhs.native_value(); } 
  friend inline bool operator >(type lhs, EnumClass rhs) { return lhs > rhs.native_value(); } 
  friend inline bool operator >(EnumClass lhs, type rhs) { return lhs.native_value() > rhs; } 
  friend inline bool operator >=(EnumClass lhs, EnumClass rhs) { return lhs.native_value() >= rhs.native_value(); } 
  friend inline bool operator >=(type lhs, EnumClass rhs) { return lhs >= rhs.native_value(); } 
  friend inline bool operator >=(EnumClass lhs, type rhs) { return lhs.native_value() >= rhs; } 
}; 
namespace boost { 
  namespace enums { 
    template <> struct scoping_type<native_type<EnumClass>::type> { typedef EnumClass type; }; 
  } 
} 
namespace boost { 
  namespace enums { 
    template <> struct is_enum<EnumClass> : mpl::true_ { }; 
  } 
} 
namespace boost { 
  namespace enums { 
    namespace meta { 
      template <> struct size< EnumClass> { 
        static const std::size_t value; 
      }; 
      const std::size_t size< EnumClass>::value = 3; 
      template <> struct pos<EnumClass, EnumClass :: Default> { static const std::size_t value = 2; }; 
      template <> struct val<EnumClass, 2> { static const boost::enums::native_type<EnumClass>::type value = EnumClass::Default; }; 
      template <> struct pos<EnumClass, EnumClass :: Enum1> { static const std::size_t value = 3; }; 
      template <> struct val<EnumClass, 3> { static const boost::enums::native_type<EnumClass>::type value = EnumClass::Enum1; }; 
      template <> struct pos<EnumClass, EnumClass :: Enum2> { static const std::size_t value = 4; }; 
      template <> struct val<EnumClass, 4> { static const boost::enums::native_type<EnumClass>::type value = EnumClass::Enum2; }; 
      template <> struct enum_traits< EnumClass> : linear_enum_traiter< EnumClass> {}; 
    } 
  } 
}
#endif
