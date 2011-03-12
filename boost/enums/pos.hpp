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

#ifndef BOOST_ENUMS_POS_HPP
#define BOOST_ENUMS_POS_HPP

#include <boost/enums/enum_type.hpp>
#include <boost/enums/enum_traits.hpp>
#include <cstddef>


namespace boost
{
  namespace enums
  {
    namespace meta
    {
      //! meta-function used to associate the an element of an enumeration to
      //! its relative position.
      //! This meta-function must be specialized for each element of the enumeration.
      template <typename EC, typename enum_type<EC>::type V>
      struct pos; 
    }

    //! Returns: the associated position
    //! The enum_traits class must be specialized and contain a pos function
    //! that returns the relative position.
    //! Throws: Nothing
    template <typename EC>
    std::size_t pos(EC e)
    {
      return meta::enum_traits<EC>::pos(e);
    }

  }
}

#endif
