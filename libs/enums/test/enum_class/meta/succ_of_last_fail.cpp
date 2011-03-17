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

#include "./EnumClass.hpp"
#include <boost/enums/ordinal/succ.hpp>
#include <boost/enums/scoped/native_type.hpp>

void fail() {
  using namespace boost::enums;

  {
    enum_type<EnumClass>::type e = meta::succ<EnumClass, EnumClass::Enum2>::value ;
  }

}
