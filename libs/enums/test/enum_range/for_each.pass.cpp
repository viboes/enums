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
#include <boost/range/algorithm/for_each.hpp> 
#include <cstddef>

static std::size_t cnt=0;
void p(EnumClass ) 
{
  cnt++;
}

int main() {

  using namespace boost;
  using namespace boost::enums;


  {
    for_each(enum_range<EnumClass>(),p);
    BOOST_TEST(cnt==enums::meta::size<EnumClass>::value);
  }
  return boost::report_errors();
}
