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

#ifndef BOOST_ENUMS_ENUM_TRAITER_HPP
#define BOOST_ENUMS_ENUM_TRAITER_HPP

#include <boost/enums/enum_type.hpp>
#include <boost/enums/size.hpp>
#include <boost/enums/val.hpp>
#include <boost/enums/pos.hpp>
#include <boost/enums/first.hpp>
#include <boost/enums/last.hpp>
#include <boost/conversion/convert_to.hpp>

namespace boost {
  namespace enums {
    template <typename EC, 
        int Last=enums::meta::size<EC>::value-1,
        int First=0
        >
    struct enum_traiter
    {
      typedef EC enum_type;
      static const int first_index = First;
      static const int last_index = Last;
      static const int size = Last-First+1;

      static EC first() 
      {
        return boost::convert_to<EC>(enums::meta::val<EC,First>::value);
      }
      static EC last() 
      {
        return boost::convert_to<EC>(enums::meta::val<EC,Last>::value);
      }
      
    };     
    template <typename EC>
    struct linear_enum_traiter : enum_traiter<EC>
    {
    typedef enum_traiter<EC> base_type;
      static int pos(EC e) 
      {
        return (enums::get_value(e)-base_type::first_index);
      } 
      static EC val(int i) 
      {
        typename enums::underlying_type<EC>::type ut = i+base_type::first_index;
        return boost::convert_to<EC>(ut);
      }  
    };
  }
}

#endif
