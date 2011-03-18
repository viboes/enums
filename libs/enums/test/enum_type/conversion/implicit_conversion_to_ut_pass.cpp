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

#include "./EnumType.hpp"

void f(int ) {
}

void fail() {

  { // The wrapper is implicit convertible to underlying int
    EnumClass e ;
    f(e); 
    int i = e; 
    (void)i;
  }

}
