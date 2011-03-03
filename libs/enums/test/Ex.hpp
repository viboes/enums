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

  BOOST_ENUM_CLASS_START(EC3, int) {
    Enum0,
    Enum1,
    Enum2
  } BOOST_ENUM_CLASS_CONS_END(EC3, int)

namespace boost {
  namespace enums {
    namespace meta {

    template <>
    struct size<EC3>
    {
      static const int value = 3;
    }; 
    template <>
    struct pos<EC3, EC3::Enum0>
    {
      static const std::size_t value = 0;
    }; 
    template <>
    struct pos<EC3, EC3::Enum1>
    {
      static const std::size_t value = 1;
    }; 
    template <>
    struct pos<EC3, EC3::Enum2>
    {
      static const std::size_t value = 2;
    }; 

    template <>
    struct val<EC3, 0>
    {
      static const boost::enums::enum_type<EC3>::type value = EC3::Enum0;
    }; 
    template <>
    struct val<EC3, 1>
    {
      static const boost::enums::enum_type<EC3>::type value = EC3::Enum1;
    }; 
    template <>
    struct val<EC3, 2>
    {
      static const boost::enums::enum_type<EC3>::type value = EC3::Enum2;
    }; 
    } // namespace meta
    template <>
    struct enum_traits<EC3> : enum_traiter<EC3> 
    {
      static std::size_t pos(EC3 e) 
      {
        switch (boost::enums::get_value(e)) 
        {
          case EC3::Enum0: return 0;
          case EC3::Enum1:   return 1;
          case EC3::Enum2:   return 2;
          default:                 throw "bad_parameter";
        }
      }
      static EC3 val(std::size_t p) 
      {
        switch (p) 
        {
          case 0: return boost::convert_to<EC3>(EC3::Enum0);
          case 1: return boost::convert_to<EC3>(EC3::Enum1);
          case 2: return boost::convert_to<EC3>(EC3::Enum2);
          default: throw "bad_parameter";
        }
      }
    }; 
  }
}

#endif
