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
 The header \c <boost/enums/ordinal/traits.hpp> declares a class template 
 \c meta::enum_traits<> which must be specialized for each enumeration including two static functions \c pos() and \c val().
 */

#ifndef BOOST_ENUMS_ORDINAL_TRAITS_HPP
#define BOOST_ENUMS_ORDINAL_TRAITS_HPP

namespace boost 
{
  namespace enums 
  {
    namespace meta 
    {
      template <typename EC>
#ifndef BOOST_ENUMS_DOXYGEN_INVOKED
        struct enum_traits;
#else
        struct enum_traits
        {   
            //! The specialization must define this function prototype
            static std::size_t pos(EC e);
            //! The specialization must define this function prototype
            static EC val(std::size_t p);
        };    
#endif        

    }
  }
}

#endif // BOOST_ENUMS_ORDINAL_TRAITS_HPP
