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

#include <boost/enums/scoped/emulation.hpp>
#include <iostream>

BOOST_ENUM_TYPE_START(E, unsigned long) 
{  E1 = 1, E2 = 2, Ebig = 0xFFFFFFF0U }
BOOST_ENUM_TYPE_CONS_END(E, unsigned long)
BOOST_ENUMS_SPECIALIZATIONS(E, unsigned long)


int main() { 
  std::cout << sizeof( E ) << std::endl; 
  std::cout << "Ebig = " << E::Ebig << std::endl; 
  std::cout << "E1 ? -1 =\t" << ( E::E1 < -1 ? "less" : E::E1 > -1 ? "greater" : "equal" ) << std::endl; 
  std::cout << "Ebig ? -1 =\t" << ( E::Ebig < -1 ? "less" : E::Ebig > -1 ? "greater" : "equal" ) << std::endl;

  E e1(E::E1);
  E ebig(E::Ebig); 
  std::cout << "e1 ? -1 =\t" << ( e1 < -1 ? "less" : e1 > -1 ? "greater" : "equal" ) << std::endl; 
  std::cout << "ebig ? -1 =\t" << ( ebig < -1 ? "less" : ebig > -1 ? "greater" : "equal" ) << std::endl;
  return 0;
}

