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

#ifndef BOOST_ENUMS_ORDINAL_LINEAR_TRAITER_HPP
#define BOOST_ENUMS_ORDINAL_LINEAR_TRAITER_HPP

#include <boost/enums/scoped/native_type.hpp>
#include <boost/enums/ordinal/size.hpp>
#include <boost/enums/ordinal/val.hpp>
#include <boost/enums/ordinal/pos.hpp>
#include <boost/enums/ordinal/first.hpp>
#include <boost/enums/ordinal/last.hpp>
#ifndef BOOST_ENUMS_NOT_DEPENDS_ON_CONVERSION
#include <boost/conversion/explicit_convert_to.hpp>
#endif
/*!
 @file
 @brief
 The header \c <boost/enums/linear_enum_traiter.hpp> declares a class template
 \c meta::linear_enum_traiter<> which can be used as \c enum_trait<> helper for enumerations having a linear progression.
 */

namespace boost {
  namespace enums {

    //! Helper class used as \c enum_trait<> for enumerations having a linear progression.
    template <
      typename EC
    >
    struct linear_enum_traiter
    {
    private:
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
      //! pos specialization.

      //! @Rreturns the returned value is calculated from the underlying value,
      //! the \c first_value and the \c step, following this formula \c (ut-first_value)/step
      BOOST_STATIC_CONSTEXPR std::size_t pos(EC e)
      {
//        typename underlying_type<EC>::type uv = underlying_value(e);
//        return (uv-first_value)/step;
        return (underlying_value(e)-first_value)/step;

      }
        //! val specialization.

        //! @Returns the returned value is calculated from the position \c p,
        //! the first value and the step, following this formula \c p*step+first_value
      BOOST_STATIC_CONSTEXPR EC val(std::size_t p)
      {
//        typename underlying_type<EC>::type uv = p*step+first_value;
//        return EC(uv);
        return EC((typename underlying_type<EC>::type)(p*step+first_value));

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
//        return (native_value(e));
//      }
//      static EC val(std::size_t i)
//      {
//        typename underlying_type<EC>::type ut = 1<<i;
//        return EC(ut);
//      }
//    };
  }
}

#endif // BOOST_ENUMS_ORDINAL_LINEAR_TRAITER_HPP
