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
#include <boost/detail/lightweight_test.hpp>
#include <boost/enums/containers/enum_range.hpp>
#include <boost/foreach.hpp>
#include <cstddef>

static std::size_t cnt=0;
void p(Ex::EnumClass )
{
  cnt++;
}

#define BOOST_ENUMS_FOREACH(EC, V) BOOST_FOREACH(EC V, boost::enums::enum_range<EC>())

int main() {

  using namespace boost;
  using namespace boost::enums;


  {
    //BOOST_FOREACH(Ex::EnumClass e, enum_range<Ex::EnumClass>())
    BOOST_ENUMS_FOREACH(Ex::EnumClass, e)
    {
        cnt++;
    }
    BOOST_TEST(cnt==enums::meta::size<Ex::EnumClass>::value);
  }
  return boost::report_errors();
}
