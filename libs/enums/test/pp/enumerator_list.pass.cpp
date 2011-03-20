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

#include <boost/enums/pp/enumerator_definition.hpp>
#include <boost/enums/pp/enumerator_list.hpp>

#define MySeq ( (E0)(3) ) ( (E1) ) ( (E2)(7)(e2) )

enum Ex {
  
  BOOST_ENUMS_ENUMERATOR_LIST_GENERATE(
                                       ( (Green)(0) ) 
                                       ( (Orange) ) 
                                       ( (Red)(2)("Rojo") )
                                       )
}; 

