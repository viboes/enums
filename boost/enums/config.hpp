//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 2011,2012.
// Distributed under the Boost
// Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or
// copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/enums for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_ENUMS_CONFIG_HPP
#define BOOST_ENUMS_CONFIG_HPP

#include <boost/config.hpp>

#define BOOST_NO_UNDERLYING_TYPE

#ifndef BOOST_NO_SCOPED_ENUMS
  #if defined(__GNUC__) &&  (__GNUC__ < 4 || ( __GNUC__ == 4 && __GNUC_MINOR__ < 5 ) || ( __GNUC__ == 4 && __GNUC_MINOR__ == 5 && __GNUC_PATCHLEVEL__ < 1))
    #define BOOST_NO_SCOPED_ENUMS_COMPARE
  #else
  #endif
#else
#endif

#if defined __clang__

#if !__has_feature(cxx_unrestricted_unions)
#  define BOOST_NO_UNRESTRICTED_UNION
#endif

#elif defined __GNUC__

  #if defined __GXX_EXPERIMENTAL_CXX0X__
    #if ((__GNUC__ < 4) || (__GNUC__ == 4 && __GNUC_MINOR__ < 6))
      #define BOOST_NO_UNRESTRICTED_UNION
    #endif
  #else
    #define BOOST_NO_UNRESTRICTED_UNION
  #endif

#else

  #define BOOST_NO_UNRESTRICTED_UNION

#endif

#if __cplusplus > 201402L
#define BOOST_ENUMS_CXX14_MUTABLE_CONSTEXPR BOOST_CONSTEXPR
#else
#define BOOST_ENUMS_CXX14_MUTABLE_CONSTEXPR
#endif

#endif // BOOST_ENUMS_CONFIG_HPP
