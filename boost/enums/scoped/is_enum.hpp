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

/*!
 \file
 \brief
 This header defines the is_enum meta-function that replace std::is_enum when we want to take care of the scoped enum emulation.
 */

#ifndef BOOST_ENUMS_SCOPED_IS_ENUM_HPP
#define BOOST_ENUMS_SCOPED_IS_ENUM_HPP

#include <boost/config.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/type_traits/is_enum.hpp>

namespace boost
{
  namespace enums
  {
    /*! meta-function configuring emulated enums.
     */
    template <typename T>
      struct is_emulated_enum : mpl::false_
      {
        //! the result of this meta-function is false by default.
        //! is_emulated_enum must be specialized for each emulated enum.
      };

    /*! meta-function checking if his parameter is a built-in or emulated enum, that is can be used as an emulated enum.
     */
    template <typename T>
	  struct is_enum
#ifdef BOOST_ENUMS_DOXYGEN_INVOKED
      //! The member \c value states whether \c T can be used as an enum.
      //! When scoped enums are not supported it is defined as \c std::is_enum<T>::value or \c is_emulated_enum<T>::value.
      //! Otherwise is defined as \c std::is_enum<T>::value.
      : bool_type
#else
  #ifdef BOOST_NO_SCOPED_ENUMS
      : mpl::or_<boost::is_enum<T>, is_emulated_enum<T> >
  #else
      : boost::is_enum<T>
  #endif
#endif
    {

	  };
  }
}

#endif // BOOST_ENUMS_SCOPED_IS_ENUM_HPP
