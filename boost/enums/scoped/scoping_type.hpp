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
 The header \c <boost/enums/scoped/scoping_type.hpp> defines the declaration of scoping_type<> meta-function.
 */

#ifndef BOOST_ENUMS_SCOPED_SCOPING_TYPE_HPP
#define BOOST_ENUMS_SCOPED_SCOPING_TYPE_HPP

#include <boost/config.hpp>

namespace boost
{
  namespace enums
  {
    namespace meta
    {
      /*! meta-function to be specialized for each emulated enum class.
       */
      template <typename EC_type>
      struct scoping_type
      {
        //! By default this metafunction defines it as if scoped enums where supported.
        typedef EC_type type;
      };    
    }
    /*! Get the wrapping class of an enum when emulation
     is used or the enum class itself when available.
     
     @note This meta-function must be specialized for each enum class.
     */
    template <typename EC_type>
    struct scoping_type
    {
      //! Depending on whethere the compiler supports scoped enums or not the nested type must be the same type or the emulated one. 
      typedef typename meta::scoping_type<EC_type>::type type;
    };    
  }
}

#endif // BOOST_ENUMS_SCOPED_SCOPING_TYPE_HPP
