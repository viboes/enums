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

#ifndef BOOST_ENUMS_SCOPED_DEFAULT_VALUE_HPP
#define BOOST_ENUMS_SCOPED_DEFAULT_VALUE_HPP

#include <boost/config.hpp>

namespace boost {
  namespace enums {

    //!  builds a enum class with the default value.
    
    //! This function is usefult to make programs portable when the scoped enum 
    //! emulation doesn't defines a default constructor.
    //! @TParams
    //! @Param{EC,the scoped enum type}
    
    //! @Returns the default value as if the default constructor of @c EC was defined.
    //! @NoThrow
    //! @Note The use of @c EC() will let the underlying storage uninitialized when constructors are not defined by the emulation.
    template <typename EC>
    inline EC default_value()
    {
#ifdef BOOST_NO_SCOPED_ENUMS
      return EC::default_value();
#else
      return EC();
#endif
    }

  }
}

#endif // BOOST_ENUMS_SCOPED_DEFAULT_VALUE_HPP
