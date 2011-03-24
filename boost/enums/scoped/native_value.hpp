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

#ifndef BOOST_ENUMS_SCOPED_NATIVE_VALUE_HPP
#define BOOST_ENUMS_SCOPED_NATIVE_VALUE_HPP

#include <boost/config.hpp>
#include <boost/enums/scoped/native_type.hpp>

namespace boost {
  namespace enums {

    //!  gets the native enum value.
    
    //! This function is useful to make programs portable when the scoped enum 
    //! emulation can not be use where native enums can.
    //! @TParams
    //! @Param{EC,the scoped enum type}
    
    //! @Params
    //! @Param{e,the scoped enum}
    //! @Returns the native enum value.
    //! @NoThrow
    template <typename EC>
    inline
    typename native_type<EC>::type native_value(EC e)
    {
#ifdef BOOST_NO_SCOPED_ENUMS
      return e.native_value();
#else
      return e;
#endif
    }
  }
}

#endif // BOOST_ENUMS_SCOPED_NATIVE_VALUE_HPP
