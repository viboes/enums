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

#ifndef EX_HPP
#define EX_HPP


#include <boost/enums/scoped.hpp>
#include <boost/enums/ordinal.hpp>
#include <cstddef>
#include <boost/enums/pp/enum_declaration.hpp>

#if 1
BOOST_ENUMS_ENUM_CLASS_DCL_CONS((EC3), int,
                                ( (Enum0) )
                                ( (Enum1)    )
                                ( (Enum2)    )
                                , linear_enum_traiter)


//~ enum class EC3 : int { Enum0 , Enum1 , Enum2 } ;
//~ inline bool operator ==(EC3 lhs, EC3 rhs) { return (int)(lhs) == (int)(rhs); }
//~ inline bool operator !=(EC3 lhs, EC3 rhs) { return (int)(lhs) != (int)(rhs); }
//~ inline bool operator <(EC3 lhs, EC3 rhs) { return (int)(lhs) < (int)(rhs); }
//~ inline bool operator <=(EC3 lhs, EC3 rhs) { return (int)(lhs) <= (int)(rhs); }
//~ inline bool operator >(EC3 lhs, EC3 rhs) { return (int)(lhs) > (int)(rhs); }
//~ inline bool operator >=(EC3 lhs, EC3 rhs) { return (int)(lhs) >= (int)(rhs); }
//~ namespace boost { namespace enums { namespace meta {
  //~ template <> struct underlying_type<EC3> { typedef int type; };
  //~ } } }
  //~ inline EC3 convert_to(int v , boost::dummy::type_tag<EC3> const& ) { return EC3(v); }
  //~ inline EC3 convert_to(boost::enums::native_type<EC3>::type v , boost::dummy::type_tag<EC3> const& ) { return v; }
  //~ inline int convert_to(EC3 v , boost::dummy::type_tag<int> const& ) { return boost::enums::underlying_value(v); }
  //~ namespace boost { namespace enums { namespace meta {
    //~ template <> struct size< EC3> { static const std::size_t value=3; };
    //~ template <> struct pos<EC3, EC3 :: Enum0> { static const std::size_t value = 0; };
    //~ template <> struct val<EC3, 0> { static const boost::enums::native_type<EC3>::type value = EC3::Enum0; };
    //~ template <> struct pos<EC3, EC3 :: Enum1> { static const std::size_t value = 1; };
    //~ template <> struct val<EC3, 1> { static const boost::enums::native_type<EC3>::type value = EC3::Enum1; };
    //~ template <> struct pos<EC3, EC3 :: Enum2> { static const std::size_t value = 2; };
    //~ template <> struct val<EC3, 2> { static const boost::enums::native_type<EC3>::type value = EC3::Enum2; };
    //~ template <> struct enum_traits< EC3> : linear_enum_traiter< EC3> {};
      //~ } } }
    //~ inline EC3 convert_to( const char* str, boost::dummy::type_tag<EC3> const& ) { if (strcmp( str, "Enum0" ) == 0) { return boost::convert_to<EC3>( EC3::Enum0 ); } if (strcmp( str, "Enum1" ) == 0) { return boost::convert_to<EC3>( EC3::Enum1 ); } if (strcmp( str, "Enum2" ) == 0) { return boost::convert_to<EC3>( EC3::Enum2 ); } throw "invalid string for " "EC3"; }
      //~ inline EC3 convert_to( const std::string& str, boost::dummy::type_tag<EC3> const& ) { return boost::convert_to<EC3>( str.c_str() ); }
      //~ inline const char* c_str(EC3 e) {
        //~ switch (boost::enums::native_value(e)) { case EC3::Enum0 : return("Enum0"); case EC3::Enum1 : return("Enum1"); case EC3::Enum2 : return("Enum2"); default: throw "invalid value for " "EC3"; } }

#else
#if 0
  BOOST_ENUM_CLASS_START(EC3, int) {
    Enum0,
    Enum1,
    Enum2
  } BOOST_ENUM_CLASS_CONS_END(EC3, int)
#else

struct EC3NS {
  enum type {
    Enum0,
    Enum1,
    Enum2
  };
};
typedef  boost::enums::enum_class_cons<EC3NS, unsigned char> EC3;
#endif
BOOST_ENUMS_SPECIALIZATIONS(EC3, int)

namespace boost {
  namespace enums {
    namespace meta {

    template <>
    struct size<EC3>
    {
      //~ BOOST_STATIC_CONSTEXPR
      static const std::size_t value;
    };
    //~ BOOST_CONSTEXPR
    const std::size_t size<EC3>::value = 3;
    template <>
    struct pos<EC3, EC3::Enum0>
    {
      BOOST_STATIC_CONSTEXPR std::size_t value = 0;
    };
    template <>
    struct pos<EC3, EC3::Enum1>
    {
      BOOST_STATIC_CONSTEXPR std::size_t value = 1;
    };
    template <>
    struct pos<EC3, EC3::Enum2>
    {
      BOOST_STATIC_CONSTEXPR std::size_t value = 2;
    };

    template <>
    struct val<EC3, 0>
    {
      BOOST_STATIC_CONSTEXPR boost::enums::native_type<EC3>::type value = EC3::Enum0;
    };
    template <>
    struct val<EC3, 1>
    {
      BOOST_STATIC_CONSTEXPR boost::enums::native_type<EC3>::type value = EC3::Enum1;
    };
    template <>
    struct val<EC3, 2>
    {
      BOOST_STATIC_CONSTEXPR boost::enums::native_type<EC3>::type value = EC3::Enum2;
    };
    template <>
    struct enum_traits<EC3> : linear_enum_traiter<EC3>
    {
    };
    } // namespace meta
  }
}

#endif
#endif
