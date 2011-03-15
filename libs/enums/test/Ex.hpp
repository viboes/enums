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


#include <boost/enums/emulation.hpp>
#include <boost/enums/size.hpp>
#include <boost/enums/pos.hpp>
#include <boost/enums/val.hpp>
#include <boost/enums/enum_traits.hpp>
#include <boost/enums/enum_traiter.hpp>
#include <cstddef>
#include <boost/enums/enum_class_cons.hpp>

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
      BOOST_STATIC_CONSTEXPR boost::enums::enum_type<EC3>::type value = EC3::Enum0;
    };
    template <>
    struct val<EC3, 1>
    {
      BOOST_STATIC_CONSTEXPR boost::enums::enum_type<EC3>::type value = EC3::Enum1;
    };
    template <>
    struct val<EC3, 2>
    {
      BOOST_STATIC_CONSTEXPR boost::enums::enum_type<EC3>::type value = EC3::Enum2;
    };
    template <>
    struct enum_traits<EC3> : linear_enum_traiter<EC3>
    {
    };
    } // namespace meta
  }
}

#endif
