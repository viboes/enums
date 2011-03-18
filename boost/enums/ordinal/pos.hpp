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
 The header \c <boost/enums/pos.hpp> declares a class template \c meta::pos<> and 
 a function \c pos() associating the an element of an enumeration to
 its relative position.
 */

#ifndef BOOST_ENUMS_ORDINAL_POS_HPP
#define BOOST_ENUMS_ORDINAL_POS_HPP

#include <boost/enums/scoped/native_type.hpp>
#include <boost/enums/ordinal/traits.hpp>
#include <cstddef>


namespace boost
{
  namespace enums
  {
    namespace meta
    {
      //! meta-function used to associate the an element of an enumeration to
      //! its relative position.
        
      //! \note This meta-function must be specialized for each element of the enumeration.
      template <typename EC, typename native_type<EC>::type V>
#ifndef BOOST_ENUMS_DOXYGEN_INVOKED
        struct pos; 
#else
        struct pos
        {
            constexpr std::size_t value=<to be defined for each specialization>;
        };    
#endif
    }

      
    //! position of an enum literal \c e on the extension of the enumeration type \c EC.
      
    //! The \c enum_traits class must be specialized and contain a \c pos function
    //! that returns the relative position of its argument \c e.
      
    //! \param e the enum literal
    //! \returns the associated position
    //! \throws Nothing
    template <typename EC>
    std::size_t pos(EC e)
    {
      return meta::enum_traits<EC>::pos(e);
    }

  }
}

#endif // BOOST_ENUMS_ORDINAL_POS_HPP
