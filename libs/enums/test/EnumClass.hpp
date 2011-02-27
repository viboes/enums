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
#include <boost/enums/enum_value.hpp>
#include <boost/enums/enum_type.hpp>
#include <boost/enums/default_value.hpp>
#include <boost/enums/get_value.hpp>
#include <boost/conversion/convert_to.hpp>
#include <boost/enums/emulation.hpp>
#include <cassert>
#include <cstring>
#include <string>

#define CTOR

//! This macro will be expanded to
//~ #if defined(BOOST_ENUM_CLASS_START)
#if 1
  BOOST_ENUM_CLASS_START(EnumClass, unsigned char) {
    Default = 0,
    Enum1,
    Enum2
  } BOOST_ENUM_CLASS_CONS_END(EnumClass, unsigned char)

#else // defined(BOOST_ENUM_CLASS_START)
  #if !defined(BOOST_NO_SCOPED_ENUMS)
enum class EnumClass : unsigned char
{
  Default = 0,
  Enum1,
  Enum2
}
;

namespace boost {
  namespace enums {
    template <>
    struct underlying_type<EnumClass>
    {
      typedef unsigned char type;
    };
  }}
#else // !defined(BOOST_NO_SCOPED_ENUMS)

class EnumClass {
public:
  //! nested C++98 enumeration class
  enum   type
  {
    Default = 0,
    Enum1,
    Enum2
  };
  typedef unsigned char underlying_type;
private:
  //! stored value with underlying type
  underlying_type Val;

public:
  //!  static helper conversion from the default enum.
  static EnumClass default_value()
  {
    EnumClass res;
    res.Val=EnumClass::type();
    return res;
  }

  //!  static helper conversion from the underlying enum. Used when constructors can not be used.
  static EnumClass convert_to(type v)
  {
    EnumClass res;
    res.Val=v;
    return res;
  }

  //!  static helper conversion from the underlying int.
  static EnumClass convert_to(underlying_type v)
  {
    EnumClass res;
    res.Val=v;
    return res;
  }

#ifdef CTOR
  //! default constructor :: Default
  EnumClass()  : Val()
  {
  }

  EnumClass(type v) : Val(v)
  {
  }
#endif // CTOR

  EnumClass& operator =(type rhs) {
    Val=rhs;
    return *this;
  }

  type get() const
  {
    return type(Val);
  }

  friend bool operator ==(EnumClass lhs, EnumClass rhs) {
    return lhs.get()==rhs.get();
  }

  friend bool operator ==(type lhs, EnumClass rhs) {
    return lhs==rhs.get();
  }

  friend bool operator ==(EnumClass lhs, type rhs) {
    return lhs.get()==rhs;
  }

  friend bool operator !=(EnumClass lhs, EnumClass rhs) {
    return lhs.get()!=rhs.get();
  }

  friend bool operator !=(EnumClass lhs, type rhs) {
    return lhs.get()!=rhs;
  }

  friend bool operator !=(type lhs, EnumClass rhs) {
    return lhs!=rhs.get();
  }

};


#endif // !defined(BOOST_NO_SCOPED_ENUMS)
#endif // defined(BOOST_ENUM_CLASS_START)

//!  conversion from the underlying int.
inline EnumClass convert_to(boost::enums::underlying_type<EnumClass>::type v
//~ inline EnumClass convert_to(unsigned int v
  , boost::dummy::type_tag<EnumClass> const&
)
{
#ifdef BOOST_NO_SCOPED_ENUMS
  return EnumClass::convert_to(v);
#else
  return EnumClass(v);
#endif
}

//!  conversion from the underlying int.
inline EnumClass convert_to(boost::enums::enum_type<EnumClass>::type  v
  , boost::dummy::type_tag<EnumClass> const&
)
{
#ifdef BOOST_NO_SCOPED_ENUMS
  return EnumClass::convert_to(v);
#else
  return EnumClass(v);
#endif
}



//!  conversion from c-string.
inline EnumClass convert_to(const char* str
  , boost::dummy::type_tag<EnumClass> const&
)
{
    if (strcmp(str, "Default") ==0)  { return boost::convert_to<EnumClass>(EnumClass::Default); }
    if (strcmp(str, "Enum1") ==0)    { return  boost::convert_to<EnumClass>(EnumClass::Enum1); }
    if (strcmp(str, "Enum2") ==0)  { return  boost::convert_to<EnumClass>(EnumClass::Enum2); }
    assert(false && "invalid string for ArqType");
}

//!  conversion from std::string.
inline EnumClass convert_to(const std::string& str
  , boost::dummy::type_tag<EnumClass> const&
)
{
    return boost::convert_to<EnumClass>(str.c_str());
}

//! explicit conversion to c-string.
inline const char* c_str(EnumClass e)
{
    switch (boost::enums::get_value(e))
    {
    case BOOST_ENUM_VALUE(EnumClass::Default) : return("EnumClass::Default");
    case BOOST_ENUM_VALUE(EnumClass::Enum1):    return("EnumClass::Enum1");
    case BOOST_ENUM_VALUE(EnumClass::Enum2) :   return("EnumClass::Enum2");
    default:
      return("EnumClass::???");
    }
}

//! OSTRREAM overloading
template <typename OSTREAM>
inline OSTREAM& operator <<(OSTREAM& os, EnumClass v) {
  os << c_str(v);
  return os;
}

#endif
