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
#include <boost/enums/get_value.hpp>
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

#define CTOR

//! This macro will be expanded to
//~ #if defined(BOOST_ENUM_CLASS_START)
#if 1
  BOOST_ENUM_CLASS_START(EnumClass, unsigned char) {
    Default = 3,
    Enum1,
    Enum2
  } BOOST_ENUM_CLASS_CONS_END(EnumClass, unsigned char)

#else // defined(BOOST_ENUM_CLASS_START)
  #if !defined(BOOST_NO_SCOPED_ENUMS)
enum class EnumClass : unsigned char
{
  Default = 3,
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
    Default = 3,
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
  EnumClass()  : Val(type())
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
//!  conversion from the underlying int.
inline EnumClass convert_to(boost::enums::underlying_type<EnumClass>::type v
  , boost::dummy::type_tag<EnumClass> const&
)
{
#ifdef BOOST_NO_SCOPED_ENUMS
  return EnumClass::convert_to(v);
#else
  return EnumClass(v);
#endif
}

//!  conversion from the native enum type.
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
#endif // defined(BOOST_ENUM_CLASS_START)

//!  conversion from c-string.
inline EnumClass convert_to(const char* str
  , boost::dummy::type_tag<EnumClass> const&
)
{
    if (strcmp(str, "Default") ==0)  { return boost::convert_to<EnumClass>(EnumClass::Default); }
    if (strcmp(str, "Enum1") ==0)    { return  boost::convert_to<EnumClass>(EnumClass::Enum1); }
    if (strcmp(str, "Enum2") ==0)  { return  boost::convert_to<EnumClass>(EnumClass::Enum2); }
    assert(false && "invalid string for EnumClass");
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
    switch (boost::enums::get_value(e))
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
      static const std::size_t value = 3;
    }; 
    template <>
    struct pos<EnumClass, EnumClass::Default>
    {
      static const std::size_t value = 0;
    }; 
    template <>
    struct pos<EnumClass, EnumClass::Enum1>
    {
      static const std::size_t value = 1;
    }; 
    template <>
    struct pos<EnumClass, EnumClass::Enum2>
    {
      static const std::size_t value = 2;
    }; 

    template <>
    struct val<EnumClass, 0>
    {
      static const boost::enums::enum_type<EnumClass>::type value = EnumClass::Default;
    }; 
    template <>
    struct val<EnumClass, 1>
    {
      static const boost::enums::enum_type<EnumClass>::type value = EnumClass::Enum1;
    }; 
    template <>
    struct val<EnumClass, 2>
    {
      static const boost::enums::enum_type<EnumClass>::type value = EnumClass::Enum2;
    }; 
    } // namespace meta
    template <>
    struct enum_traits<EnumClass> : enum_traiter<EnumClass> 
    {
      static std::size_t pos(EnumClass e) 
      {
        switch (boost::enums::get_value(e)) 
        {
          case EnumClass::Default: return 0;
          case EnumClass::Enum1:   return 1;
          case EnumClass::Enum2:   return 2;
          default:                 throw "bad_parameterparameter";
        }
      }
      static EnumClass val(std::size_t p) 
      {
        switch (p) 
        {
          case 0: return boost::convert_to<EnumClass>(EnumClass::Default);
          case 1: return boost::convert_to<EnumClass>(EnumClass::Enum1);
          case 2: return boost::convert_to<EnumClass>(EnumClass::Enum2);
          default: throw "bad_parameter";
        }
      }
    }; 
  }
}



//! OSTRREAM overloading
template <typename OSTREAM>
inline OSTREAM& operator <<(OSTREAM& os, EnumClass v) {
  os << int(boost::enums::get_value(v));
  return os;
}

#endif
