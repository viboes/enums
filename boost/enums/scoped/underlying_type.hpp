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

#ifndef BOOST_ENUMS_SCOPED_UNDERLYING_TYPE_HPP
#define BOOST_ENUMS_SCOPED_UNDERLYING_TYPE_HPP

#include <boost/enums/config.hpp>
#ifndef BOOST_NO_UNDERLYING_TYPE
  #include <type_traits>
#endif

namespace boost
{
  namespace enums
  {
    namespace meta
    {
      //! customization-point for underlying type metafunction
           
      //! <b>Requires</b> \c EC must be an enum type or the emulation of a scoped enum.\n\n
      template <typename EC>
      struct underlying_type
      {
#ifdef BOOST_ENUMS_DOXYGEN_INVOKED
        //! The member typedef \c type name the underlying type of \c T. 
        //! When scoped enums are emulated it is defined as \c typename \c EC::underlying_type. 
        //! Otherwise is defined as \c std::underlying_type<EC>::type.
        //! This meta-function must be specialized for the compilers providing scoped enums
        //! but don't providing the \c std::underlying_type meta-function.
        typedef see_below type;
#else
#ifdef BOOST_NO_SCOPED_ENUMS
        typedef typename EC::underlying_type type;
#else
#ifndef BOOST_NO_UNDERLYING_TYPE
        typedef typename std::underlying_type<EC>::type type;
#endif
#endif
#endif
      };
    }    
    //! underlying type metafunction
       
    //! <b>Requires</b> \c EC must be an enum type or the emulation of a scoped enum.\n\n
    template <typename EC>
    struct underlying_type
    {
#ifdef BOOST_ENUMS_DOXYGEN_INVOKED
      //! The member typedef \c type names the underlying type of \c T. 
      //! It is defined as \c meta::underlying_type<EC>::type which could need specialization.
      //! @see boost::enums::meta::underlying_type
      typedef see_below type;
#else
      typedef typename meta::underlying_type<EC>::type type;
#endif
    };
  }
}

#endif // BOOST_ENUMS_SCOPED_UNDERLYING_TYPE_HPP
