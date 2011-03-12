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

    template <
      typename EC
    >
    struct linear_enum_traiter
    {
    protected:
      BOOST_STATIC_CONSTEXPR typename underlying_type<EC>::type first_value =
          static_cast<typename underlying_type<EC>::type>(
              enums::meta::val<EC,0>::value
          );
      BOOST_STATIC_CONSTEXPR typename underlying_type<EC>::type last_value =
          static_cast<typename underlying_type<EC>::type>(
              enums::meta::val<EC,meta::size<EC>::value-1>::value
          );
      BOOST_STATIC_CONSTEXPR std::size_t step = (last_value-first_value)/(meta::size<EC>::value-1);
    public:
      static std::size_t pos(EC e)
      {
        typename underlying_type<EC>::type ut = static_cast<typename underlying_type<EC>::type>(get_value(e));
        return (ut-first_value)/step;
      }
      static EC val(std::size_t i)
      {
        typename underlying_type<EC>::type ut = i*step+first_value;
        return boost::convert_to<EC>(ut);
      }
    };

//    template <
//      typename EC
//    >
//    struct log2_enum_traiter
//    {
//    public:
//      static std::size_t pos(EC e)
//      {
//        return (get_value(e));
//      }
//      static EC val(std::size_t i)
//      {
//        typename underlying_type<EC>::type ut = 1<<i;
//        return boost::convert_to<EC>(ut);
//      }
//    };
  }
}

#endif
