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
 The header \c <boost/enums/size.hpp> declares a class template \c meta::size<> and 
 a function \c size() returning the number of elements in the enumeration.
 */

#ifndef BOOST_ENUMS_SIZE_HPP
#define BOOST_ENUMS_SIZE_HPP

#include <boost/enums/enum_type.hpp>


namespace boost {
  namespace enums {
    namespace meta {
		//! meta-function used to get the number of elements of an enumeration.
		
		//! \note This meta-function must be specialized for each enumeration.
		template <typename EC>
#ifndef BOOST_ENUMS_DOXYGEN_INVOKED
		struct size; 
#else
		struct size 
		{
			constexpr std::size_t value=<to be defined for each specialization>;
		};	
#endif
    }
    template <typename EC>
    std::size_t size() 
    {
        return meta::size<EC>();
    }

  }
}

#endif
